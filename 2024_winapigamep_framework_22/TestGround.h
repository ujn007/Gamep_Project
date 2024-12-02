#pragma once
#include"Object.h"

class TestGround : public Object
{
public:
	TestGround();
	~TestGround();
public:
	// Object��(��) ���� ��ӵ�
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other)override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;

public:	
	void SetCollider(Object* owner, Vec2 scale, Vec2 offset);

private:
	Object* m_pOwner;
};

