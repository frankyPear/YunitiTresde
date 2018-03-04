#include "ModuleAudio.h"
#include "ComponentAudioListener.h"
#include "ComponentAudioSource.h"
#include "ResourceAudio.h"
#include "GameObject.h"
#include "ComponentTransform.h"

using namespace std;


ModuleAudio::ModuleAudio()
{
	//HWND hwnd;
	//BASS_Init(-1, 44100, BASS_DEVICE_STEREO, 0, nullptr);

}

bool ModuleAudio::Start()
{
	return true;
}

bool ModuleAudio::Init()
{
	bool success = BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, nullptr);
	if (!success) LOG("Couldn't initialize bass")
	return success;
}

bool ModuleAudio::Clear()
{
	return true;
}

update_status ModuleAudio::Update()
{
	return UPDATE_CONTINUE;
}

ModuleAudio::~ModuleAudio()
{

}

bool ModuleAudio::ImportAudioSource(const char*path) 
{
	bool ret = false;
	if (path != nullptr)
	{
		const char* dot = strrchr(path,'.');
		if (dot) {
			dot = dot + 1;
			if (dot == "ogg")
			{
				HSTREAM stream = BASS_StreamCreateFile(FALSE, path, 0, 0, 0);
				if (stream == 0) LOG("Failed creating stream.")		
				else {
					BASS_StreamFree(stream);
					ret = true;
				}
			}
			else if (dot == "wav")
			{
				char *buffer= nullptr;
				int size = 0;
				LPDWORD numberOfBytesRead = 0;
				HANDLE hin = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				ReadFile(hin, buffer, size, numberOfBytesRead,NULL);
				//HSAMPLE sample = BASS_SampleCreate(size, 28160, 1, 1, BASS_SAMPLE_LOOP | BASS_SAMPLE_OVER_POS);
				if (buffer != nullptr) {
					HSAMPLE sample = BASS_SampleLoad(TRUE, buffer, 0, size, 5, BASS_SAMPLE_OVER_VOL);
					if (sample == 0) LOG("Failed to load sample")
					else {
						BASS_SampleFree(sample);
						ret = true;
					}
					RELEASE(buffer);
				}
				else LOG("Failed to read the file.")
			}
		}		
	}
	if (ret)
	{
		
	}
	return ret;
}

bool ModuleAudio::LoadResourceAudio(ResourceAudio *ra)
{
	bool ret = false;
	uint audioID = 0;

	const char* dot = strrchr(ra->GetFilePath(), '.');
	if (dot) {
		dot = dot + 1;
		if (dot == "ogg")
		{
			HSTREAM stream = BASS_StreamCreateFile(FALSE, ra->GetFilePath(), 0, 0, 0);
			if (stream == 0) LOG("Failed creating stream.")
			else 
			{
				audioID = (uint)stream;
				ra->SetAudioFormat(ResourceAudio::STREAM);
			}
		}
		else if (dot == "wav")
		{
			char *buffer = nullptr;
			int size = 0;
			LPDWORD numberOfBytesRead = 0;
			HANDLE hin = CreateFile(ra->GetFilePath(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			ReadFile(hin, buffer, size, numberOfBytesRead, NULL);
			//HSAMPLE sample = BASS_SampleCreate(size, 28160, 1, 1, BASS_SAMPLE_LOOP | BASS_SAMPLE_OVER_POS);
			if (buffer != nullptr) {
				HSAMPLE sample = BASS_SampleLoad(TRUE, buffer, 0, size, 5, BASS_SAMPLE_OVER_VOL);
				if (sample == 0) LOG("Failed to load sample")
				else {
					audioID = BASS_SampleGetChannel(sample,FALSE);
					if (audioID != 0) ra->SetAudioFormat(ResourceAudio::SAMPLE);
					else LOG ("Failed to get a channel")
				}
				RELEASE(buffer);
			}
			else LOG("Failed to read the file.")
		}
	}
	if (audioID != 0)
	{
		ra->SetResourceAudioId(audioID);
		ret = true;
	}
	return ret;
}

void ModuleAudio::AudioListenerUpdate()
{
	if (listener != nullptr) {
		BASS_Set3DFactors(listener->GetDistance(), listener->GetRoll_off(), listener->GetDoppler());
		ComponentTransform *ct = (ComponentTransform *)listener->LinkedTo()->GetComponent(TRANSFORMATION);
		if (ct != nullptr) {
			BASS_Set3DPosition((BASS_3DVECTOR*) &ct->GetGlobalPosition(), nullptr, (BASS_3DVECTOR*)&ct->GetGlobalTransform().WorldZ(), (BASS_3DVECTOR*)&ct->GetGlobalTransform().WorldY());
		}
	}
}

void ModuleAudio::AudioSourceUpdate(ComponentAudioSource *as)
{

}

float ModuleAudio::GetMusicVolume() const
{
	return music_volume;
}

float ModuleAudio::GetFXVolume() const
{
	return fx_volume;
}

float ModuleAudio::GetMasterVolume() const
{
	return master_volume;
}

ComponentAudioListener* ModuleAudio::GetAudioListener()
{
	return listener;
}


void ModuleAudio::SetMusicVolume(float volume)
{
	music_volume = volume;
}

void ModuleAudio::SetFXVolume(float volume)
{
	fx_volume = volume;
}

void ModuleAudio::SetMasterVolume(float volume)
{
	master_volume = volume;
}

void ModuleAudio::SetAudioListener(ComponentAudioListener *listenerNew)
{
	listener = listenerNew;

}
