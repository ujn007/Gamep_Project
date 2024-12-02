#include "pch.h"
#include "TestGround.h"
#include "Collider.h"
#include "Rigidbody.h"

TestGround::TestGround()
{
	this->AddComponent<Collider>();
}

TestGround::~TestGround()
{
}

void TestGround::Update()
{
}

void TestGround::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = 1280;
	int height = 100;
	ComponentRender(_hdc);
}

void TestGround::EnterCollision(Collider* _other)
{
	
}

void TestGround::SetCollider(Object* owner, Vec2 scale, Vec2 offset)
{
	/*m_pOwner = owner;

	Collider* col = GetCollider();
	col->SetSize(scale);
	col->SetOffSetPos(offset);*/
}

void TestGround::StayCollision(Collider* _other)
{
  
}

void TestGround::ExitCollision(Collider* _other)
{
   
}
