#pragma once
#include"Component.h"

class RigidBody : public Component
{
private:
    Vec2 m_vForce;
    Vec2 m_vAccel;
    Vec2 m_vVelocity;

    float m_fMass;
    float m_fMaxSpeed;
    float m_fFricCoeff;

    float m_gravity;
    bool useGravity;

public:
    RigidBody(); 
    ~RigidBody() override;
public:
    void finalUpdate();
public:
    void UseGravity(bool v) { useGravity = v; }
    void AddForce(Vec2 _vf) { m_vForce += _vf; }
    void SetMass(float _fMass) { m_fMass = _fMass; }
    float  GetMass() { return m_fMass; }
    Vec2 GetVelocity() { return m_vVelocity; }  

    void SetVelocity(Vec2 _v) { m_vVelocity = _v; } 
    void AddVelocity(Vec2 _v) { m_vVelocity += _v; } 
    void SetMaxVelocity(float _Speed) { m_fMaxSpeed = _Speed; }

    void Gravity();
private:
    void Move();

public:
    void LateUpdate() override;
    void Render(HDC _hdc) override;
};