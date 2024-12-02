#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "Background.h"
#include "TestGround.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Collider.h"
void TitleScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	//GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//GET_SINGLE(ResourceManager)->Play(L"BGM");

	TestGround* pGround = new TestGround;
	pGround->SetPos(Vec2(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 200.f));
	pGround->SetSize(Vec2(SCREEN_WIDTH * 1.f, 80.f));
	pGround->GetComponent<Collider>()->SetSize(Vec2(SCREEN_WIDTH * 1.f, 50.f));	
	pGround->SetName(L"Ground");
	AddObject(pGround, LAYER::GROUND);

	TestGround* pWall = new TestGround;
	pWall->SetPos(Vec2(SCREEN_WIDTH - 300.f, SCREEN_HEIGHT /2.f));
	pWall->SetSize(Vec2(200.f, 1080.f));
	pWall->GetComponent<Collider>()->SetSize(Vec2(200.f, 1080.f));
	pWall->SetName(L"Wall");
	AddObject(pWall, LAYER::Wall);	
}

void TitleScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}
