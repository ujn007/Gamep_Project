#include "pch.h"
#include "DotweenManager.h"
#include "Object.h"
#include <algorithm>

// Ʈ�� ������Ʈ
void DotweenManager::Update(float deltaTime) {
    for (auto& tween : tweens) {
        if (!tween.active) continue;

        tween.elapsed += deltaTime;
        float t = tween.elapsed / tween.duration;
        if (t > 1.0f) t = 1.0f;

        // LERP�� ����Ͽ� Object�� ��ġ ����
        if (tween.target) {
            float newX = (1 - t) * tween.startPos.x + t * tween.endPos.x;
            float newY = (1 - t) * tween.startPos.y + t * tween.endPos.y;
            tween.target->SetPos({ newX, newY });
        }

        // �ִϸ��̼� �Ϸ� üũ
        if (t >= 1.0f) {
            tween.active = false;
        }
    }

    // �Ϸ�� Ʈ�� ����
    tweens.erase(
        std::remove_if(tweens.begin(), tweens.end(), [](const Tween& tween) { return !tween.active; }),
        tweens.end()
    );
}

// DoMove Ʈ�� �߰�
void DotweenManager::DoMove(Object* target, Vec2 startPos, Vec2 endPos, float duration) {
    tweens.emplace_back(target, startPos, endPos, duration);
}