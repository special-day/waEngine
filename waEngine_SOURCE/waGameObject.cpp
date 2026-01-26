#include "waGameObject.h"
#include "waInput.h"
#include "waTime.h"

namespace wa
{

    GameObject::GameObject()
        : mX(0)
        , mY(0)
    {
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::Update()
    {
        const int speed = 100.0f;
        if (Input::GetKey(eKeyCode::A))
        {
            mX -= speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::D))
        {
            mX += speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::W))
        {
            mY -= speed * Time::DT();
        }

        if (Input::GetKey(eKeyCode::S))
        {
            mY += speed * Time::DT();
        }

    }

    void GameObject::LateUpdate()
    {

    }

    void GameObject::Render(HDC hdc)
    {
        // 파랑 브러쉬 생성
        HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));

        // 파랑 브러쉬 DC에 선택 그리고 흰색 브러쉬 반환
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

        HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        Ellipse(hdc, mX, mY, 100 + mX, 100 + mY);

        // 파랑 브러쉬 삭제
        DeleteObject(blueBrush);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(redPen);
    }
}