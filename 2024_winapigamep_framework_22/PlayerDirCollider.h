#pragma once
#include "Object.h"
#include "RigidBody.h"
#include "Player.h"
class PlayerDirCollider :
	public Object
{
public:
	PlayerDirCollider();
	~PlayerDirCollider();
public:
	virtual void Update();
	virtual void Render(HDC _hdc);
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther) override;
public:
	void SetCollider(DIR state, Vec2 scale, Vec2 offset);
	void SetOwner(Player* player) { m_pOwner = player; }
private:
	void BlockCheck(Object* pOtherObj);
	void BlockCheckOut();
private:
	DIR m_eState;
	Player* m_pOwner;
	RigidBody* rigid;
};