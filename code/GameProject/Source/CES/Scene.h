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

	int mMaxEntities;
	int mCurrentEntities = 0;
	int* mMask;

	int mComponentCount;
	void** mComponentData;
	std::map<Hash, int> mComponentIndex;

	SystemPtr mUpdateSystems[64];
	SystemPtr mDrawSystems  [32];
	
	int mUpdateSystemCount = 0;
	int mDrawSystemCount   = 0;

	uint mCreateEntity();

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
	mComponentData[mComponentCount] = new T[mMaxEntities];

	mComponentIndex[typeid(T).hash_code()] = mComponentCount;

	++mComponentCount;
}

template<typename T>
inline T& Scene::GetComponent(int pEntity)
{
	return ( (T*)mComponentData[mComponentIndex[typeid(T).hash_code()]] )[pEntity];
}

template<typename T>
inline Mask Scene::GetMask()
{
	return 1 << mComponentIndex[typeid(T).hash_code()];
}

#endif