#pragma once
#include "waComponent.h"
#include "waLayer.h"
#include "waGameObject.h"
#include "waSceneManager.h"
#include "waScene.h"
#include "waTransform.h"


namespace wa::object
{
	template<typename T>
	static T* Instantiate(wa::enums::eLayerType type)
	{
		T* gameObject = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		return gameObject;
	}

	template<typename T>
	static T* Instantiate(wa::enums::eLayerType type, math::Vector2 position)
	{
		T* gameObject = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		Transform* tr = gameObject->GetComponent<wa::Transform>();
		tr->SetPosition(position);

		return gameObject;
	}

	static void Destroy(GameObject* obj)
	{
		obj->Death();
	}
}