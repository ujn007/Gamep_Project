#include "pch.h"
#include "Door.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "EventManager.h"
#include "DotweenManager.h"

Door::Door()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Door", L"Texture\\Door.bmp");
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 1.f, 2.f });
	GetComponent<Collider>()->SetOffSetPos({ 0.f, 0.5f });
}

Door::~Door()
{
}

void Door::Update()
{

}

void Door::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//ELLIPSE_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::TransparentBlt(_hdc
		, (int)(vPos.x - width * vSize.x / 2)
		, (int)(vPos.y - height * vSize.y / 2)
		, width * vSize.x, height * vSize.y,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 255, 255));
	ComponentRender(_hdc);
}

void Door::EnterCollision(Collider* _other)
{
	
}

void Door::StayCollision(Collider* _other)
{
}

void Door::ExitCollision(Collider* _other)
{
}
