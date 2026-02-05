#include "waGameObject.h"
#include "waInput.h"
#include "waTime.h" 
#include "waTransform.h"

namespace wa
{

    GameObject::GameObject()
    {
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
			comp->Initialize();
        }
	}

    void GameObject::Update()
    {
        for (Component* comp : mComponents)
        {
            comp->Update();
        }
    }

    void GameObject::LateUpdate()
    {
        for (Component* comp : mComponents)
        {
            comp->LateUpdate();
        }
    }

    void GameObject::Render(HDC hdc)
    {
        for(Component* comp : mComponents)
        {
            comp->Render(hdc);
		}
    }

    void GameObject::initializeTransform()
    {
        AddComponent<Transform>();
    }
}