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
Player::Player()
	: m_pTex(nullptr)
	, isJump(false)
	, isGround(false)
	, currentAnim(ANIM::IDLE_RIGHT)
	, currentCol(COLDIR::DOWN)
	, isLeftCollision(false)
	, isRightCollision(false)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path);
	//m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\planem.bmp");
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"PlayerAnim", L"Texture\\PlayerAnim.bmp");
	this->AddComponent<Collider>();
	AddComponent<RigidBody>();
	AddComponent<Animator>();

	rigid = GetComponent<RigidBody>();
	rigid->UseGravity(true);

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

	GET_SINGLE(ResourceManager)->LoadSound(L"Jump", L"Sound\\Jump.wav", false);
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	HandleMovement();   // 이동 처리
	HandleAnimation();  // 애니메이션 처리
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

	// 점프 처리
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

	// 이동 상태에 따른 애니메이션 선택
	if (!isGround) {
		if (rigid->GetVelocity().y <= 0) {
			targetAnim = isFacingRight ? ANIM::JUMP_RIGHT : ANIM::JUMP_LEFT;
		}
		else if (rigid->GetVelocity().y > 0) {
			targetAnim = isFacingRight ? ANIM::FALL_RIGHT : ANIM::FALL_LEFT;
		}
	}
	else if (rigid->GetVelocity().x < 0) {
		targetAnim = ANIM::RUN_LEFT;
	}
	else if (rigid->GetVelocity().x > 0) {
		targetAnim = ANIM::RUN_RIGHT;
	}
	else {
		targetAnim = isFacingRight ? ANIM::IDLE_RIGHT : ANIM::IDLE_LEFT;
	}
	// 애니메이션 변경 시에만 호출
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
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	//::BitBlt(_hdc
	//	, (int)(vPos.x - vSize.x / 2)
	//	, (int)(vPos.y - vSize.y / 2)
	//	, width, height,
	//	m_pTex->GetTexDC()
	//	,0,0,SRCCOPY
	//);
	/*::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0,width, height, RGB(255,0,255));*/
	ComponentRender(_hdc);
	//::StretchBlt();
	//::AlphaBlend();
	//::PlgBlt();
}

void Player::EnterCollision(Collider* _other)
{
	Object* obj = _other->GetOwner();
	Object* player = rigid->GetOwner();

	Vec2 playerTopLeft = player->GetDirPos(DIR::UP_LEFT);
	Vec2 playerBottomRight = player->GetDirPos(DIR::DOWN_RIGHT);

	Vec2 objTopLeft = obj->GetDirPos(DIR::UP_LEFT);
	Vec2 objBottomRight = obj->GetDirPos(DIR::DOWN_RIGHT);
	cout << objTopLeft.y << " " << playerBottomRight.y << endl;
	if (obj->GetName() == L"Ground") {
		if (playerBottomRight.y >= objTopLeft.y && playerTopLeft.y < objTopLeft.y) {
			cout << "DOWN" << endl;
			currentCol = COLDIR::DOWN;
			isGround = true;
			rigid->UseGravity(false);
			float newPos = objTopLeft.y - playerBottomRight.y;
			if (newPos < 0) 
				player->SetPos(Vec2(player->GetPos().x, player->GetPos().y + newPos + 1.f));
		}

		if (playerTopLeft.y <= objBottomRight.y && playerBottomRight.y > objBottomRight.y) {
			cout << "UP" << endl;
			currentCol = COLDIR::UP;
			rigid->SetVelocity({ rigid->GetVelocity().x, 0.f });
			float newPos = objTopLeft.y - playerBottomRight.y;
			if (newPos > 0)
				player->SetPos(Vec2(player->GetPos().x, player->GetPos().y + newPos));
		}

		if (playerBottomRight.x >= objTopLeft.x - 2.f && playerTopLeft.x < objTopLeft.x) {	
			cout << "RIGHT" << endl;
			currentCol = COLDIR::RIGHT;
			isRightCollision = true;
		}

		if (playerTopLeft.x <= objBottomRight.x && playerBottomRight.x > objBottomRight.x) {
			cout << "LEFT" << endl;
			currentCol = COLDIR::LEFT;	
			isLeftCollision = true;
		}
	}
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
	Object* obj = _other->GetOwner();

	if (obj->GetName() == L"Ground" ) {
		switch (currentCol)
		{
		case COLDIR::UP:
			break;
		case COLDIR::DOWN:
			rigid->UseGravity(true);
			break;
		case COLDIR::LEFT:
			isLeftCollision = false;	
			break;	
		case COLDIR::RIGHT:
			isRightCollision = false;	
			break;
		default:
			break;
		}
	}
}
