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
private:
	void Load(const std::experimental::filesystem::path& path);

	const std::string& Get(const std::experimental::filesystem::path& path) const;

	std::map<std::experimental::filesystem::path, std::string> buffers;


};



#endif // !_MODULEUI_

