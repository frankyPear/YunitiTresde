#ifndef _IMPORTER_H_
#define _IMPORTER_H_

class ResourceMesh;
class MeshImporter;



class Importer
{
public:
	Importer();
	~Importer();

private:
	MeshImporter* meshImporter = nullptr;
};

#endif // !_IMPORTER_H_