#include "pch.h"
#include "Spine.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "EventManager.h"
#include "DotweenManager.h"

Spine::Spine()
//	: m_dir(-1.f)
	: m_angle(0.f)
	, m_vDir(1.f, 1.f)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\Bullet.bmp";
	//m_pTex->Load(path);
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Spine", L"Texture\\Spine.bmp");
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetOwner(this);
	GetComponent<Collider>()->SetSize({ 2.f * Ratio, 1.f * Ratio });
	enterMove = TweenMode::NONE;
}

Spine::~Spine()
{
}

void Spine::Update()
{
	
}

void Spine::Render(HDC _hdc)
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
		, 0, 0, width, height, RGB(255, 0, 255));
	ComponentRender(_hdc);
}

void Spine::EnterCollision(Collider* _other)
{
	static int hash = 0;
	switch (enterMove)
	{
	case TweenMode::NONE:
		break;
	case TweenMode::ONCE:
		GET_SINGLE(DotweenManager)->DoMove(this, GetPos(), enterPos, 1.f);
		enterMove = TweenMode::NONE;
		GetComponent<Collider>()->SetSize(changeColliderSize);
		SetName(L"Die" + std::to_wstring(hash));
		hash++;
		break;
	case TweenMode::EVERYTIME:
		GET_SINGLE(DotweenManager)->DoMove(this, GetPos(), enterPos, 1.f);
		SetName(L"Die" + std::to_wstring(hash));
		hash++;
		break;
	default:
		break;
	}
}

void Spine::StayCollision(Collider* _other)
{
}

void Spine::ExitCollision(Collider* _other)
{
}
