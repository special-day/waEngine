#pragma once
#include "waEntity.h"
#include "waGameObject.h"
#include "waLayer.h"

namespace wa
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObject, const eLayerType type);

	private:
		std::vector<Layer*> mLayers;
	};

}

