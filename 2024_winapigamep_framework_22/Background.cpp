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
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Map", L"Texture\\Stage2.bmp");
	//this->AddComponent<Collider>();
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

	::StretchBlt(_hdc 
		, 0
		, 0
		, SCREEN_WIDTH, SCREEN_HEIGHT ,
		m_pTex->GetTexDC()
		, 0
		, 0, SCREEN_WIDTH / Ratio, SCREEN_HEIGHT / Ratio, SRCCOPY);
	ComponentRender(_hdc);
	//::StretchBlt();
	//::AlphaBlend();
	//::PlgBlt();
}