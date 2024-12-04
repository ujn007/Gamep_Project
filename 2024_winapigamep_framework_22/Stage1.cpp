#include "pch.h"
#include "Stage1.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Enemy.h"
#include "Spine.h"
#include "Door.h"
#include "Wall.h"
#include "TestGround.h"
#include "Background.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "DotweenManager.h"
#include "Collider.h"
#include "Test.h"

void Stage1::Init()
{ 
	Object* pPlayer = new Player;
	pPlayer->SetPos({ 100.f, 0.f });
	pPlayer->SetSize({ 30.f,30.f });
	pPlayer->SetName(L"Player");	
	AddObject(pPlayer, LAYER::PLAYER);

	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BACKGROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
	//GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//GET_SINGLE(ResourceManager)->Play(L"BGM");

	Object* pBG = new Background;
	pBG->SetPos({ SCREEN_WIDTH  / 2.f, SCREEN_HEIGHT / 2.f });
	pBG->SetSize({Ratio, Ratio });
	AddObject(pBG, LAYER::BACKGROUND);

	GET_SINGLE(TimeManager)->GetDT();

	/*vector<Vec2> spinePos;
	spinePos.push_back({ 400.f, 600.f });
	spinePos.push_back({ 500.f, 600.f });
	spinePos.push_back({ 600.f, 600.f });
	spinePos.push_back({ 700.f, 600.f });

	vector<Object*> spines;
	for (int i = 0; i < spinePos.size(); i++) {
		spines.push_back(new Spine);
		spines[i]->SetPos(spinePos[i]);
		spines[i]->SetSize({Ratio,Ratio});


		AddObject(spines[i], LAYER::PROJECTILE);
	}*/

	Wall* pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 340.f });
	pGround->SetSize({ 1280.f , 100.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	Object* pGround1 = new Wall;
	pGround1->SetPos({500.f, SCREEN_HEIGHT / 2.f + 300.f });
	pGround1->SetSize({ 500.f , 100.f });
	pGround1->GetComponent<Collider>()->SetSize(pGround1->GetSize());
	pGround1->SetName(L"Ground");
	AddObject(pGround1, LAYER::GROUND);

	/*Object* pGround1 = new Wall;
	pGround1->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 400.f });
	pGround1->SetSize({ 50.f ,5.f });
	pGround1->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround1->SetName(L"Ground");
	AddObject(pGround1, LAYER::GROUND);*/

	//Object* test = new Test;
	//test->SetPos({0.f, 633.703f });
	//test->SetSize({1.f ,1.f });		
	//test->SetName(L"Test");	
	//AddObject(test, LAYER::ENEMY);	

	Object* pDoor = new Door;
	pDoor->SetPos({ 1100.f, 600.f });
	pDoor->SetSize({ Ratio, Ratio });
	pDoor->SetName(L"Door");
	AddObject(pDoor, LAYER::GROUND);
}

void Stage1::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadNextScene();
}
