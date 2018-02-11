#include "Resource.h"

Resource::Resource(uid id, Type type) : _id(id), _type(type)
{}

Resource::~Resource()
{}
Resource::Type Resource::GetType() const
{
	return _type;
}

// ---------------------------------------------------------
uid Resource::GetId() const
{
	return _id;
}
// ---------------------------------------------------------
const char * Resource::GetFileName() const
{
	return _file.c_str();
}
// ---------------------------------------------------------
const char * Resource::GetExportedFileName() const
{
	return _exportedFile.c_str();
}

bool Resource::IsLoadedToMemory() const
{
	return _isLoaded > 0;
}

bool Resource::LoadToMemory()
{
	if (_isLoaded > 0)
		_isLoaded++;
	else
		_isLoaded = LoadInMemory() ? 1 : 0;

	return _isLoaded > 0;
}

// ---------------------------------------------------------
uint Resource::CountReferences() const
{
	return _isLoaded;
}

// ---------------------------------------------------------
//void Resource::Save(Config & config) const
//{
//	config.AddUID("UID", uid);
//	config.AddInt("Type", type);
//	config.AddString("File", file.c_str());
//	config.AddString("Exported", exported_file.c_str());
//}
//
//// ---------------------------------------------------------
//void Resource::Load(const Config & config)
//{
//	uid = config.GetUID("UID", 0);
//	type = (Type)config.GetInt("Type", unknown);
//	file = config.GetString("File", "???");
//	exported_file = config.GetString("Exported", "???");
//}
