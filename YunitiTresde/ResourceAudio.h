#pragma once
#include "Resource.h"
class ResourceAudio :
	public Resource
{

	enum AudioFormat {STREAM,SAMPLE};

public:
	ResourceAudio(uid id, Type t);
	~ResourceAudio();

	AudioFormat GetAudioFormat() const;
	uint GetResourceAudioId() const;
	void SetAudioFormat();

public:
	uint resourceAudioId;
	AudioFormat audioformat;
};

