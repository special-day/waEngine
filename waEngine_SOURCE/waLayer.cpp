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

			if (gameObj->GetState() == GameObject::eState::Dead
				|| gameObj->GetState() == GameObject::eState::Paused)
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

			if (gameObj->GetState() == GameObject::eState::Dead
				|| gameObj->GetState() == GameObject::eState::Paused)
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

			if (gameObj->GetState() == GameObject::eState::Dead
				|| gameObj->GetState() == GameObject::eState::Paused)
				continue;

			gameObj->Render(hdc);
		}
	}

	void Layer::Destroy()
	{
		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); )
		{
			GameObject::eState active = (*iter)->GetState();
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

	void Layer::AddGameObject(GameObject* gameObj)
	{
		if(gameObj == nullptr)
			return;

		mGameObjects.push_back(gameObj);
	}

	void Layer::EraseGameObject(GameObject* eraseGameObj)
	{
		// std::erase() iter 넣어줘서 해당 이터레이터와 같은 객체 삭제
		// std::erase_if() 조건이 참인 객체만
		std::erase_if(mGameObjects,
			[=](GameObject* gameObj)
			{
				return gameObj == eraseGameObj;
			});
	}
}