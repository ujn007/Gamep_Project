#include "pch.h"
#include "Stage3.h"
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

void Stage3::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ 100.f,500.f });
	pPlayer->SetSize({ 30.f,30.f });
	pPlayer->SetName(L"Player");
	pPlayer->GetComponent<Collider>()->SetOwner(pPlayer);
	AddObject(pPlayer, LAYER::PLAYER);

	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BACKGROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::SPINE, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::DOOR, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_DIR_COL);
	//GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//GET_SINGLE(ResourceManager)->Play(L"BGM");

	Object* pBG = new Background;
	pBG->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pBG->SetSize({ Ratio, Ratio });
	AddObject(pBG, LAYER::BACKGROUND);

	GET_SINGLE(TimeManager)->GetDT();

	vector<Vec2> spinePos;
	spinePos.push_back({ 600.f, SCREEN_HEIGHT / 2.f + 265.f });
	spinePos.push_back({ 400.f, SCREEN_HEIGHT / 2.f + 265.f });

	vector<Object*> spines;
	for (int i = 0; i < spinePos.size(); i++) {
		spines.push_back(new Spine);
		spines[i]->SetPos(spinePos[i]);
		spines[i]->SetSize({Ratio * 0.15f ,Ratio * 0.15f});
		spines[i]->GetComponent<Collider>()->SetOwner(spines[i]);

		spines[i]->SetName(L"Die" + std::to_wstring(i));

		AddObject(spines[i], LAYER::SPINE);
	}

	Wall* pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 320.f });
	pGround->SetSize({ 1280.f , 100.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	 Wall* pFall = new Wall;
	 pFall->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 540.f });	
	 pFall->SetSize({ 100.f * Ratio ,5.f * Ratio });	
	 pFall->GetComponent<Collider>()->SetSize(pFall->GetSize());	
	 pFall->SetName(L"Die");	
	AddObject(pFall, LAYER::SPINE);	

	Object* pDoor = new Door;
	pDoor->SetPos({ 1100.f, 600.f });
	pDoor->SetSize({ Ratio, Ratio });
	pDoor->SetName(L"Door");
	AddObject(pDoor, LAYER::DOOR);
}

void Stage3::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadNextScene();
}
