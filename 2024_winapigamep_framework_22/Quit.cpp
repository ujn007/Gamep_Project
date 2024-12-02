#include "pch.h"
#include "Quit.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "InputManager.h"

Quit::Quit()
	: m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Quit", L"Texture\\Quit.bmp");
}
Quit::~Quit()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}

void Quit::Update()
{
	Vec2 pos2 = GetPos();
	Vec2 size2 = GetRect();
	Vec2 mousePos = GET_MOUSEPOS;

	if (GET_KEYDOWN(KEY_TYPE::LBUTTON)) {
		if (mousePos.x > pos2.x - size2.x && mousePos.x < pos2.x + size2.x && mousePos.y > pos2.y - size2.y && mousePos.y < pos2.y + size2.y)
			PostQuitMessage(0);
	}
}
void Quit::Render(HDC _hdc)
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

Vec2 Quit::GetRect()
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	return { vSize.x * width, vSize.y * height };
}
