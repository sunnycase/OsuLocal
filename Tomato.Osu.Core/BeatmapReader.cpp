//
// Osu Core
// Beatmap 读取器
// 作者：SunnyCase
// 创建时间：2015-08-03
//
#include "pch.h"
#include "BeatmapReader.h"

using namespace Platform;
using namespace NS_OSU_CORE;

namespace
{
	const std::wstring OsuFileVersionPrefix(L"osu file format v");
}

BeatmapReader::BeatmapReader()
{

}

Beatmap^ BeatmapReader::Read(Platform::String ^ source)
{
	readingContext = ReadingContext::FileVersion;

	std::wstring nativeSource(Platform::begin(source), Platform::end(source));
	std::wistringstream ss(nativeSource);

	enum State
	{
		// 开头
		Leading,
		// 有意义的符号
		Symbols,
		// 第一个 /
		FirstSlash,
		// 等待输出
		Pending,
		// 忽略
		Ignore
	};
	ss >> std::noskipws;

	std::wstringstream line;
	State state = Leading;

	auto map = ref new Beatmap();

	while (!ss.eof())
	{
		wchar_t chr;
		ss >> chr;

	start:
		switch (state)
		{
		case Leading:
			switch (chr)
			{
			case '/':
				state = FirstSlash;
			case ' ':
				break;
			case '\r':
			case '\n':
				state = Ignore;
				break;
			default:
				state = Symbols;
				// 重新读取字符
				goto start;
				break;
			}
			break;
		case Symbols:
			switch (chr)
			{
			case '/':
				state = FirstSlash;
				break;
			case '\r':
			case '\n':
				// 遇到换行则说明该行读取完毕
				state = Pending;
				break;
			default:
				line << chr;
				break;
			}
			break;
		case FirstSlash:
			switch (chr)
			{
			case '/':
				// 又是一个 / 说明后面都是注释
				if (line.peek() == EOF)
					state = Ignore;
				else
					state = Pending;
				break;
			default:
				// 其他情况说明不是注释
				line << '/';
				state = Symbols;
				goto start;
				break;
			}
		default:
			break;
		}

		if (state == Ignore)
		{
			line.swap(decltype(line)());
			state = Leading;
		}
		else if (state == Pending)
		{
			// 移除尾部空格
			auto trimLine = std::exchange(line, decltype(line)()).str();
			auto idx = trimLine.find_last_not_of(' ');
			if (idx != std::wstring::npos)
			{
				trimLine = trimLine.substr(0, idx + 1);

				assert(trimLine.find_first_not_of(' ') == 0);
				ReadLine(map, std::move(trimLine));
			}
			state = Leading;
		}
	}

	return map;
}

void BeatmapReader::ReadLine(Beatmap^ beatmap, std::wstring&& line)
{
	switch (readingContext)
	{
	case ReadingContext::FileVersion:
		ReadFileVersion(beatmap, std::move(line));
		break;
	case ReadingContext::FindSection:
		ReadSection(beatmap, std::move(line));
		break;
	case ReadingContext::General:
		ReadGeneralSection(beatmap, std::move(line));
		break;
	//case ReadingContext::Editor:
	//	ReadEditorSection(beatmap, line);
	//	break;
	case ReadingContext::Metadata:
		ReadMetadataSection(beatmap, std::move(line));
		break;
	case ReadingContext::Difficulty:
		ReadDifficultySection(beatmap, std::move(line));
		break;
	case ReadingContext::TimingPoints:
		ReadTimingPointsSection(beatmap, std::move(line));
		break;
	default:
		break;
	}
}

void BeatmapReader::ReadFileVersion(Beatmap^ beatmap, std::wstring&& line)
{
	auto idx = line.find(OsuFileVersionPrefix);
	if (idx == 0)
	{
		std::wstringstream ss(line.substr(OsuFileVersionPrefix.length()));
		float version;
		ss >> version;
		beatmap->Version = version;
		readingContext = ReadingContext::FindSection;
	}
}

void BeatmapReader::ReadSection(Beatmap^ beatmap, std::wstring&& line)
{
	static std::unordered_map<std::wstring, std::function<void(ReadingContext&, Beatmap^)>> logics
	{
		{ L"[General]", [](ReadingContext& context, Beatmap^ map) {
				context = ReadingContext::General;
				map->General = ref new GeneralSection();
			}
		},
		{ L"[Metadata]", [](ReadingContext& context, Beatmap^ map) {
				context = ReadingContext::Metadata;
				map->Metadata = ref new MetadataSection();
			}
		},
		{ L"[Difficulty]", [](ReadingContext& context, Beatmap^ map) {
				context = ReadingContext::Difficulty;
				map->Difficulty = ref new DifficultySection();
			}
		},
		{ L"[TimingPoints]", [](ReadingContext& context, Beatmap^ map) {
				context = ReadingContext::TimingPoints;
				map->internalTimingPoints = ref new Collections::Vector<TimingPoint^>();
			}
		}
	};

	auto it = logics.find(line);
	if (it != logics.end())
		it->second(readingContext, beatmap);
	else
		readingContext = ReadingContext::FindSection;
}

std::wstring trim(const std::wstring& str)
{
	if (!str.length())
		return std::wstring();
	auto startIdx = str.find_first_not_of(' ');
	auto endIdx = str.find_last_not_of(' ');
	return str.substr(startIdx, endIdx - startIdx + 1);
}

void BeatmapReader::ReadGeneralSection(Beatmap^ beatmap, std::wstring && line)
{
	if (line.front() == '[')
		return ReadSection(beatmap, std::move(line));

	auto splitIdx = line.find_first_of(':');
	if (splitIdx != std::wstring::npos)
	{
		auto key = trim(line.substr(0, splitIdx));
		auto value = trim(line.substr(splitIdx + 1));

		static const std::unordered_map<std::wstring, std::function<void(GeneralSection^, std::wstring&&)>> logics
		{
			{ L"AudioFilename", [](GeneralSection^ section, std::wstring&& value) {
					section->AudioFileName = ref new String(value.c_str(), value.length());
				}
			},
			{ L"AudioLeadIn", [](GeneralSection^ section, std::wstring&& value) {
					section->AudioLeadIn = MSToTimeSpan(_wtoll(value.c_str()));
				}
			},
			{ L"PreviewTime", [](GeneralSection^ section, std::wstring&& value) {
					section->PreviewTime = MSToTimeSpan(_wtoll(value.c_str()));
				}
			},
			{ L"Countdown", [](GeneralSection^ section, std::wstring&& value) {
					std::wstringstream ss(std::move(value));
					bool val; ss >> val;
					section->Countdown = val;
				}
			},
			{ L"SampleSet", [](GeneralSection^ section, std::wstring&& value) {
					section->SampleSet = ref new String(value.c_str(), value.length());
				}
			},
			{ L"StackLeniency", [](GeneralSection^ section, std::wstring&& value) {
					section->StackLeniency = _wtof(value.c_str());
				}
			},
			{ L"Mode", [](GeneralSection^ section, std::wstring&& value) {
					section->Mode = static_cast<GameMode>(_wtoi(value.c_str()));
				}
			},
			{ L"LetterboxInBreaks", [](GeneralSection^ section, std::wstring&& value) {
					std::wstringstream ss(std::move(value));
					bool val; ss >> val;
					section->LetterboxInBreaks = val;
				}
			},
			{ L"WidescreenStoryboard", [](GeneralSection^ section, std::wstring&& value) {
					std::wstringstream ss(std::move(value));
					bool val; ss >> val;
					section->WidescreenStoryboard = val;
				}
			}
		};

		auto it = logics.find(key);
		if (it != logics.end())
			it->second(beatmap->General, std::move(value));
	}
}

void BeatmapReader::ReadMetadataSection(Beatmap^ beatmap, std::wstring && line)
{
	if (line.front() == '[')
		return ReadSection(beatmap, std::move(line));

	auto splitIdx = line.find_first_of(':');
	if (splitIdx != std::wstring::npos)
	{
		auto key = trim(line.substr(0, splitIdx));
		auto value = trim(line.substr(splitIdx + 1));

		static const std::unordered_map<std::wstring, std::function<void(MetadataSection^, std::wstring&&)>> logics
		{
			{ L"Title", [](MetadataSection^ section, std::wstring&& value) {
					section->Title = ref new String(value.c_str(), value.length());
				}
			},
			{ L"TitleUnicode", [](MetadataSection^ section, std::wstring&& value) {
					section->TitleUnicode = ref new String(value.c_str(), value.length());
				}
			},
			{ L"Artist", [](MetadataSection^ section, std::wstring&& value) {
					section->Artist = ref new String(value.c_str(), value.length());
				}
			},
			{ L"ArtistUnicode", [](MetadataSection^ section, std::wstring&& value) {
					section->ArtistUnicode = ref new String(value.c_str(), value.length());
				}
			},
			{ L"Creator", [](MetadataSection^ section, std::wstring&& value) {
					section->Creator = ref new String(value.c_str(), value.length());
				}
			},
			{ L"Version", [](MetadataSection^ section, std::wstring&& value) {
					section->Version = ref new String(value.c_str(), value.length());
				}
			},
			{ L"Source", [](MetadataSection^ section, std::wstring&& value) {
					section->Source = ref new String(value.c_str(), value.length());
				}
			},
			{ L"Tags", [](MetadataSection^ section, std::wstring&& value) {
					auto tags = ref new Collections::Vector<Platform::String^>();
					std::wistringstream source(value);
					std::for_each(std::istream_iterator<std::wstring, wchar_t>(source), std::istream_iterator<std::wstring, wchar_t>(),
						[=](const std::wstring& tag)
					{
						tags->Append(ref new String(tag.c_str(), tag.length()));
					});
					section->Tags = tags->GetView();
				}
			},
			{ L"BeatmapID", [](MetadataSection^ section, std::wstring&& value) {
					section->BeatmapId = _wtoi(value.c_str());
				}
			},
			{ L"BeatmapSetID", [](MetadataSection^ section, std::wstring&& value) {
					section->BeatmapSetId = _wtoi(value.c_str());
				}
			}
		};

		auto it = logics.find(key);
		if (it != logics.end())
			it->second(beatmap->Metadata, std::move(value));
	}
}

void BeatmapReader::ReadDifficultySection(Beatmap^ beatmap, std::wstring && line)
{
	if (line.front() == '[')
		return ReadSection(beatmap, std::move(line));

	auto splitIdx = line.find_first_of(':');
	if (splitIdx != std::wstring::npos)
	{
		auto key = trim(line.substr(0, splitIdx));
		auto value = trim(line.substr(splitIdx + 1));

		static const std::unordered_map<std::wstring, std::function<void(DifficultySection^, std::wstring&&)>> logics
		{
			{ L"HPDrainRate", [](DifficultySection^ section, std::wstring&& value) {
					section->HPDrainRate = _wtof(value.c_str());
				}
			},
			{ L"CircleSize", [](DifficultySection^ section, std::wstring&& value) {
					section->CircleSize = _wtof(value.c_str());
				}
			},
			{ L"OverallDifficulty", [](DifficultySection^ section, std::wstring&& value) {
					section->OverallDifficulty = _wtof(value.c_str());
				}
			},
			{ L"ApproachRate", [](DifficultySection^ section, std::wstring&& value) {
					section->ApproachRate = _wtof(value.c_str());
				}
			},
			{ L"SliderMultiplier", [](DifficultySection^ section, std::wstring&& value) {
					section->SliderMultiplier = _wtof(value.c_str());
				}
			},
			{ L"SliderTickRate", [](DifficultySection^ section, std::wstring&& value) {
					section->SliderTickRate = _wtof(value.c_str());
				}
			}
		};

		auto it = logics.find(key);
		if (it != logics.end())
			it->second(beatmap->Difficulty, std::move(value));
	}
}

void BeatmapReader::ReadTimingPointsSection(Beatmap^ beatmap, std::wstring && line)
{
	if (line.front() == '[')
		return ReadSection(beatmap, std::move(line));

	enum State
	{
		Offset,
		MPB,
		Meter,
		SampleType,
		SampleSet,
		Volume,
		Inherited,
		KiaiMode,
		End
	} state = Offset;

	auto timingPoint = ref new TimingPoint();
	std::wistringstream ss(line);
	while (state != End)
	{
		int iValue;
		double dValue;
		bool bValue;

		switch (state)
		{
		case Offset:
			ss >> iValue;
			timingPoint->Offset = MSToTimeSpan(iValue);
			break;
		case MPB:
			ss >> dValue;
			timingPoint->MillisecondsPerBeat = dValue;
			break;
		case Meter:
			ss >> iValue;
			timingPoint->Meter = iValue;
			break;
		case SampleType:
			ss >> iValue;
			timingPoint->SampleType = iValue;
			break;
		case SampleSet:
			ss >> iValue;
			timingPoint->SampleSet = iValue;
			break;
		case Volume:
			ss >> iValue;
			timingPoint->Volume = iValue;
			break;
		case Inherited:
			ss >> bValue;
			timingPoint->Inherited = bValue;
			break;
		case KiaiMode:
			ss >> bValue;
			timingPoint->KiaiMode = bValue;
			break;
		default:
			break;
		}
		state = static_cast<State>(state + 1);

		wchar_t splitter; ss >> splitter;
	}
	beatmap->internalTimingPoints->Append(timingPoint);
}