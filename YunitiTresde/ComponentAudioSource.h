#pragma once
#include "Component.h"
#include "ComponentWithResource.h"
#include "Globals.h"
class ComponentAudioSource :
	public Component,public ComponentWithResource
{
public:

	enum State {UNLOADED,PLAYING,PAUSED,STOPPED, WAITING_TO_PLAY, TO_PLAY, WAITING_TO_PAUSE,TO_PAUSE, 
		WAITING_TO_UNPAUSE,TO_RESUME,TO_STOP,UNINITIALIZED};
	
	ComponentAudioSource();
	~ComponentAudioSource();

	void UpdateAudioSource();
	State GetState() const;
	void SetState(State s);
	void AssignAudioResource(uint audioID);

	bool SetResource(uid id)override;

	bool IsPlaying() const;
	bool IsPaused() const;
	bool IsStopped() const;

	bool Play();
	bool Pause();
	bool Resume();
	bool Stop();

	void Unload();

private:
	State actualState=State::UNLOADED;

public:

	float maxDistance = 0.f;
	float minDistance = 0.f;

	float fadeOut = 1.0f;
	float fadeIn = 1.0f;

	int angleConeIn = 360;
	int angleConeOut = 360;
	float VolumeConeOut = 0.f;
	
	

};

