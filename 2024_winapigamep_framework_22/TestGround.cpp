#include "pch.h"
#include "TestGround.h"
#include "Collider.h"

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
	Object::EnterCollision(_other);
	cout << "dd";
}

void TestGround::StayCollision(Collider* _other)
{
	Object::StayCollision(_other);
}

void TestGround::ExitCollision(Collider* _other)
{
	Object::ExitCollision(_other);
}
