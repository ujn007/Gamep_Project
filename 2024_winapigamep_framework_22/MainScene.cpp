#include "pch.h"
#include "MainScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MainBG.h"
#include "Quit.h"
#include "Background.h"
#include "ResourceManager.h"
#include "Btn.h"

void MainScene::Init()
{
	Object* pObj = new MainBG;
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pObj->SetSize({ 1.f,1.f });
	pObj->SetName(L"BG");
	AddObject(pObj, LAYER::BACKGROUND);

	Object* btnObj = new Btn;
	btnObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f +100});
	btnObj->SetSize({ 2.f, 2.f });
	btnObj->SetName(L"Btn");
	AddObject(btnObj, LAYER::UI);

	btnObj = new Quit;
	btnObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 200});
	btnObj->SetSize({ 2.f, 2.f });
	btnObj->SetName(L"Btn2");
	AddObject(btnObj, LAYER::UI);
}
void MainScene::Update()
{
	Scene::Update();
}
