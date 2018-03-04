#pragma once
#include "Component.h"
class ComponentAudioListener :
	public Component
{
public:
	ComponentAudioListener();
	~ComponentAudioListener();
	


	float GetDoppler() const;
	float GetRoll_off() const;
	float GetDistance() const;

	void SetDoppler(float newDopplerValue);
	void SetRoll_off(float newRoll_offValue);
	void SetDistance(float newDistanceValue);

public:
	float doppler = 1.0f;
	float roll_off = 1.0f;
	float distance = 150.0f;
};

