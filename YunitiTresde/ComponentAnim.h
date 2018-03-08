#pragma once
#include "Component.h"
class ComponentAnim :
	public Component
{
public:
	ComponentAnim();
	~ComponentAnim();

	void SetAnimId(int id, const char* channelName);
	void ResetAnimId();

	void UpdateAnim();

public:

	const char* animName = "";
	int animInstanceId;
};

