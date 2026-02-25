#include "waLayer.h"


namespace wa
{
	Layer::Layer()
		: mGameObjects{}
	{
	}
	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Initialize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->LateUpdate();
		}
	}
	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj == nullptr)
				continue;

			gameObj->Render(hdc);
		}
	}

	void Layer::Destroy()
	{
		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); )
		{
			GameObject::eState active = (*iter)->GetActive();
			if (active == GameObject::eState::Dead)
			{
				GameObject* deathObj = (*iter);
				iter = mGameObjects.erase(iter);

				delete deathObj;
				deathObj = nullptr;

				continue;
			}

			++iter;
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if(gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}
}