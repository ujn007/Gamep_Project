#pragma once
#include "Object.h"
#include <functional>
#include <vector>

struct Tween {
    Object* target;
    Vec2 startPos;
    Vec2 endPos;
    float elapsed;
    float duration;
    bool active;

    Tween(Object* target, Vec2 startPos, Vec2 endPos, float duration)
        : target(target), startPos(startPos), endPos(endPos),
        elapsed(0.0f), duration(duration), active(true) {}
};

class DotweenManager {
public:
    DECLARE_SINGLE(DotweenManager);
    void Update(float deltaTime);

    void DoMove(Object* target, Vec2 startPos, Vec2 endPos, float duration);
    void Release();

private:
    std::vector<Tween> tweens;
};