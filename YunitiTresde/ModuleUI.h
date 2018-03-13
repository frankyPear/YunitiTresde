#ifndef _MODULEUI_
#define _MODULEUI_

#include "Module.h"
#include "Globals.h"
#include <vector>
#include <experimental/filesystem>
#include <map>
class ModuleUI :
	public Module
{

public:
	ModuleUI();
	~ModuleUI();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);

	bool CleanUp();

	void WowFirstPage();
	void printBackground();
	void printLogo();
	void printButton1();
	void printButton2();
private:
	void Load(const std::experimental::filesystem::path& path);

	const std::string& Get(const std::experimental::filesystem::path& path) const;

	void printElement(const char * path, float * vertices);

	float verticesBackground[12] = {
		0.850f, 0.650f,0.f,  -0.850f, 0.650f,0.f,  -0.850f,-0.650f,0.f,   0.850f,-0.650f,0.f };
	float verticeslogo[12] = {
		-0.40f, 0.50f,0.15f,  -0.750f, 0.50f,0.15f,  -0.750f,0.30f,0.15f,   -0.40f,0.30f,0.15f };
	float verticesButtonMA[12] = {
		-0.45f, -0.30f,0.15f,  -0.650f, -0.30f,0.15f,  -0.650f,-0.35f,0.15f,   -0.45f,-0.35f,0.15f };
	float verticesButtonCS[12] = {
		-0.45f, -0.40f,0.15f,  -0.650f, -0.40f,0.15f,  -0.650f,-0.45f,0.15f,   -0.45f,-0.45f,0.15f };
	float verticesButtonLogin[12] = {
		0.15f, -0.25f,0.15f,  -0.150f, -0.25f,0.15f,  -0.150f,-0.35f,0.15f,   0.15f,-0.35f,0.15f };
	float verticesInputLogin[12] = {
		0.15f, -0.15f,0.15f,  -0.150f, -0.15f,0.15f,  -0.150f,-0.25f,0.15f,   0.15f,-0.25f,0.15f };
	float verticesInputPass[12] = {
		0.15f, -0.05f,0.15f,  -0.150f, -0.05f,0.15f,  -0.150f,-0.15f,0.15f,   0.15f,-0.15f,0.15f };
	float verticesButtonCinematics[12] = {
		0.650f, -0.30f,0.15f,  0.450f, -0.30f,0.15f,  0.450f,-0.35f,0.15f,   0.650f,-0.35f,0.15f };
	float verticesButtonCredits[12] = {
		0.650f, -0.35f,0.15f,  0.450f, -0.35f,0.15f,  0.450f,-0.40f,0.15f,   0.650f,-0.40f,0.15f };
	float verticesButtonTerms[12] = {
		0.650f, -0.45f,0.15f,  0.450f, -0.45f,0.15f,  0.450f,-0.50f,0.15f,   0.650f,-0.50f,0.15f };

	std::map<std::experimental::filesystem::path, std::string> buffers;


};



#endif // !_MODULEUI_

