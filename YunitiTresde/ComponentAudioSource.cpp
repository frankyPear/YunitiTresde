#include "ComponentAudioSource.h"



ComponentAudioSource::ComponentAudioSource()
{
}


ComponentAudioSource::~ComponentAudioSource()
{
}

void ComponentAudioSource::UpdateAudioSource()
{

}

ComponentAudioSource::State ComponentAudioSource::GetState() const
{
	return actualState;
}

void ComponentAudioSource::SetState(State s)
{
	actualState = s;
}

bool ComponentAudioSource::IsPlaying() const
{
	return actualState == State::PLAYING;
}

bool ComponentAudioSource::IsPaused() const
{
	return actualState == State::PAUSED;
}

bool ComponentAudioSource::IsStopped() const
{
	return actualState == State::STOPPED;
}

bool ComponentAudioSource::Play()
{
	bool ret;
	actualState == State::STOPPED ? ret = false: ret = true;
	if (ret) actualState = State::TO_PLAY;
	return ret;
}

bool ComponentAudioSource::Pause()
{
	bool ret;
	actualState == State::PLAYING ? ret = false : ret = true;
	if (ret) actualState = State::TO_PAUSE;
	return ret;
}

bool ComponentAudioSource::Resume()
{
	bool ret;
	actualState == State::PAUSED ? ret = false : ret = true;
	if (ret) actualState = State::TO_RESUME;
	return ret;
}

bool ComponentAudioSource::Stop()
{
	bool ret;
	actualState == State::PLAYING ? ret = false : ret = true;
	if (ret) actualState = State::TO_STOP;
	return ret;
}