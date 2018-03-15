#pragma once
#include "Resource.h"
class ResourceAudio :
	public Resource
{

	

public:
	enum AudioFormat { STREAM, SAMPLE };

	ResourceAudio(uid id, Type t);
	~ResourceAudio();

	AudioFormat GetAudioFormat() const;
	uint GetResourceAudioId() const;
	const char* GetFilePath() const;
	void SetAudioFormat(AudioFormat af);
	void SetResourceAudioId(uint newID);
	void SetFilePath(const char *path);
	bool LoadInMemory();

public:
	uint resourceAudioId = 0;
	AudioFormat audioformat;
	const char* filepath;
};

