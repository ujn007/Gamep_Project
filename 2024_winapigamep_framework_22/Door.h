#pragma once
#include "Object.h"
class Texture;
class Door : public Object
{
public:
	Door();
	~Door();
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	Texture* m_pTex;
};

