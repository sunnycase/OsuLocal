//
// Osu Core
// Beatmap ��ȡ��
// ���ߣ�SunnyCase
// ����ʱ�䣺2015-08-03
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

///<summary>Beatmap ��ȡ��</summary>
public ref class BeatmapReader sealed
{
public:
	///<summary>���� <see cref="BeatmapReader"/> ��ʵ����</summary>
	BeatmapReader();

	///<summary>���ı���ȡ Beatmap</summary>
	///<param name="source">Beatmap Դ�ı�</param>
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