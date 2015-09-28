//
// Osu Core
// Beatmap 读取器
// 作者：SunnyCase
// 创建时间：2015-08-03
//
#pragma once
#include "Beatmap.h"

DEFINE_NS_OSU_CORE

enum class ReadingContext
{
	FileVersion,
	FindSection,
	General,
	Editor,
	Metadata,
	Difficulty,
	TimingPoints
};

///<summary>Beatmap 读取器</summary>
public ref class BeatmapReader sealed
{
public:
	///<summary>创建 <see cref="BeatmapReader"/> 的实例。</summary>
	BeatmapReader();

	///<summary>从文本读取 Beatmap</summary>
	///<param name="source">Beatmap 源文本</param>
	Beatmap^ Read(Platform::String^ source);
private:
	void ReadLine(Beatmap^ beatmap, std::wstring&& line);

	void ReadFileVersion(Beatmap^ beatmap, std::wstring&& line);
	void ReadSection(Beatmap^ beatmap, std::wstring&& line);
	void ReadGeneralSection(Beatmap^ beatmap, std::wstring&& line);
	void ReadMetadataSection(Beatmap^ beatmap, std::wstring&& line);
	void ReadDifficultySection(Beatmap^ beatmap, std::wstring&& line);
	void ReadTimingPointsSection(Beatmap^ beatmap, std::wstring&& line);
private:
	ReadingContext readingContext;
};

END_NS_OSU_CORE