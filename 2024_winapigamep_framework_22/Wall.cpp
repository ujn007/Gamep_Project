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
	enterMove = TweenMode::NONE;
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
	//cout << "Render : " << vPos.x - width * vSize.x * 6.7f << endl;

	/*::BitBlt(_hdc
		, (vPos.x - width * vSize.x)
		, (vPos.y - height * vSize.y)
		, vSize.x, vSize.y
		, m_pTex->GetTexDC()
		, 0, 0
		, SRCCOPY
	);*/
	::StretchBlt(_hdc
		, vPos.x - (vSize.x / 2.f)
		, vPos.y - (vSize.y / 2.f)
		, vSize.x, vSize.y
		, m_pTex->GetTexDC()
		, 0
		, 0
		, width, height, SRCCOPY);
	ComponentRender(_hdc);
}
void Wall::SetCollider(Object* owner, Vec2 scale, Vec2 offset)
{

}

void Wall::EnterCollision(Collider* _other)
{
	switch (enterMove)
	{
	case TweenMode::NONE:
		break;
	case TweenMode::ONCE:
		GET_SINGLE(DotweenManager)->DoMove(this, GetPos(), enterPos, 1.f);
		enterMove = TweenMode::NONE;
		break;
	case TweenMode::EVERYTIME:
		GET_SINGLE(DotweenManager)->DoMove(this, GetPos(), enterPos, 1.f);
		break;
	default:
		break;
	}
}

void Wall::StayCollision(Collider* _other)
{

}

void Wall::ExitCollision(Collider* _other)
{

}
