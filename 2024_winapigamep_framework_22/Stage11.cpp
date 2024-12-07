#include "pch.h"
#include "Stage11.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MainBG.h"
#include "Quit.h"
#include "Background.h"
#include "ResourceManager.h"
#include "StartBtn.h"

void Stage11::Init()
{
	Object* pObj = new MainBG(L"Ending", L"Texture\\Clear.bmp");
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pObj->SetSize({ 1.f,1.f });
	pObj->SetName(L"BG");
	AddObject(pObj, LAYER::BACKGROUND);

	Object* btnObj = new StartBtn(L"Main", L"Texture\\Menu.bmp", L"MainScene");
	btnObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 250 });
	btnObj->SetSize({ 2.f, 2.f });
	btnObj->SetName(L"Btn");
	AddObject(btnObj, LAYER::UI);
}
void Stage11::Update()
{
	Scene::Update();
}
