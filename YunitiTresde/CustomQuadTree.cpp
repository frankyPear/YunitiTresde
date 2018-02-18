#include "CustomQuadTree.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Brofiler\include\Brofiler.h"
#include <stack>

using namespace std;

CustomQuadTree::CustomQuadTree()
{

}

CustomQuadTree::~CustomQuadTree()
{

}

void CustomQuadTree::Create(AABB& limits)
{
	root_ = new CustomQuadTreeNode(limits, nullptr);
}

void CustomQuadTree::Clear()
{
	delete root_;
	root_ = nullptr;
}

void CustomQuadTree::Insert(GameObject *newAddition)
{
	if (newAddition != nullptr) {
		ComponentMesh* cm = (ComponentMesh*)newAddition->GetComponent(MESH);
		ComponentTransform* ct = (ComponentTransform*)newAddition->GetComponent(TRANSFORMATION);
		if (cm != nullptr && ct != nullptr) {
			AABB newBox = *(cm->GetBoundingBox());
			newBox.TransformAsAABB(ct->GetGlobalTransform());
			if (root_ == nullptr) {
				root_ = new CustomQuadTreeNode(newBox, nullptr);
			}
			else {
				if (root_->box_.Contains(newBox)) root_->InsertInNode(newAddition);
				else {
					root_->box_.Enclose(newBox);
					root_->InsertInNode(newAddition);
				}
			}
		}
	}
}

void CustomQuadTree::Remove(GameObject *toRemove)
{
	if (root_ != nullptr && toRemove != nullptr) {
		ComponentMesh* cm = (ComponentMesh*)toRemove->GetComponent(MESH);
		ComponentTransform* ct = (ComponentTransform*)toRemove->GetComponent(TRANSFORMATION);
		if (cm != nullptr && ct != nullptr) {
			AABB newBox = *(cm->GetBoundingBox());
			newBox.TransformAsAABB(ct->GetGlobalTransform());
			if (root_->box_.Contains(newBox)) root_->EliminateNode(toRemove);
		}
	}
}

void CustomQuadTree::Intersect(std::vector<GameObject*>& toTest, const Frustum& camFrustum)
{
	if (root_ != nullptr) root_->NodeIntersect(toTest, camFrustum);
}

void CustomQuadTree::Intersect(std::vector<GameObject*>& toTest, const Ray& ray)
{
	if (root_ != nullptr) root_->NodeIntersect(toTest, ray);
}



void CustomQuadTree::DrawBox()
{
	if (root_ != nullptr) root_->DrawNodeBox();
}


//----------------------------- NODE FUNCTIONS ---------------------------------

CustomQuadTreeNode::CustomQuadTreeNode()
{

}

CustomQuadTreeNode::CustomQuadTreeNode(AABB box, CustomQuadTreeNode* parent) : box_(box), parent_(parent), child_nodes_()
{

}

CustomQuadTreeNode::~CustomQuadTreeNode()
{

}

void CustomQuadTreeNode::SetNodeBox(AABB box)
{
	box_ = box;
}

void CustomQuadTreeNode::SetParent(CustomQuadTreeNode* newparent)
{
	parent_ = newparent;
}

void  CustomQuadTreeNode::InsertInNode(GameObject *toInsert)
{
	if (objectsInBox_.size() < MAX_OBJECTS_IN_NODE || box_.Size().x < MINIMUM_BOX_SIZE) objectsInBox_.push_back(toInsert);
	else {
		if (child_nodes_.empty()) DivideBox();
		objectsInBox_.push_back(toInsert);
		ReallocateChilds();
	}
}
void CustomQuadTreeNode::EliminateNode(GameObject* toEliminate)
{
	list<GameObject*>::iterator it;
	bool found = false;
	for (it = objectsInBox_.begin(); it != objectsInBox_.end() && !found; ++it) {
		if (*it == toEliminate) {
			found = true;
			it = objectsInBox_.erase(it);
		}
	}
	if (!found && !child_nodes_.empty()) {
		for (int i = 0; i < 4; ++i)
		{
			if (child_nodes_[i] != nullptr) child_nodes_[i]->EliminateNode(toEliminate);
		}
	}
}

void CustomQuadTreeNode::NodeIntersect(std::vector<GameObject*>& toTest, const Frustum& camFrustum)
{
    BROFILER_CATEGORY("NodeInterSect", Profiler::Color::Red);
  	if (camFrustum.Intersects(box_)) {
		list<GameObject*>::iterator it;
		for (it = objectsInBox_.begin(); it != objectsInBox_.end(); ++it) {
			bool found = false;
			for (int i = 0; i < toTest.size(); ++i) {
				if (toTest[i] == *it) found = true;
			}
			if (!found) toTest.push_back(*it);
		}
		if (!child_nodes_.empty()) {
			  for (int i = 0; i < 4; ++i) child_nodes_[i]->NodeIntersect(toTest, camFrustum);
	    }
    }
}



void CustomQuadTreeNode::NodeIntersect(std::vector<GameObject*>& toTest, const Ray& ray)
{
	if (ray.Intersects(box_)) {
		list<GameObject*>::iterator it;
		for (it = objectsInBox_.begin(); it != objectsInBox_.end(); ++it) {
			bool found = false;
			for (int i = 0; i < toTest.size(); ++i) {
				if (toTest[i] == *it) found = true;
			}
			if (!found) toTest.push_back(*it);
		}
		if (!child_nodes_.empty()) {
			for (int i = 0; i < 4; ++i) child_nodes_[i]->NodeIntersect(toTest, ray);
		}
	}

}

void CustomQuadTreeNode::ReallocateChilds()
{
  list<GameObject*>::iterator it;
	for (it = objectsInBox_.begin(); it != objectsInBox_.end();) {
		bool boxIntersects[4];
		for (int i = 0; i < 4; ++i) {
			ComponentMesh* cm = (ComponentMesh*)(*it)->GetComponent(MESH);
			ComponentTransform* ct = (ComponentTransform*)(*it)->GetComponent(TRANSFORMATION);
			if (cm != nullptr && ct != nullptr) {
				AABB newBox = *(cm->GetBoundingBox());
				newBox.TransformAsAABB(ct->GetGlobalTransform());
				boxIntersects[i] = (child_nodes_[i]->box_.Intersects(newBox));
			}
		}
		if (boxIntersects[0] && boxIntersects[1] && boxIntersects[2] && boxIntersects[3]) ++it;
		else {
			for (int i = 0; i < 4; ++i) {
				if (boxIntersects[i]) child_nodes_[i]->InsertInNode(*it);
			}
			it = objectsInBox_.erase(it);
		}
}
}

void CustomQuadTreeNode::DivideBox()
{
	float3 maxPoints = this->box_.maxPoint;
	float3 minPoints = this->box_.minPoint;
	float3 boxSizeOffset = this->box_.HalfSize();
	AABB subBox;

	subBox.maxPoint = float3(maxPoints.x - boxSizeOffset.x, maxPoints.y, maxPoints.z - boxSizeOffset.z);
	subBox.minPoint = float3(minPoints.x, minPoints.y, minPoints.z);
	child_nodes_.push_back(new CustomQuadTreeNode(subBox, this));

	subBox.maxPoint = float3(maxPoints.x, maxPoints.y, maxPoints.z - boxSizeOffset.z);
	subBox.minPoint = float3(minPoints.x + boxSizeOffset.x, minPoints.y, minPoints.z);
	child_nodes_.push_back(new CustomQuadTreeNode(subBox, this));

	subBox.maxPoint = float3(maxPoints.x - boxSizeOffset.x, maxPoints.y, maxPoints.z);
	subBox.minPoint = float3(minPoints.x, minPoints.y, minPoints.z + boxSizeOffset.z);
	child_nodes_.push_back(new CustomQuadTreeNode(subBox, this));

	subBox.maxPoint = float3(maxPoints.x, maxPoints.y, maxPoints.z);
	subBox.minPoint = float3(minPoints.x + boxSizeOffset.x, minPoints.y, minPoints.z + boxSizeOffset.z);
	child_nodes_.push_back(new CustomQuadTreeNode(subBox, this));
}

void CustomQuadTreeNode::DrawNodeBox()
{
	float3 CornerVertex[8];
	box_.GetCornerPoints(CornerVertex);
	glLineWidth((GLfloat)3.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	//1		
	glVertex3fv((GLfloat*)&CornerVertex[0]);
	glVertex3fv((GLfloat*)&CornerVertex[4]);
	//2	
	glVertex3fv((GLfloat*)&CornerVertex[4]);
	glVertex3fv((GLfloat*)&CornerVertex[6]);
	//3		
	glVertex3fv((GLfloat*)&CornerVertex[2]);
	glVertex3fv((GLfloat*)&CornerVertex[6]);
	//4		
	glVertex3fv((GLfloat*)&CornerVertex[0]);
	glVertex3fv((GLfloat*)&CornerVertex[2]);
	//5		
	glVertex3fv((GLfloat*)&CornerVertex[4]);
	glVertex3fv((GLfloat*)&CornerVertex[5]);
	//6		
	glVertex3fv((GLfloat*)&CornerVertex[6]);
	glVertex3fv((GLfloat*)&CornerVertex[7]);
	//7		
	glVertex3fv((GLfloat*)&CornerVertex[2]);
	glVertex3fv((GLfloat*)&CornerVertex[3]);
	//8		
	glVertex3fv((GLfloat*)&CornerVertex[0]);
	glVertex3fv((GLfloat*)&CornerVertex[1]);
	//9		
	glVertex3fv((GLfloat*)&CornerVertex[1]);
	glVertex3fv((GLfloat*)&CornerVertex[5]);
	//10		
	glVertex3fv((GLfloat*)&CornerVertex[5]);
	glVertex3fv((GLfloat*)&CornerVertex[7]);
	//11		
	glVertex3fv((GLfloat*)&CornerVertex[7]);
	glVertex3fv((GLfloat*)&CornerVertex[3]);
	//12		
	glVertex3fv((GLfloat*)&CornerVertex[1]);
	glVertex3fv((GLfloat*)&CornerVertex[3]);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth((GLfloat)1.0f);
	if (!child_nodes_.empty())
	{
		for (int i = 0; i < 4; ++i) child_nodes_[i]->DrawNodeBox();
	}
}
