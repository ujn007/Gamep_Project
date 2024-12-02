#pragma once
#include "Object.h"
#include <functional>
#include <vector>

// Tween ����ü ���� (DoMove ����)
struct Tween {
    Object* target;                         // ������ Object
    Vec2 startPos;                   // ���� ��ġ
    Vec2 endPos;                       // ��ǥ ��ġ
    float elapsed;                          // ��� �ð�
    float duration;                         // ���� �ð�
    bool active;                            // Ȱ�� ����

    Tween(Object* target, Vec2 startPos, Vec2 endPos, float duration)
        : target(target), startPos(startPos), endPos(endPos),
        elapsed(0.0f), duration(duration), active(true) {}
};

// DotweenManager Ŭ����
class DotweenManager {
public:
    DECLARE_SINGLE(DotweenManager);
    // ������ ������ ��� Ʈ�� ������Ʈ
    void Update(float deltaTime);

    // DoMove �߰�
    void DoMove(Object* target, Vec2 startPos, Vec2 endPos, float duration);

private:
    std::vector<Tween> tweens;
};