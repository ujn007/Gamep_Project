#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "GameScene.h"
#include "MainScene.h"
#include <string>
#include <sstream>

void SceneManager::Init()
{
	m_pCurrentScene = nullptr;

	// �� ���
	RegisterScene(L"Stage1",std::make_shared<Stage1>());
	RegisterScene(L"Stage2",std::make_shared<Stage2>());
	RegisterScene(L"Stage3",std::make_shared<Stage3>());
	RegisterScene(L"GameScene",std::make_shared<GameScene>());
	RegisterScene(L"MainScene",std::make_shared<MainScene>());

	// �� �ε�
	LoadScene(L"MainScene");
}

void SceneManager::Update()
{
	if (m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Update();
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
	m_mapScenes.insert(m_mapScenes.end(), {_sceneName, _scene});
}

void SceneManager::LoadScene(const wstring& _sceneName)
{
	// ���� ������
	if (m_pCurrentScene != nullptr)               
	{
		m_pCurrentScene->Release();
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
	LoadScene(GetNextSceneName(GetCurrentSceneName()));	
}

void SceneManager::TESTSCENE()
{
	m_pCurrentScene->Release();	
	m_pCurrentScene->Init();	
}

wstring SceneManager::GetNextSceneName(const wstring& _sceneName)
{
	if (!_sceneName.empty()) {
		// wstring -> string ��ȯ 
		std::string str(_sceneName.begin(), _sceneName.end());

		// ������ ���ڰ� �������� Ȯ��
		if (isdigit(str.back())) {
			// ���ڷ� ��ȯ �� 1 ���ϱ�
			int number = str.back() - '0' + 1;

			// ������ ���� ���� �� �� ���� �߰�
			str.pop_back();
			str += std::to_string(number);
		}

		// ��� ���
		return std::wstring(str.begin(), str.end());
	}
	return L"";
}
