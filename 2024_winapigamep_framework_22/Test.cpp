#include "pch.h"
#include "Test.h"
#include "Collider.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"

Test::Test()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"jiwoo", L"Texture\\jiwoo.bmp");
	this->AddComponent<Collider>();
}

Test::~Test()
{
}

void Test::Update()
{
}

void Test::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::BitBlt(_hdc,
		vPos.x, vPos.y,
		width, height,
		m_pTex->GetTexDC(),
		0, 0, SRCCOPY);
	ComponentRender(_hdc);
}
