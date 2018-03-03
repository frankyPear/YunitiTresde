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
