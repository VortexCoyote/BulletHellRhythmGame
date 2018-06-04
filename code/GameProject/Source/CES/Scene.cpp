#include "Scene.h"

Scene::Scene( int entityAmount)
	:mMaxEntities( entityAmount)
{	
	mComponentData = new void*[32];
	mMask = new int[mMaxEntities];

	for (int i = 0; i < mMaxEntities; ++i)
	{
		mMask[i] = NULL;
	}
}
Scene::~Scene()
{	
	delete[] mMask;
	delete[] mComponentData;
}


void Scene::SubmitUpdateSystem(SystemPtr system)
{
	mUpdateSystems[mUpdateSystemCount] = system;
	++mUpdateSystemCount;
}
void Scene::SubmitDrawSystem(SystemPtr system)
{
	mDrawSystems[mDrawSystemCount] = system;
	++mDrawSystemCount;
}


uint Scene::mCreateEntity()
{
	unsigned int entity;
	for (entity = 0; entity < mMaxEntities; ++entity)
	{
		if (mMask[entity] == NULL)
		{
			return(entity);
		}
	}

	printf("Error!  No more entities left!\n");

	return(mMaxEntities);
}
uint Scene::DestroyEntity(int entity)
{
	if (mMask[entity])
	{
		--mCurrentEntities;
		mMask[entity] = NULL;
	}

	return 0;
}
uint Scene::RegisterEntity(int entityMask)
{
	++mCurrentEntities;

	uint entity = mCreateEntity();

	mMask[entity] = entityMask;

	return entity;
}

uint Scene::GetMaxEntities()
{
	return mMaxEntities;
}
uint Scene::GetCurrentEntities()
{
	return mCurrentEntities;
}
uint Scene::GetEntityMask(int index)
{
	return mMask[index];
}

void Scene::Update(float deltaTime)
{
	for (int entity = 0; entity < mMaxEntities; ++entity)
	{
		for (int system = 0; system < mUpdateSystemCount; ++system)
		{
			mUpdateSystems[system](*this, entity, deltaTime);
		}
	}
}

void Scene::Draw(float deltaTime)
{
	for (int entity = 0; entity < mMaxEntities; ++entity)
	{
		for (int system = 0; system < mDrawSystemCount; ++system)
		{
			mDrawSystems[system](*this, entity, deltaTime);
		}
	}
}
