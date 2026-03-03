#include "waGameObject.h"
#include "waInput.h"
#include "waTime.h" 
#include "waTransform.h"

namespace wa::object
{
    void Destory(GameObject* gameObject)
    {
        if (gameObject != nullptr)
            gameObject->death();
    }
}

namespace wa
{

    GameObject::GameObject()
        : mState(eState::Active)
        , mLayerType(eLayerType::None)
    {
        mComponents.resize((UINT)enums::eComponentType::End);
		initializeTransform();
    }

    GameObject::~GameObject()
    {
        for(Component* comp : mComponents)
        {
            delete comp;
            comp = nullptr;
		}
    }

    void GameObject::Initialize()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
                continue;

			comp->Initialize();
        }
	}

    void GameObject::Update()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
                continue;

            comp->Update();
        }
    }

    void GameObject::LateUpdate()
    {
        for (Component* comp : mComponents)
        {
            if (comp == nullptr)
                continue;

            comp->LateUpdate();
        }
    }

    void GameObject::Render(HDC hdc)
    {
        for(Component* comp : mComponents)
        {
            if (comp == nullptr)
                continue;

            comp->Render(hdc);
		}
    }

    void GameObject::initializeTransform()
    {
        AddComponent<Transform>();
    }
}