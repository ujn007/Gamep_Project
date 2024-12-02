#include "pch.h"
#include "Define.h"
#include "RigidBody.h"
#include "Object.h"
#include "TimeManager.h"

RigidBody::RigidBody()
	:m_fMass(1.f)
	, m_fFricCoeff(200.f)
	, m_fMaxSpeed(100.f)
	, m_gravity(980 + 590.f)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::LateUpdate()
{
	Gravity();
	//std::cout << m_vVelocity.y << endl;
	float fForce = m_vForce.Length();

	if (fForce != 0.f) {
		m_vForce.Normalize();

		float m_fAccel = fForce / m_fMass;

		m_vAccel = m_vForce * m_fAccel;

		m_vVelocity += m_vAccel * fDT;

		if (!m_vVelocity.IsZero())
		{
			Vec2 vFricDir = -m_vVelocity;
			vFricDir.Normalize();

			Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
			if (m_vVelocity.Length() <= vFriction.Length())
			{
				m_vVelocity = Vec2(0.f, 0.f);
			}
			else
			{
				m_vVelocity += vFriction;
			}
		}

		if (m_fMaxSpeed < m_vVelocity.Length()) {
			m_vVelocity.Normalize();
			m_vVelocity *= m_fMaxSpeed;
		}
	}

	Move();
	m_vForce = Vec2(0.f, 0.f);
}

void RigidBody::finalUpdate()
{

}

void RigidBody::Gravity()
{
	if (useGravity == false) 
		m_vVelocity.y = 0.f;
	else
		m_vVelocity.y += m_gravity * fDT;


	/*if (m_isGrounded == true)
	{
		m_velocity.y = 0;
		return;
	}*/

}

void RigidBody::Move()
{
	float fSpeed = m_vVelocity.Length();
	Vec2 vPos = GetOwner()->GetPos();

	if (fSpeed != 0.f) {
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();
		float speed = m_vVelocity.Length();
		vPos += m_vVelocity * fDT;
	}

	GetOwner()->SetPos(vPos);
}

void RigidBody::Render(HDC _hdc)
{
}