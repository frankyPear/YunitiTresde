#include "ModuleTest.h"


using namespace std;

ModuleTest::ModuleTest()
{
	// JSON Test
	j =
	{
		{ "pi", 3.14 },
		{ "name", "json j" },
		{ "size", 3 }
	};
	// Math Geo Lib test
	f.x = 3.0f;
	f.y = 2.0f;
	f.z = 1.0f;
}


ModuleTest::~ModuleTest()
{
}


bool ModuleTest::Init() {
	return true;
}

bool ModuleTest::Start() {
	return true;
}

update_status ModuleTest::Update() {

	return UPDATE_CONTINUE;
}
bool ModuleTest::CleanUp() {
	return true;

}