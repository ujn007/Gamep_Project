#include "pch.h"
#include "Wall.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "EventManager.h"
#include "DotweenManager.h"

Wall::Wall()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Wall", L"Texture\\Wall.bmp");
	this->AddComponent<Collider>();
	enterMove = false;
}

Wall::~Wall()
{
}

void Wall::Update()
{

}

void Wall::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//ELLIPSE_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::StretchBlt(_hdc
		, (vPos.x - width * vSize.x * 6.7f)
		, (vPos.y - height * vSize.y * 6.7f)
		, vSize.x * Ratio, vSize.y * Ratio,
		m_pTex->GetTexDC()
		, 0
		, 0, 
		width, height, SRCCOPY);
	ComponentRender(_hdc);
}
void Wall::SetCollider(Object* owner, Vec2 scale, Vec2 offset)
{

}

void Wall::EnterCollision(Collider* _other)
{
	if(enterMove)
		GET_SINGLE(DotweenManager)->DoMove(this, GetPos(), enterPos, 1.f);
}

void Wall::StayCollision(Collider* _other)
{

}

void Wall::ExitCollision(Collider* _other)
{

}
