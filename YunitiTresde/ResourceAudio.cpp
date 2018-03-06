#include "ResourceAudio.h"



ResourceAudio::ResourceAudio(uid id, Type t) :Resource(id,audio)
{

}


ResourceAudio::~ResourceAudio()
{

}

ResourceAudio::AudioFormat ResourceAudio::GetAudioFormat() const
{
	return audioformat;
}

uint ResourceAudio::GetResourceAudioId() const
{
	return resourceAudioId;
}

const char* ResourceAudio::GetFilePath() const
{
	return filepath;
}

void ResourceAudio::SetAudioFormat(AudioFormat af)
{
	audioformat = af;
}

void ResourceAudio::SetResourceAudioId(uint newID)
{
	resourceAudioId = newID;
}

void ResourceAudio::SetFilePath(const char *path)
{
	filepath = path;
}


bool ResourceAudio::LoadInMemory()
{
	return true;
}