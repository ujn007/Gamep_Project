#include "pch.h"
#include "Stage7.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "EventManager.h"
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
#include "Teleport.h"

void Stage7::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ 100.f,550.f });
	pPlayer->SetSize({ 20.f,30.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::DOOR, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::SPINE, LAYER::PLAYER);	
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::TELEPORT, LAYER::PLAYER);	
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::SPINE, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::TELEPORT, LAYER::PLAYER_DIR_COL);	
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_DIR_COL);

	Object* pBG = new Background;
	pBG->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pBG->SetSize({ Ratio, Ratio });
	AddObject(pBG, LAYER::BACKGROUND);

	GET_SINGLE(TimeManager)->GetDT();

#pragma region Grounds
	vector<Wall*> grounds;
	for (int i = 0; i < 4; i++) {
		grounds.push_back(new Wall);
		grounds[i]->SetPos(Vec2((i+1) * 200.f + 70.f, SCREEN_HEIGHT / 2.f + 320.f));
		grounds[i]->SetSize({ 100.f, 100.f });
		grounds[i]->GetComponent<Collider>()->SetSize(grounds[i]->GetSize());
		grounds[i]->GetComponent<Collider>()->SetOwner(grounds[i]);
		grounds[i]->SetName(L"Ground");

		AddObject(grounds[i], LAYER::GROUND);
	}

	Wall* pGround = new Wall;
	pGround->SetPos({ 1170.f, SCREEN_HEIGHT / 2.f + 320.f });
	pGround->SetSize({ 300.f, 100.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	pGround = new Wall;
	pGround->SetPos({50.f, SCREEN_HEIGHT / 2.f + 320.f });
	pGround->SetSize({ 150.f, 100.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	Teleport *teleport = new Teleport;			
	teleport->SetPos({ 0.f, SCREEN_HEIGHT / 2.f + 320.f });	
	teleport->SetSize({ 50.f, 1000.f});	
	teleport->GetComponent<Collider>()->SetSize(teleport->GetSize());	
	teleport->SetTelePos({ SCREEN_WIDTH - 35.f ,  600.f});
	teleport->SetName(L"TELEPORT");				
	AddObject(teleport, LAYER::SPINE);		

#pragma endregion

	vector<Spine*> spines;
	for (int i = 0; i <= 2; i++) {
		spines.push_back(new Spine);
		spines[i]->SetPos(Vec2((i + 2) * 200.f + 70.f, SCREEN_HEIGHT / 2.f + 320.f));
		spines[i]->SetSize({ Ratio * 0.2f ,Ratio * 0.15f });
		spines[i]->GetComponent<Collider>()->SetSize({ 1.f * Ratio, 10.f * Ratio });
		spines[i]->SetchangeColliderSize({ 3.5f * Ratio, 1.f * Ratio });
		spines[i]->SetMode(TweenMode::ONCE);
		spines[i]->SetEnterPos(Vec2((i+2) * 200.f + 70.f, SCREEN_HEIGHT / 2.f + 320.f) - Vec2(0.f, 60.f));
		spines[i]->SetDuation(0.2f);
		spines[i]->GetComponent<Collider>()->SetOwner(spines[i]);

		spines[i]->SetName(L"ss" + std::to_wstring(i));

		AddObject(spines[i], LAYER::SPINE);
	}

	pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 540.f });
	pGround->SetSize({ 100.f * Ratio ,5.f * Ratio });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Die");
	AddObject(pGround, LAYER::SPINE);

	Object* pDoor = new Door;
	pDoor->SetPos({ 1100.f, 600.f });
	pDoor->SetSize({ Ratio, Ratio });
	pDoor->SetName(L"Door");
	AddObject(pDoor, LAYER::DOOR);
}

void Stage7::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ESC))
		GET_SINGLE(EventManager)->LoadScene(L"MainScene");
}
