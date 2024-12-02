#include "pch.h"
#include "DotweenManager.h"
#include "Object.h"
#include <algorithm>

// 트윈 업데이트
void DotweenManager::Update(float deltaTime) {
    for (auto& tween : tweens) {
        if (!tween.active) continue;

        tween.elapsed += deltaTime;
        float t = tween.elapsed / tween.duration;
        if (t > 1.0f) t = 1.0f;

        // LERP를 사용하여 Object의 위치 갱신
        if (tween.target) {
            float newX = (1 - t) * tween.startPos.x + t * tween.endPos.x;
            float newY = (1 - t) * tween.startPos.y + t * tween.endPos.y;
            tween.target->SetPos({ newX, newY });
        }

        // 애니메이션 완료 체크
        if (t >= 1.0f) {
            tween.active = false;
        }
    }

    // 완료된 트윈 제거
    tweens.erase(
        std::remove_if(tweens.begin(), tweens.end(), [](const Tween& tween) { return !tween.active; }),
        tweens.end()
    );
}

// DoMove 트윈 추가
void DotweenManager::DoMove(Object* target, Vec2 startPos, Vec2 endPos, float duration) {
    tweens.emplace_back(target, startPos, endPos, duration);
}