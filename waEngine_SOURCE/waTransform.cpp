#include "waTransform.h"
#include "waInput.h"
#include "waTime.h"

namespace wa
{
	Transform::Transform()
		: mPosition(0.0f, 0.0f)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
		const float speed = 100.0f;
        if (Input::GetKey(eKeyCode::A))
        {
            mPosition.x -= speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::D))
        {
			mPosition.x += speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::W))
        {
			mPosition.y -= speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::S))
        {
			mPosition.y += speed * Time::DT();
        }
	}
	void Transform::LateUpdate()
	{
	}
	void Transform::Render(HDC hdc)
	{
	}
}