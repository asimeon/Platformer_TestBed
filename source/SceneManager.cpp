
#include "SceneManager.h"
#include "Scene.h"

SceneManager* SceneManager::m_pInstance = 0;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
	if(m_pInstance == 0)
	{
		m_pInstance = new SceneManager;
	}

	return m_pInstance;
}

void SceneManager::DestroyInstance()
{
	if(m_pInstance)
	{
		Cleanup();

		delete m_pInstance;
		m_pInstance = 0;
	}
}

void SceneManager::Cleanup()
{
	SceneVector::iterator iterScene = m_vScenes.begin();
	for(; iterScene != m_vScenes.end(); ++iterScene)
	{
		Scene* pScene = *iterScene;
		delete pScene;
	}

	m_vScenes.clear();
}

void SceneManager::PushScene( Scene* a_pScene )
{
	m_vScenes.push_back(a_pScene);
}

void SceneManager::PopScene()
{
	m_vScenes.pop_back();
}

void SceneManager::RunCurrentScene(float a_fDeltaTime)
{
	GetCurrentScene()->Update(a_fDeltaTime);
	GetCurrentScene()->Render();
}
