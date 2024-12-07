#include "pch.h"
#include "Stage5.h"
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

void Stage5::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ 100.f,620.f });
	pPlayer->SetSize({ 30.f,30.f });
	pPlayer->SetName(L"Player");
	pPlayer->GetComponent<Collider>()->SetOwner(pPlayer);
	AddObject(pPlayer, LAYER::PLAYER);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::SPINE, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::DOOR, LAYER::PLAYER);	
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::SPINE, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER_DIR_COL);

	Object* pBG = new Background;
	pBG->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pBG->SetSize({ Ratio, Ratio });
	AddObject(pBG, LAYER::BACKGROUND);

	GET_SINGLE(TimeManager)->GetDT();

	vector<Vec2> spinePos;
	spinePos.push_back({ 600.f, SCREEN_HEIGHT / 2.f + 265.f });
	spinePos.push_back({ 400.f, SCREEN_HEIGHT / 2.f + 265.f });
	spinePos.push_back({ 800.f, SCREEN_HEIGHT / 2.f + 365.f });

	vector<Spine*> spines;
	for (int i = 0; i < spinePos.size()-1; i++) {
		spines.push_back(new Spine);
		spines[i]->SetPos(spinePos[i]);
		spines[i]->SetSize({ Ratio * 0.15f ,Ratio * 0.15f });
		spines[i]->GetComponent<Collider>()->SetSize({ 8.f * Ratio, 2.f * Ratio });
		spines[i]->SetchangeColliderSize({ 2.f * Ratio, 1.f * Ratio });
		spines[i]->SetMode(TweenMode::ONCE);
		spines[i]->SetEnterPos(spinePos[i] - Vec2(60.f, 0.f));
		spines[i]->GetComponent<Collider>()->SetOwner(spines[i]);

		spines[i]->SetName(L"ss" + std::to_wstring(i));

		AddObject(spines[i], LAYER::SPINE);
	}
	spines.push_back(new Spine);
	spines[2]->SetPos(spinePos[2]);
	spines[2]->SetSize({ Ratio * 0.15f ,Ratio * 0.15f });
	spines[2]->GetComponent<Collider>()->SetSize({ 6.f * Ratio, 40.f * Ratio });
	spines[2]->SetchangeColliderSize({ 2.f * Ratio, 1.f * Ratio });
	spines[2]->SetMode(TweenMode::ONCE);
	spines[2]->SetEnterPos(spinePos[2] - Vec2(0.f, 100.f));
	spines[2]->GetComponent<Collider>()->SetOwner(spines[2]);

	spines[2]->SetName(L"ss" + std::to_wstring(2));

	AddObject(spines[2], LAYER::SPINE);

	Wall* pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 320.f });
	pGround->SetSize({ 1280.f , 100.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 540.f });
	pGround->SetSize({ 100.f * Ratio ,5.f * Ratio });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Die");
	AddObject(pGround, LAYER::GROUND);


	Object* pDoor = new Door;
	pDoor->SetPos({ 1100.f, 600.f });
	pDoor->SetSize({ Ratio, Ratio });
	pDoor->SetName(L"Door");
	AddObject(pDoor, LAYER::DOOR);
}

void Stage5::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadNextScene();
}
