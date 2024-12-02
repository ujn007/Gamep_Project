#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Projectile.h"
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
	GetComponent<Animator>()->CreateAnimation(L"Player_Idle_Right", m_pTex, Vec2(0.f, 0.f),
		Vec2(size, size), Vec2(size, 0.f), 2, 0.5f, true);
	GetComponent<Animator>()->PlayAnimation(L"Player_Idle_Right", true);

}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	cout << GetPos().x << endl;
	if (GET_KEY(KEY_TYPE::A) && 0< GetPos().x)
		rigid->SetVelocity(Vec2(-250.f, rigid->GetVelocity().y));
	else if (GET_KEY(KEY_TYPE::D) && SCREEN_WIDTH - 202 > GetPos().x)
		rigid->SetVelocity(Vec2(250.f, rigid->GetVelocity().y));
	else
		rigid->SetVelocity(Vec2(0.f, rigid->GetVelocity().y));

	if (GET_KEYDOWN(KEY_TYPE::SPACE) && isGround) {
		isGround = false;
		rigid->UseGravity(true);
		rigid->SetVelocity(Vec2(rigid->GetVelocity().x, -500.f));
	}

	if (GET_KEYDOWN(KEY_TYPE::F)) {
		Object* player = rigid->GetOwner();
		cout << player->GetPos().x << " " << player->GetPos().y << endl;
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

	if (obj->GetName() == L"Ground") {
		isGround = true;
		rigid->UseGravity(false);
		float groundPos = obj->GetPos().y - (obj->GetSize().y / 2);		
		player->SetPos(Vec2(player->GetPos().x, groundPos));		
	}
}

void Player::StayCollision(Collider* _other)
{

}

void Player::ExitCollision(Collider* _other)
{
}
