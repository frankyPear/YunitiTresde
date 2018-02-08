#pragma once
#include "Globals.h"
#include <string>

class Config;

class Resource
{
	friend class ModuleResources;
public:
	enum Type {
		texture,
		mesh,
		audio,
		scene,
		bone,
		animation,
		default
	};

public:
	//Constructor
	Resource(uid uid, Type type);

	//Destructor
	virtual ~Resource();


#pragma region Getters
	Type GetType() const;
	uid GetId() const;
	const char* GetFileName() const;
	const char* GetExportedFileName() const;
#pragma endregion

	bool IsLoadedToMemory() const;
	bool LoadToMemory();

	uint CountReferences() const;

	//virtual void Save(Config& config) const;
	//virtual void Load(const Config& config);

protected:

	virtual bool LoadInMemory() = 0;

protected:

	uid _id = 0;
	std::string _file;
	std::string _exportedFile;

	Type _type = Type:: default;
	uint _isLoaded = 0;
};