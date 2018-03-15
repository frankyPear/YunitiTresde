#pragma once
#include "Component.h"
class ComponentAnim :
	public Component
{
public:
	ComponentAnim();
	~ComponentAnim();

	void SetAnimIdAndName(int id, const char* channelName);
	void SetAnimId(int id);
	void ResetAnimId();

	void UpdateAnim();

public:

	const char* animName = "";
	int animInstanceId = -1;
};

