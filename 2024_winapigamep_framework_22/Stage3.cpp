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
	AddObject(pPlayer, LAYER::PLAYER);

	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BACKGROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::PLAYER);
	//GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//GET_SINGLE(ResourceManager)->Play(L"BGM");

	Object* pBG = new Background;
	pBG->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pBG->SetSize({ Ratio, Ratio });
	AddObject(pBG, LAYER::BACKGROUND);

	GET_SINGLE(TimeManager)->GetDT();

	vector<Vec2> spinePos;
	spinePos.push_back({ 400.f, SCREEN_HEIGHT / 2.f + 340.f });
	spinePos.push_back({ 500.f, SCREEN_HEIGHT / 2.f + 340.f });
	spinePos.push_back({ 600.f, SCREEN_HEIGHT / 2.f + 340.f });
	spinePos.push_back({ 700.f, SCREEN_HEIGHT / 2.f + 340.f });

	vector<Object*> spines;
	for (int i = 0; i < spinePos.size(); i++) {
		spines.push_back(new Spine);
		spines[i]->SetPos(spinePos[i]);
		spines[i]->SetSize({Ratio,Ratio});


		AddObject(spines[i], LAYER::PROJECTILE);
	}

	Wall* pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f - 450.f, SCREEN_HEIGHT / 2.f + 340.f });
	pGround->SetSize({ 50.f ,5.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f + 550.f, SCREEN_HEIGHT / 2.f + 340.f });
	pGround->SetSize({ 15.f ,5.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Ground2");
	AddObject(pGround, LAYER::GROUND);

	pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 540.f });
	pGround->SetSize({ 100.f ,5.f });
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	pGround->SetName(L"Die");
	AddObject(pGround, LAYER::GROUND);

	pGround = new Wall;
	pGround->SetPos({ SCREEN_WIDTH / 2.f + 300.f, SCREEN_HEIGHT / 2.f + 340.f });
	pGround->SetSize({ 5.5f ,5.f });
	pGround->SetEnterPos({ SCREEN_WIDTH / 2.f + 300.f, SCREEN_HEIGHT / 2.f + 640.f });
	pGround->SetMove(true);
	pGround->GetComponent<Collider>()->SetSize({ 7.f ,7.f });
	pGround->SetName(L"Trab");
	AddObject(pGround, LAYER::GROUND);

	Object* pDoor = new Door;
	pDoor->SetPos({ 1100.f, 600.f });
	pDoor->SetSize({ Ratio, Ratio });
	pDoor->SetName(L"Door");
	AddObject(pDoor, LAYER::GROUND);
}

void Stage3::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadNextScene();
}