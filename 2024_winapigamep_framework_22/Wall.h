	#pragma once
	#include "Object.h"
	#include "pch.h"
	class Texture;
	class Wall : public Object
	{
	public:
		Wall();
		~Wall();
		void Update() override;
		void Render(HDC _hdc) override;
		void EnterCollision(Collider* _other)override;
		void StayCollision(Collider* _other) override;
		void ExitCollision(Collider* _other) override;
	public:
		void SetCollider(Object* owner, Vec2 scale, Vec2 offset);
		void SetEnterPos(Vec2 pos) { enterPos = pos; }
		void SetMode(TweenMode value) { enterMove = value; }
		void SetchangeColliderSize(Vec2 value) { changeColliderSize = value; }
	private:
		Texture* m_pTex;
		Vec2 enterPos;
		Vec2 changeColliderSize;
		TweenMode enterMove;
	};