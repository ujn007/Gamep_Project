#include "pch.h"
#include "Background.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"

Background::Background()
	: m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Stage2", L"Texture\\Stage2.bmp");
	this->AddComponent<Collider>();
}
Background::~Background()
{
	/*if (nullptr != m_pTex)
		delete m_pTex;*/
}
void Background::Update()
{

}

void Background::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(vPos.x - width * vSize.x / 2)
		, (int)(vPos.y - height * vSize.y / 2)
		, width * vSize.x, height * vSize.y,
		m_pTex->GetTexDC()
		, 0, 0,width, height, RGB(255,0,255));
	ComponentRender(_hdc);
	//::StretchBlt();
	//::AlphaBlend();
	//::PlgBlt();
}