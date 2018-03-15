#pragma once
#include "Component.h"
#include "ComponentWithResource.h"
#include "Globals.h"

class ResourceAudio;

class ComponentAudioSource :
	public Component,public ComponentWithResource
{
public:

	enum State {UNLOADED,PLAYING,PAUSED,STOPPED,TO_PLAY, TO_PAUSE,TO_RESUME,TO_STOP,UNINITIALIZED};
	
	ComponentAudioSource();
	ComponentAudioSource(float distmin, float distmax, float fadeOut, float fadeIn,int angleConeIn, int angleConeOut, float outVol);
	~ComponentAudioSource();

	void UpdateAudioSource();
	State GetState() const;
	void SetState(State s);
	ResourceAudio* GetAudioSource() const;
	void SetAudioResource(ResourceAudio* newResource);

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
	State actualState = State::UNLOADED;
	ResourceAudio *rs = nullptr;

public:

	float maxDistance = 0.0f;
	float minDistance = 0.0f;

	float fadeOut = 1.0f;
	float fadeIn = 1.0f;

	int angleConeIn = 360;
	int angleConeOut = 360;
	float VolumeConeOut = 0.0f;
	
	

};

