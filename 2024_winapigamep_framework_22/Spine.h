#pragma once
#include "Object.h"
class Texture;
class Spine : public Object
{
public:
	Spine();
	~Spine();
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetAngle(float _f)
	{
		m_angle = _f;
	}
	void SetDir(Vec2 _dir)
	{
		m_vDir = _dir;
		m_vDir.Normalize();
	}
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
	void SetEnterPos(Vec2 pos) { enterPos = pos; }
	void SetMode(TweenMode value) { enterMove = value; }
	void SetchangeColliderSize(Vec2 value) { changeColliderSize = value; }
	void SetDuation(float v) { m_duration = v; }	
private:
	float m_duration;
	//float m_dir;
	float m_angle;
	Vec2 m_vDir;
	Texture* m_pTex;
	Vec2 enterPos;
	Vec2 changeColliderSize;
	TweenMode enterMove;
};

