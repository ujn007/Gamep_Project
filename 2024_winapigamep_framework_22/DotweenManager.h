#pragma once
#include "Object.h"
#include <functional>
#include <vector>

// Tween 구조체 정의 (DoMove 전용)
struct Tween {
    Object* target;                         // 움직일 Object
    Vec2 startPos;                   // 시작 위치
    Vec2 endPos;                       // 목표 위치
    float elapsed;                          // 경과 시간
    float duration;                         // 지속 시간
    bool active;                            // 활성 상태

    Tween(Object* target, Vec2 startPos, Vec2 endPos, float duration)
        : target(target), startPos(startPos), endPos(endPos),
        elapsed(0.0f), duration(duration), active(true) {}
};

// DotweenManager 클래스
class DotweenManager {
public:
    DECLARE_SINGLE(DotweenManager);
    // 프레임 단위로 모든 트윈 업데이트
    void Update(float deltaTime);

    // DoMove 추가
    void DoMove(Object* target, Vec2 startPos, Vec2 endPos, float duration);

private:
    std::vector<Tween> tweens;
};