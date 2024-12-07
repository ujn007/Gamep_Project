#include "pch.h"
#include "Stage8.h"
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

void Stage8::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ 100.f,500.f });
	pPlayer->SetSize({ 30.f,30.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::SPINE, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::TRAP, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::DOOR, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::SPINE, LAYER::PLAYER);

	Object* pBG = new Background;
	pBG->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pBG->SetSize({ Ratio, Ratio });
	AddObject(pBG, LAYER::BACKGROUND);

	GET_SINGLE(TimeManager)->GetDT();

	Wall* pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f + 320.f });
	pGround->SetSize({ 1280.f  , 100.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	vector<int> index = { 0, 0, 2, 0, 4, 0, 0, 7, 0, 9, 0, 11, 0, 0, 14, 0, 16, 0, 0, 0, 20 };
	vector<Spine*> spines;		
	for (int i = 0; i < 20; i++) {	
		spines.push_back(new Spine);	
		spines[i]->SetPos(Vec2((4+index[i]) * 45.f, SCREEN_HEIGHT / 2.f + 320.f));	
		spines[i]->SetSize({ Ratio * 0.1f ,Ratio * 0.15f });		
		spines[i]->GetComponent<Collider>()->SetSize({ 1.5f * Ratio, 10.f * Ratio });
		spines[i]->SetchangeColliderSize({ 1.5f * Ratio, 1.f * Ratio });	
		spines[i]->SetMode(TweenMode::ONCE);	
		spines[i]->SetEnterPos(Vec2(( 4 + index[i]) * 45.f, SCREEN_HEIGHT / 2.f + 320.f) - Vec2(0.f, 60.f));	
		spines[i]->SetDuation(0.05f);	
		spines[i]->GetComponent<Collider>()->SetOwner(spines[i]);	

		spines[i]->SetName(L"ss" + std::to_wstring(i));	
				
		AddObject(spines[i], LAYER::SPINE);	
	}

	Object* pDoor = new Door;
	pDoor->SetPos({ 1100.f, 600.f });
	pDoor->SetSize({ Ratio, Ratio });
	pDoor->SetName(L"Door");
	AddObject(pDoor, LAYER::DOOR);
}

void Stage8::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadNextScene();
}
