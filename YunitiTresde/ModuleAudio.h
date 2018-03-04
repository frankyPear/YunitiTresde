#pragma once

#include <vector>
#include <string>
#include "Module.h"
#include "Bass\include\bass.h"
#include "Bass\include\bassenc.h"
#include "Bass\include\bassenc_ogg.h"

class ComponentAudioListener;
class ComponentAudioSource;
class ResourceAudio;

class ModuleAudio :
	public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Start();
	bool Init();
	bool Clear();
	update_status Update();

	bool ImportAudioSource(const char*path);
	bool LoadResourceAudio(ResourceAudio *ra);
	void AudioListenerUpdate();
	void AudioSourceUpdate(ComponentAudioSource *as);
	void UpdateStatus();

	float GetMusicVolume() const;
	float GetFXVolume() const;
	float GetMasterVolume() const;
	ComponentAudioListener *GetAudioListener();

	void SetMusicVolume(float volume);
	void SetFXVolume(float volume);
	void SetMasterVolume(float volume);
	void SetAudioListener(ComponentAudioListener *listener);

public:
	int resourcesImported = 0;
	std::vector<int> idsLeft;
	BASS_FILEPROCS* BassIO = nullptr;

	ComponentAudioListener *listener = nullptr;
	float music_volume = 1.0f;
	float fx_volume = 1.0f;
	float master_volume = 1.0f;
};

