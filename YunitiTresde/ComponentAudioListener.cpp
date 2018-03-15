#include "ComponentAudioListener.h"


ComponentAudioListener::ComponentAudioListener()
{

}

ComponentAudioListener::~ComponentAudioListener()
{

}



float ComponentAudioListener::GetDoppler() const
{
	return doppler;
}

float ComponentAudioListener::GetRoll_off() const
{
	return roll_off;
}

float ComponentAudioListener::GetDistance() const
{
	return distance;
}

void ComponentAudioListener::SetDoppler(float newDopplerValue)
{
	doppler = newDopplerValue;
	if (doppler < 0.0) doppler = 0.0f;
	if (doppler > 1.0) doppler = 1.0f;
}

void ComponentAudioListener::SetRoll_off(float newRoll_offValue)
{
	roll_off = newRoll_offValue;
	if (roll_off < 0.0) roll_off = 0.0f;
	if (roll_off > 1.0) roll_off = 1.0f;
}

void ComponentAudioListener::SetDistance(float newDistanceValue)
{
	distance = newDistanceValue;
	if (distance < 0.0) distance = 0.0f;
	if (distance > 1.0) distance = 1.0f;
}