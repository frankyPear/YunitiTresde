#include "ModuleAudio.h"
#include "ComponentAudioListener.h"
#include "ComponentAudioSource.h"
#include "ResourceAudio.h"

using namespace std;


ModuleAudio::ModuleAudio()
{
	//HWND hwnd;
	//BASS_Init(-1, 44100, BASS_DEVICE_STEREO, hwnd, nullptr);
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
				HSTREAM stream = BASS_StreamCreateFile(FALSE, "afile.mp3", 0, 0, 0);
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
	uint id = 0;

	return ret;
}

