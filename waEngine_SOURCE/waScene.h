#pragma once
#include "waEntity.h"
#include "waGameObject.h"
#include "waLayer.h"
#include "waTexture.h"

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
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, const enums::eLayerType type);
		void EraseGameObject(GameObject* gameObj);
		Layer* GetLayer(const enums::eLayerType type) { return mLayers[(UINT)type]; }

		void SetColMap(graphics::Texture* colMap) { mColMap = colMap; }
		graphics::Texture* GetColMap() { return mColMap; }

	private:
		void createLayers();

	private:
		std::vector<Layer*> mLayers;
		graphics::Texture* mColMap;
	};

}

