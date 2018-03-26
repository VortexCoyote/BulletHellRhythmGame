#include "Scene.h"

Scene::Scene( int entityAmount)
	:m_maxEntities( entityAmount)
{	
	m_componentData = new void*[32];
	m_mask = new int[m_maxEntities];

	for (int i = 0; i < m_maxEntities; ++i)
	{
		m_mask[i] = NULL;
	}
}
Scene::~Scene()
{	
	delete[] m_mask;
	delete[] m_componentData;
}


void Scene::SubmitUpdateSystem(SystemPtr system)
{
	m_updateSystems[m_updateSystemCount] = system;
	++m_updateSystemCount;
}
void Scene::SubmitDrawSystem(SystemPtr system)
{
	m_drawSystems[m_drawSystemCount] = system;
	++m_drawSystemCount;
}


uint Scene::m_CreateEntity()
{
	unsigned int entity;
	for (entity = 0; entity < m_maxEntities; ++entity)
	{
		if (m_mask[entity] == NULL)
		{
			return(entity);
		}
	}

	printf("Error!  No more entities left!\n");

	return(m_maxEntities);
}
uint Scene::DestroyEntity(int entity)
{
	if (m_mask[entity])
	{
		--m_currentEntities;
		m_mask[entity] = NULL;
	}

	return 0;
}
uint Scene::RegisterEntity(int entityMask)
{
	++m_currentEntities;

	uint entity = m_CreateEntity();

	m_mask[entity] = entityMask;

	return entity;
}

uint Scene::GetMaxEntities()
{
	return m_maxEntities;
}
uint Scene::GetCurrentEntities()
{
	return m_currentEntities;
}
uint Scene::GetEntityMask(int index)
{
	return m_mask[index];
}

void Scene::Update(float deltaTime)
{
	for (int entity = 0; entity < m_maxEntities; ++entity)
	{
		for (int system = 0; system < m_updateSystemCount; ++system)
		{
			m_updateSystems[system](*this, entity, deltaTime);
		}
	}
}
void Scene::Draw(float deltaTime)
{
	for (int entity = 0; entity < m_maxEntities; ++entity)
	{
		for (int system = 0; system < m_drawSystemCount; ++system)
		{
			m_drawSystems[system](*this, entity, deltaTime);
		}
	}
}
