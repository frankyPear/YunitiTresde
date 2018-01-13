#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(), mouse({0, 0}), mouse_motion({0,0})
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	RELEASE_ARRAY(keyboard);
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ModuleInput::Start()
{
	return true;
}

// Called each loop iteration
update_status ModuleInput::PreUpdate()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	return true;
}

// ---------
bool ModuleInput::GetWindowEvent(EventWindow ev) const
{
	return windowEvents[ev];
}

const iPoint& ModuleInput::GetMousePosition() const
{
	return mouse;
}

const iPoint& ModuleInput::GetMouseMotion() const
{
	return mouse_motion;
}