#pragma once
#include "waEntity.h"
#include "commonInclude.h"
#include "waGameObject.h"

namespace wa
{
	class Layer : public Entity
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Destroy();

		void AddGameObject(GameObject* gameObj);
		void EraseGameObject(GameObject* eraseGameObj);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }

	private:


	private:
		// eLayerType mType;
		std::vector<GameObject*> mGameObjects;

	};
}

