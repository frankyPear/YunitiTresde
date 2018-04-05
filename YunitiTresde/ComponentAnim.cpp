#include "ComponentAnim.h"
#include "ComponentTransform.h"
#include "GameObject.h"
#include <queue>

using namespace std;

ComponentAnim::ComponentAnim()
{
	component_id = App->rng->GetRandomNumber();
}


ComponentAnim::~ComponentAnim()
{
}

void ComponentAnim::SetAnimIdAndName(int id, const char* channelName)
{
	animInstanceId = id;
	animName = channelName;
}

void ComponentAnim::SetAnimId(int id)
{
	animInstanceId = id;
}

void ComponentAnim::ResetAnimId()
{
	animInstanceId = -1;
	animName = "";
}


void ComponentAnim::UpdateAnim()
{
	if (animInstanceId != -1)
	{
		queue<GameObject*> visitQueue;
		visitQueue.push(linked_to);
		while (!visitQueue.empty())
		{
			GameObject *actual = visitQueue.front();
			visitQueue.pop();
			for (int i = 0; i < actual->GetChilds().size(); ++i) visitQueue.push(actual->GetChilds()[i]);
		}
	}
}
