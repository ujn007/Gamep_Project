#pragma once
#include "Scene.h"
class MainScene :
    public Scene
{
public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
};

