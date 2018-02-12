#pragma once

#include "Mathgeolib\include\Geometry\Frustum.h"
#include "Mathgeolib\include\Geometry\AABB.h"
#include "GameObject.h"
#include <vector>
#include <list>

#define MINIMUM_BOX_SIZE 1
#define MAX_OBJECTS_IN_NODE 4

class CustomQuadTreeNode {
public:
	CustomQuadTreeNode();
	CustomQuadTreeNode(AABB box, CustomQuadTreeNode* parent);
	~CustomQuadTreeNode();

	void SetNodeBox(AABB box);
	void SetParent(CustomQuadTreeNode* newparent);
	void InsertInNode(GameObject* newAddition);
	void EliminateNode(GameObject* toEliminate);
	void NodeIntersect(std::vector<GameObject*>& toTest, const Frustum& camFrustum);
	void ReallocateChilds();
	void DivideBox();
	void DrawNodeBox();

public:
	CustomQuadTreeNode * parent_ = nullptr;
	AABB box_;
	std::vector<CustomQuadTreeNode*> child_nodes_;
	std::list<GameObject*> objectsInBox_;
};

class CustomQuadTree
{
public:
	CustomQuadTree();
	~CustomQuadTree();

	void Create(AABB& limits);
	void Clear();
	void Insert(GameObject *newAddition);
	void Remove(GameObject *toRemove);
	void Intersect(std::vector<GameObject*>& toTest, const Frustum& camFrustum);
	void DrawBox();

public:
	CustomQuadTreeNode * root_ = nullptr;

};

