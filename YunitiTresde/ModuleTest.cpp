#include "ModuleTest.h"


using namespace std;

ModuleTest::ModuleTest()
{

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