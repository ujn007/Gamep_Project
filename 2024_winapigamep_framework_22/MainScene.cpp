#include "pch.h"
#include "MainScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MainBG.h"
#include "Background.h"
#include "ResourceManager.h"
#include "StartBtn.h"

void MainScene::Init()
{
	Object* pObj = new MainBG;
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pObj->SetSize({ 10000.f,10000.f });
	pObj->SetName(L"BG");
	AddObject(pObj, LAYER::BACKGROUND);

	Object* btnObj = new StartBtn;
	btnObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	btnObj->SetSize({ 2.f, 2.f });
	btnObj->SetName(L"Btn");
	AddObject(btnObj, LAYER::UI);
}
void MainScene::Update()
{
	Scene::Update();
	StartBtn* btn = dynamic_cast<StartBtn*>(GetLayerObjects(LAYER::UI)[0]);

	Vec2 pos = btn->GetPos();
	Vec2 size = btn->GetRect();
	Vec2 mousePos = GET_MOUSEPOS;
	if (GET_KEYDOWN(KEY_TYPE::LBUTTON)) {
		Vec2 mousePos = GET_MOUSEPOS;
		if(mousePos.x > pos.x - size.x && mousePos.x < pos.x + size.x && mousePos.y > pos.y - size.y && mousePos.y < pos.y + size.y)
			GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}
}
