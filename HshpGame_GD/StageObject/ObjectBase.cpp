#include "ObjectBase.h"

ObjectBase::ObjectBase() :
	m_hObjectImg(-1),
	m_IsExist(false)
{
}

void ObjectBase::Init()
{
}

void ObjectBase::SetPos()
{
}

void ObjectBase::Update()
{
}

void ObjectBase::Draw()
{
}

bool ObjectBase::CollisionCheck(float X, float Y)
{
	return false;
}
