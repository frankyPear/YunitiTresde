#pragma once
#include "Component.h"
#include "Globals.h"
class ComponentAudioSource :
	public Component
{
public:

	enum State {PLAYING,PAUSED,STOPPED,TO_PLAY,TO_PAUSE,TO_RESUME,TO_STOP, UNINITIALIZED};

	ComponentAudioSource();
	~ComponentAudioSource();

	void UpdateAudioSource();
	State GetState() const;
	void SetState(State s);
	void AssignAudioResource(uint audioID);

	bool IsPlaying() const;
	bool IsPaused() const;
	bool IsStopped() const;

	bool Play();
	bool Pause();
	bool Resume();
	bool Stop();

private:
	State actualState;

};

