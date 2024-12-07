#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"
#include "Stage7.h"
#include "Stage8.h"
#include "Stage9.h"
#include "Stage10.h"
#include "Stage11.h"
#include "GameScene.h"
#include "MainScene.h"
#include "DotweenManager.h"
#include "EventManager.h"
#include <string>
#include <sstream>

void SceneManager::Init()
{
	m_pCurrentScene = nullptr;

	// ¾À µî·Ï
	RegisterScene(L"Stage1", std::make_shared<Stage1>());
	RegisterScene(L"Stage2", std::make_shared<Stage2>());
	RegisterScene(L"Stage3", std::make_shared<Stage3>());
	RegisterScene(L"Stage4", std::make_shared<Stage4>());
	RegisterScene(L"Stage5", std::make_shared<Stage5>());
	RegisterScene(L"Stage6", std::make_shared<Stage6>());
	RegisterScene(L"Stage7", std::make_shared<Stage7>());
	RegisterScene(L"Stage8", std::make_shared<Stage8>());
	RegisterScene(L"Stage9", std::make_shared<Stage9>());
	RegisterScene(L"Stage10", std::make_shared<Stage10>());
	RegisterScene(L"Stage11", std::make_shared<Stage11>());
	RegisterScene(L"GameScene", std::make_shared<GameScene>());
	RegisterScene(L"MainScene", std::make_shared<MainScene>());

	// ¾À ·Îµå
	LoadScene(L"Stage8");
}

void SceneManager::Update()
{
	if (m_pCurrentScene == nullptr) return;
	m_pCurrentScene->Update();
	if (m_pCurrentScene == nullptr) return;
	m_pCurrentScene->LateUpdate();
}

void SceneManager::Render(HDC _hdc)
{
	if (m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Render(_hdc);
}

void SceneManager::RegisterScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene)
{
	if (_sceneName.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), { _sceneName, _scene });
}

void SceneManager::LoadScene(const wstring& _sceneName)
{
	// ¾ÀÀÌ ÀÖÀ¸¸é
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->Release();
		GET_SINGLE(DotweenManager)->Release();
		m_currentSceneName = _sceneName;
		m_pCurrentScene = nullptr;
	}

	auto iter = m_mapScenes.find(_sceneName);
	if (iter != m_mapScenes.end())
	{
		m_pCurrentScene = iter->second;
		m_pCurrentScene->Init();
	}
}

void SceneManager::LoadNextScene()
{
	GET_SINGLE(EventManager)->LoadScene(GetNextSceneName(GetCurrentSceneName()));
}

wstring SceneManager::GetNextSceneName(const wstring& _sceneName)
{
	if (!_sceneName.empty()) {
		std::string str(_sceneName.begin(), _sceneName.end());

		if (isdigit(str.back())) {
			int number = str.back() - '0' + 1;

			str.pop_back();
			str += std::to_string(number);
		}

		return std::wstring(str.begin(), str.end());
	}
	return L"";
}
