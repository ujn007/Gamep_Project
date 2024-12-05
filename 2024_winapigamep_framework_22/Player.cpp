#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"
#include "PlayerDirCollider.h"
#include "CollisionManager.h"

Player::Player()
	: m_pTex(nullptr)
	, isJump(false)
	, isGround(false)
	, currentAnim(ANIM::IDLE_RIGHT)
	, currentCol(COLDIR::DOWN)
	, isLeftCollision(false)
	, isRightCollision(false)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"PlayerAnim", L"Texture\\PlayerAnim.bmp");
	this->AddComponent<Collider>();
	AddComponent<RigidBody>();
	AddComponent<Animator>();
	GetComponent<Collider>()->SetSize({ 20.f, 30.f });

	rigid = GetComponent<RigidBody>();
	rigid->UseGravity(true);

#pragma region DIRCol
	PlayerDirCollider* m_pDirLeftCol = new PlayerDirCollider;
	m_pDirLeftCol->SetOwner(this);
	m_pDirLeftCol->SetCollider(DIR::LEFT, { 5.f, 25.f }, { -9.5f, 0.f });

	PlayerDirCollider* m_pDirRightCol = new PlayerDirCollider;
	m_pDirRightCol->SetOwner(this);
	m_pDirRightCol->SetCollider(DIR::RIGHT, { 5.f, 25.f }, { 9.5f, 0.f });

	PlayerDirCollider* m_pDirTopCol = new PlayerDirCollider;
	m_pDirTopCol->SetOwner(this);
	m_pDirTopCol->SetCollider(DIR::TOP, { 20.f, 1.f }, { 0.f, -18.f });

	PlayerDirCollider* m_pDirBottomCol = new PlayerDirCollider;
	m_pDirBottomCol->SetOwner(this);
	m_pDirBottomCol->SetCollider(DIR::BOTTOM, { 20.f, 1.f }, { 0.f, 18.f }); 

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(m_pDirLeftCol, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(m_pDirRightCol, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(m_pDirTopCol, LAYER::PLAYER_DIR_COL);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(m_pDirBottomCol, LAYER::PLAYER_DIR_COL);

#pragma endregion
#pragma region Animation
	float size = 32.f;
	float leftFlip = size * 8;
	GetComponent<Animator>()->CreateAnimation(L"Player_Idle_Right", m_pTex, Vec2(0.f, 0.f),
		Vec2(size, size), Vec2(size, 0.f), 2, 0.5f);
	GetComponent<Animator>()->CreateAnimation(L"Player_Idle_Left", m_pTex, Vec2(leftFlip, 0.f),
		Vec2(size, size), Vec2(size, 0.f), 2, 0.5f);
	GetComponent<Animator>()->CreateAnimation(L"Player_run_Right", m_pTex, Vec2(0.f, size * 3),
		Vec2(size, size), Vec2(size, 0.f), 8, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Player_run_Left", m_pTex, Vec2(leftFlip, size * 3),
		Vec2(size, size), Vec2(size, 0.f), 8, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Player_jump_Right", m_pTex, Vec2(size * 2, size * 5),
		Vec2(size, size), Vec2(size, 0.f), 1, 1);
	GetComponent<Animator>()->CreateAnimation(L"Player_jump_Left", m_pTex, Vec2(leftFlip + (size * 2), size * 5),
		Vec2(size, size), Vec2(size, 0.f), 1, 1);
	GetComponent<Animator>()->CreateAnimation(L"Player_fall_Right", m_pTex, Vec2((size * 4), size * 5),
		Vec2(size, size), Vec2(size, 0.f), 1, 1);
	GetComponent<Animator>()->CreateAnimation(L"Player_fall_Left", m_pTex, Vec2(leftFlip + (size * 4), size * 5),
		Vec2(size, size), Vec2(size, 0.f), 1, 1);
	GetComponent<Animator>()->PlayAnimation(L"Player_Idle_Right", true);
#pragma endregion


	GET_SINGLE(ResourceManager)->LoadSound(L"Jump", L"Sound\\Jump.wav", false);
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	HandleMovement(); 
	HandleAnimation();
}

void Player::HandleMovement()
{
	Vec2 velocity = rigid->GetVelocity();

	if (GET_KEY(KEY_TYPE::A) && 0 + 10 < GetPos().x && !isLeftCollision) {
		velocity.x = -250.f;
		isFacingRight = false;
	}
	else if (GET_KEY(KEY_TYPE::D) && SCREEN_WIDTH - 10 > GetPos().x && !isRightCollision) {
		velocity.x = 250.f;
		isFacingRight = true;
	}
	else {
		velocity.x = 0.f;
	}

	if (GET_KEYDOWN(KEY_TYPE::SPACE) && isGround) {
		isGround = false;
		rigid->UseGravity(true);
		velocity.y = -400.f;

		GET_SINGLE(ResourceManager)->Play(L"Jump");
	}

	rigid->SetVelocity(velocity);
}

void Player::HandleAnimation()
{
	ANIM targetAnim = ANIM::IDLE_RIGHT;

	if (!isGround) {
		if (rigid->GetVelocity().y <= 0) {
			targetAnim = isFacingRight ? ANIM::JUMP_RIGHT : ANIM::JUMP_LEFT;
		}
		else if (rigid->GetVelocity().y > 0) {
			targetAnim = isFacingRight ? ANIM::FALL_RIGHT : ANIM::FALL_LEFT;
		}
	}
	else if (rigid->GetVelocity().x < 0 && !rigid->IsStopMoveLeft()) {
		targetAnim = ANIM::RUN_LEFT;	
	}
	else if (rigid->GetVelocity().x > 0 && !rigid->IsStopMoveRight()) {
		targetAnim = ANIM::RUN_RIGHT;	
	}
	else {
		targetAnim = isFacingRight ? ANIM::IDLE_RIGHT : ANIM::IDLE_LEFT;
	}
	if (currentAnim != targetAnim) {
		currentAnim = targetAnim;

		switch (currentAnim) {
		case ANIM::RUN_LEFT:
			GetComponent<Animator>()->PlayAnimation(L"Player_run_Left", true);
			break;
		case ANIM::RUN_RIGHT:
			GetComponent<Animator>()->PlayAnimation(L"Player_run_Right", true);
			break;
		case ANIM::IDLE_LEFT:
			GetComponent<Animator>()->PlayAnimation(L"Player_Idle_Left", true);
			break;
		case ANIM::IDLE_RIGHT:
			GetComponent<Animator>()->PlayAnimation(L"Player_Idle_Right", true);
			break;
		case ANIM::JUMP_LEFT:
			GetComponent<Animator>()->PlayAnimation(L"Player_jump_Left", false);
			break;
		case ANIM::JUMP_RIGHT:
			GetComponent<Animator>()->PlayAnimation(L"Player_jump_Right", false);
			break;
		case ANIM::FALL_LEFT:
			GetComponent<Animator>()->PlayAnimation(L"Player_fall_Left", false);
			break;
		case ANIM::FALL_RIGHT:
			GetComponent<Animator>()->PlayAnimation(L"Player_fall_Right", false);
			break;
		}
	}
}

void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	ComponentRender(_hdc);
}

void Player::EnterCollision(Collider* _other)
{
	Object* obj = _other->GetOwner();

	if (obj->GetName() == L"Door") {
		GET_SINGLE(SceneManager)->LoadNextScene();
	}
}
