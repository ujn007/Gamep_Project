#include "pch.h"
#include "PlayerDirCollider.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Object.h"
#include "Scene.h"

PlayerDirCollider::PlayerDirCollider()
	: m_pOwner(nullptr)
	, m_eState(DIR::TOP)
{
	this->AddComponent<Collider>();
	//rigid = m_pOwner->GetRigid();
	SetName(L"DIRCOL");
}

PlayerDirCollider::~PlayerDirCollider()
{
}

void PlayerDirCollider::Update()
{
	if (m_pOwner == nullptr)
		return;

	SetPos(m_pOwner->GetPos()); // 플레이어 위치로 이동
}

void PlayerDirCollider::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void PlayerDirCollider::EnterCollision(Collider* _pOther)
{
	Object* pOtherObj = _pOther->GetOwner();
	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"Ground")
		BlockCheck(pOtherObj);

	if (m_eState == DIR::BOTTOM && objName == L"DamageObject")
	{
		//m_pOwner->Die();
	}
}

void PlayerDirCollider::ExitCollision(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetOwner();

	wstring objName = pOtherObj->GetName();
	// Block
	if (objName == L"Block" || objName == L"Ground" || objName == L"FallingBlock")
		BlockCheckOut();

	// DamageAndJumpAbleObject
}

void PlayerDirCollider::SetCollider(DIR state, Vec2 scale, Vec2 offset)
{
	Collider* col = GetComponent<Collider>();
	col->SetSize(scale);
	col->SetOffSetPos(offset);

	m_eState = state;

	if (m_eState == DIR::BOTTOM)
		SetName(L"DIR_BOTTOM_COL");
}

void PlayerDirCollider::BlockCheck(Object* obj)
{
	Vec2 velo = m_pOwner->GetRigid()->GetVelocity();

	switch (m_eState)
	{
	case DIR::LEFT: // 조건 체크 후 스탑 x
		m_pOwner->GetRigid()->StopMoveLeft(true); // 스탑 레프트 무브	
		break;
	case DIR::TOP: // 스탑 Y
		if (velo.y < 0)
			m_pOwner->GetRigid()->StopVeloY();
		break;
	case DIR::RIGHT: // 조건 체크 후 스탑 x
		m_pOwner->GetRigid()->StopMoveRight(true); // 스탑 라이트 무브
		break;
	case DIR::BOTTOM: // 스탑 Y하고 그라운드 체킹해주기
		if (velo.y > 0)
		{
			m_pOwner->SetIsGround(true);
			m_pOwner->GetRigid()->StopVeloY();
			m_pOwner->GetRigid()->UseGravity(false);

			float groundUp = (obj->GetPos().y - (obj->GetSize().y * Ratio / 2.f));
			float playerDown = (m_pOwner->GetPos().y + m_pOwner->GetSize().y / 2);
			float newPos = groundUp - playerDown;

			if (newPos > 0)
				m_pOwner->SetPos(Vec2(m_pOwner->GetPos().x, m_pOwner->GetPos().y - newPos));
		}

		break;
	default:
		break;
	}
}

void PlayerDirCollider::BlockCheckOut()
{
	Vec2 velo = m_pOwner->GetRigid()->GetVelocity();

	if (m_eState == DIR::BOTTOM)
	{
		m_pOwner->SetIsGround(false);
		m_pOwner->GetRigid()->UseGravity(true);
	}
	else if (m_eState == DIR::LEFT || m_eState == DIR::RIGHT)
	{
		m_pOwner->GetRigid()->StopMoveLeft(false);
		m_pOwner->GetRigid()->StopMoveRight(false);
	}


}
