#ifndef HEADER_SCENE
#define HEADER_SCENE

#include <map>
#include <iostream>

#include <stdlib.h>

#include "..\Game\Game.h"

class Scene;
typedef void(*SystemPtr)(Scene& scene, int entity, float deltaTime);
typedef unsigned int Mask;
typedef unsigned int uint;
typedef unsigned int Hash;

#define SYSTEM(name) void name (Scene& scene, int entity, float deltaTime)
#define ENTITY(mask) (scene.GetEntityMask(entity) & mask) == mask

class Scene
{

	int m_maxEntities;
	int m_currentEntities = 0;
	int* m_mask;

	int m_componentCount;
	void** m_componentData;
	std::map<Hash, int> m_componentIndex;

	SystemPtr m_updateSystems[64];
	SystemPtr m_drawSystems  [32];
	
	int m_updateSystemCount = 0;
	int m_drawSystemCount   = 0;

	uint m_CreateEntity();

public:
	
	Scene(int entityAmount);
	~Scene();

	template <typename T>
	void SubmitComponent();

	template <typename T>
	T& GetComponent(int entity);

	template <typename T>
	Mask GetMask();


	void SubmitUpdateSystem(SystemPtr system);
	void SubmitDrawSystem(SystemPtr system);


	uint DestroyEntity(int entity);
	uint RegisterEntity(int entityMask);

	uint GetMaxEntities();
	uint GetCurrentEntities();
	uint GetEntityMask(int index);

	void Update(float deltaTime);
	void Draw(float deltaTime);

};

template<typename T>
inline void Scene::SubmitComponent()
{
	m_componentData[m_componentCount] = new T[m_maxEntities];

	m_componentIndex[typeid(T).hash_code()] = m_componentCount;

	++m_componentCount;
}

template<typename T>
inline T& Scene::GetComponent(int entity)
{
	return ( (T*)m_componentData[m_componentIndex[typeid(T).hash_code()]] )[entity];
}

template<typename T>
inline Mask Scene::GetMask()
{
	return 1 << m_componentIndex[typeid(T).hash_code()];
}

#endif