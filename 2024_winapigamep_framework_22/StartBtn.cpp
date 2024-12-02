#include "pch.h"
#include "StartBtn.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"

StartBtn::StartBtn()
	: m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Start", L"Texture\\Start.bmp");
}
StartBtn::~StartBtn()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}

void StartBtn::Update()
{
	Vec2 pos = GetPos();
	Vec2 size = GetRect();
	Vec2 mousePos = GET_MOUSEPOS;

	if (GET_KEYDOWN(KEY_TYPE::LBUTTON)) {
		if (mousePos.x > pos.x - size.x && mousePos.x < pos.x + size.x && mousePos.y > pos.y - size.y && mousePos.y < pos.y + size.y)
			GET_SINGLE(SceneManager)->LoadScene(L"Stage1");
	}
}
void StartBtn::Render(HDC _hdc)
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
		, 0, 0, width, height, RGB(255, 255, 255));

	ComponentRender(_hdc);
}

Vec2 StartBtn::GetRect()
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	return { vSize.x * width, vSize.y * height };
}
