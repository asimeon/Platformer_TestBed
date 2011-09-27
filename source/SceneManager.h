
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>

class Scene;

typedef std::vector<Scene*> SceneVector;

class SceneManager
{
public:
	~SceneManager();

	static SceneManager* GetInstance();
	void DestroyInstance();

	void PushScene(Scene* a_pScene);
	void PopScene();
	Scene* GetCurrentScene() const { return m_vScenes.back(); }

	void Cleanup();

	void RunCurrentScene(float a_fDeltaTime);

private:
	SceneManager();

	static SceneManager* m_pInstance;
	SceneVector m_vScenes;
};

#endif // SCENEMANAGER_H
