#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Enemy.h"
#include "Spine.h"
#include "TestGround.h"
#include "Background.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "DotweenManager.h"
#include "Collider.h"

void TitleScene::Init()
{ 
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,100.f });
	pPlayer->SetSize({ 100.f,100.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
	//GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//GET_SINGLE(ResourceManager)->Play(L"BGM");

	Object* pBG = new Background;
	pBG->SetPos({ SCREEN_WIDTH  / 2.f, SCREEN_HEIGHT / 2.f });
	pBG->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
	AddObject(pBG, LAYER::BACKGROUND);

	/*vector<Vec2> spinePos;
	spinePos.push_back({ 400.f, SCREEN_HEIGHT / 2.f });
	spinePos.push_back({ 500.f, SCREEN_HEIGHT / 2.f });
	spinePos.push_back({ 600.f, SCREEN_HEIGHT / 2.f });
	spinePos.push_back({ 600.f, SCREEN_HEIGHT / 2.f });

	GET_SINGLE(TimeManager)->GetDT();

	vector<Object*> spines;
	for (int i = 0; i < spinePos.size(); i++) {
		spines.push_back(new Spine);
		spines[i]->SetPos(spinePos[i]);
		spines[i]->SetSize({Ratio,Ratio});


		AddObject(spines[i], LAYER::PROJECTILE);
	}*/

	Object* pGround = new TestGround;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT -50.f});	
	pGround->SetSize({ SCREEN_WIDTH * 1.f ,50.f });	
	pGround->GetComponent<Collider>()->SetSize({ SCREEN_WIDTH * 1.f, 50.f });
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);
}

void TitleScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}
