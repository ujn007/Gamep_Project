#include "pch.h"
#include "Teleport.h"
#include "Collider.h"

Teleport::Teleport()
{
	this->AddComponent<Collider>();	
}

Teleport::~Teleport()
{
}

void Teleport::Update()
{
}

void Teleport::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Teleport::EnterCollision(Collider* _other)
{
	Object* player = _other->GetOwner();

	if (player->GetName() == L"Player") {
		cout << "Tele" << endl;
		player->SetPos(m_teleportPos);	
	}
}
