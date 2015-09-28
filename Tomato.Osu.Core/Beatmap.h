//
// Osu Core
// Beatmap
// 作者：SunnyCase
// 创建时间：2015-08-03
//
#pragma once
#include "common.h"

DEFINE_NS_OSU_CORE

///<summary>GameMode</summary>
public enum class GameMode
{
	Osu = 0,
	Taiko = 1,
	CatchTheBeat = 2,
	OsuTheMania = 3
};

///<summary>GeneralSection</summary>
public ref class GeneralSection sealed
{
public:
	///<summary>获取音频文件名</summary>
	property Platform::String^ AudioFileName
	{
		Platform::String^ get() { return audioFileName; }
	internal: void set(Platform::String^ value) { audioFileName = value; }
	}

	///<summary>The amount of time added before the audio file begins playing. Useful for audio files that begin immediately. </summary>
	property Windows::Foundation::TimeSpan AudioLeadIn
	{
		Windows::Foundation::TimeSpan get() { return audioLeadIn; }
	internal: void set(Windows::Foundation::TimeSpan value) { audioLeadIn = value; }
	}

	///<summary>Defines when the audio file should begin playing when selected in the song selection menu. </summary>
	property Windows::Foundation::TimeSpan PreviewTime
	{
		Windows::Foundation::TimeSpan get() { return previewTime; }
	internal: void set(Windows::Foundation::TimeSpan value) { previewTime = value; }
	}

	///<summary>Specifies whether or not a countdown occurs before the first hit object appears. </summary>
	property bool Countdown
	{
		bool get() { return countdown; }
	internal: void set(bool value) { countdown = value; }
	}

	///<summary>Specifies which set of hit sounds will be used throughout the beatmap. </summary>
	property Platform::String^ SampleSet
	{
		Platform::String^ get() { return sampleSet; }
	internal: void set(Platform::String^ value) { sampleSet = value; }
	}

	///<summary>How often closely placed hit objects will be stacked together. </summary>
	property double StackLeniency
	{
		double get() { return stackLeniency; }
	internal: void set(double value) { stackLeniency = value; }
	}

	///<summary>Defines the game mode of the beatmap. </summary>
	property GameMode Mode
	{
		GameMode get() { return mode; }
	internal: void set(GameMode value) { mode = value; }
	}

	///<summary>Specifies whether the letterbox appears during breaks. </summary>
	property bool LetterboxInBreaks
	{
		bool get() { return countdown; }
	internal: void set(bool value) { countdown = value; }
	}

	///<summary>Specifies whether or not the storyboard should be widescreen. </summary>
	property bool WidescreenStoryboard
	{
		bool get() { return countdown; }
	internal: void set(bool value) { countdown = value; }
	}

private:
	Platform::String^ audioFileName;
	Windows::Foundation::TimeSpan audioLeadIn;
	Windows::Foundation::TimeSpan previewTime;
	bool countdown;
	Platform::String^ sampleSet;
	double stackLeniency;
	GameMode mode;
	bool letterboxInBreaks;
	bool widescreenStoryboard;
};

public ref class MetadataSection sealed
{
public:
	///<summary>The title of the song limited to ASCII characters. </summary>
	property Platform::String^ Title
	{
		Platform::String^ get() { return title; }
	internal: void set(Platform::String^ value) { title = value; }
	}

	///<summary>The title of the song with unicode support. If not present, Title is used. </summary>
	property Platform::String^ TitleUnicode
	{
		Platform::String^ get() { return titleUnicode; }
	internal: void set(Platform::String^ value) { titleUnicode = value; }
	}

	///<summary>The name of the song's artist limited to ASCII characters. </summary>
	property Platform::String^ Artist
	{
		Platform::String^ get() { return artist; }
	internal: void set(Platform::String^ value) { artist = value; }
	}

	///<summary>The name of the song's artist with unicode support. If not present, Artist is used. </summary>
	property Platform::String^ ArtistUnicode
	{
		Platform::String^ get() { return artistUnicode; }
	internal: void set(Platform::String^ value) { artistUnicode = value; }
	}

	///<summary>The username of the mapper. </summary>
	property Platform::String^ Creator
	{
		Platform::String^ get() { return creator; }
	internal: void set(Platform::String^ value) { creator = value; }
	}

	///<summary>The name of the beatmap's difficulty. </summary>
	property Platform::String^ Version
	{
		Platform::String^ get() { return version; }
	internal: void set(Platform::String^ value) { version = value; }
	}

	///<summary>Describes the origin of the song. </summary>
	property Platform::String^ Source
	{
		Platform::String^ get() { return source; }
	internal: void set(Platform::String^ value) { source = value; }
	}

	///<summary>A collection of words describing the song. Tags are searchable in both the online listings and in the song selection menu. </summary>
	property Windows::Foundation::Collections::IVectorView<Platform::String^>^ Tags
	{
		Windows::Foundation::Collections::IVectorView<Platform::String^>^ get() { return tags; }
	internal: void set(Windows::Foundation::Collections::IVectorView<Platform::String^>^ value) { tags = value; }
	}

	///<summary>The ID of the single beatmap. </summary>
	property int BeatmapId
	{
		int get() { return beatmapId; }
	internal: void set(int value) { beatmapId = value; }
	}

	///<summary>The ID of the beatmap set. </summary>
	property int BeatmapSetId
	{
		int get() { return beatmapSetId; }
	internal: void set(int value) { beatmapSetId = value; }
	}
private:
	Platform::String^ title;
	Platform::String^ titleUnicode;
	Platform::String^ artist;
	Platform::String^ artistUnicode;
	Platform::String^ creator;
	Platform::String^ version;
	Platform::String^ source;
	Windows::Foundation::Collections::IVectorView<Platform::String^>^ tags;
	int beatmapId;
	int beatmapSetId;
};

public ref class DifficultySection sealed
{
public:
	///<summary>Specifies the HP Drain difficulty. </summary>
	property double HPDrainRate
	{
		double get() { return hpDrainRate; }
	internal: void set(double value) { hpDrainRate = value; }
	}

	///<summary>Specifies the size of hit object circles. </summary>
	property double CircleSize
	{
		double get() { return circleSize; }
	internal: void set(double value) { circleSize = value; }
	}

	///<summary>Specifies the amount of time allowed to click a hit object on time. </summary>
	property double OverallDifficulty
	{
		double get() { return overallDifficulty; }
	internal: void set(double value) { overallDifficulty = value; }
	}

	///<summary>Specifies the amount of time taken for the approach circle and hit object to appear. </summary>
	property double ApproachRate
	{
		double get() { return approachRate; }
	internal: void set(double value) { approachRate = value; }
	}

	///<summary>Specifies a multiplier for the slider velocity. Default value is 1. </summary>
	property double SliderMultiplier
	{
		double get() { return sliderMultiplier; }
	internal: void set(double value) { sliderMultiplier = value; }
	}

	///<summary>Specifies how often slider ticks appear. Default value is 1. </summary>
	property double SliderTickRate
	{
		double get() { return sliderTickRate; }
	internal: void set(double value) { sliderTickRate = value; }
	}
private:
	double hpDrainRate;
	double circleSize;
	double overallDifficulty;
	double approachRate;
	double sliderMultiplier = 1.0;
	double sliderTickRate = 1.0;
};

///<summary>TimingPoint</summary>
public ref class TimingPoint sealed
{
public:
	///<summary>Defines when the Timing Point takes effect. </summary>
	property Windows::Foundation::TimeSpan Offset
	{
		Windows::Foundation::TimeSpan get() { return offset; }
	internal: void set(Windows::Foundation::TimeSpan value) { offset = value; }
	}

	///<summary>Defines the beats per minute of the song. </summary>
	property double MillisecondsPerBeat
	{
		double get() { return millisecondsPerBeat; }
	internal: void set(double value) { millisecondsPerBeat = value; }
	}

	///<summary>Defines the number of beats in a measure. </summary>
	property int Meter
	{
		int get() { return meter; }
	internal: void set(int value) { meter = value; }
	}

	///<summary>Defines the type of hit sound samples that are used. </summary>
	property int SampleType
	{
		int get() { return sampleType; }
	internal: void set(int value) { sampleType = value; }
	}

	///<summary>Defines the set of hit sounds that are used. </summary>
	property int SampleSet
	{
		int get() { return sampleSet; }
	internal: void set(int value) { sampleSet = value; }
	}

	///<summary>A value from 0 - 100 that defines the volume of hit sounds. </summary>
	property int Volume
	{
		int get() { return volume; }
	internal: void set(int value) { volume = value; }
	}

	///<summary>Defines whether or not the Timing Point is an inherited Timing Point. </summary>
	property bool Inherited
	{
		bool get() { return inherited; }
	internal: void set(bool value) { inherited = value; }
	}

	///<summary>Defines whether or not Kiai Time effects are active. </summary>
	property bool KiaiMode
	{
		bool get() { return kiaiMode; }
	internal: void set(bool value) { kiaiMode = value; }
	}
private:
	Windows::Foundation::TimeSpan offset;
	double millisecondsPerBeat;
	int meter;
	int sampleType;
	int sampleSet;
	int volume;
	bool inherited;
	bool kiaiMode;
};

typedef Windows::Foundation::Collections::IVectorView<TimingPoint^> TimingPointsSection;

///<summary>Beatmap</summary>
public ref class Beatmap sealed
{
public:
	///<summary>获取文件版本</summary>
	property float Version
	{
		float get() { return version; }
	internal: void set(float value) { version = value; }
	}

	///<summary>获取 General 小节</summary>
	property GeneralSection^ General
	{
		Core::GeneralSection^ get() { return general; }
	internal: void set(GeneralSection^ value) { general = value; }
	}

	///<summary>获取 Metadata 小节</summary>
	property MetadataSection^ Metadata
	{
		MetadataSection^ get() { return metadata; }
	internal: void set(MetadataSection^ value) { metadata = value; }
	}

	///<summary>获取 Difficulty 小节</summary>
	property DifficultySection^ Difficulty
	{
		DifficultySection^ get() { return difficulty; }
	internal: void set(DifficultySection^ value) { difficulty = value; }
	}

	///<summary>获取 TimingPoints 小节</summary>
	property TimingPointsSection^ TimingPoints
	{
		TimingPointsSection^ get() 
		{
			if (!timingPoints && internalTimingPoints)
				timingPoints = internalTimingPoints->GetView();
			return timingPoints;
		}
	internal: void set(TimingPointsSection^ value) { timingPoints = value; }
	}


internal:
	Platform::Collections::Vector<TimingPoint^>^ internalTimingPoints;
private:
	float version;
	GeneralSection^ general;
	MetadataSection^ metadata;
	DifficultySection^ difficulty;
	TimingPointsSection^ timingPoints;
};

END_NS_OSU_CORE