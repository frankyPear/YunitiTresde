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

	bool ImportAudioSource(const char*path);
	bool LoadResourceAudio(ResourceAudio *ra);


public:
	int resourcesImported = 0;
	std::vector<int> idsLeft;
	BASS_FILEPROCS* BassIO = nullptr;
};

