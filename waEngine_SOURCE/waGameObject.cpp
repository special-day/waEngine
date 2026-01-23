#include "waGameObject.h"
#include "waInput.h"

ya::GameObject::GameObject()
{
}

ya::GameObject::~GameObject()
{
}

void ya::GameObject::Update()
{
    if (Input::GetKey(eKeyCode::A))
    {
        mX -= 0.01f;
    }

    if (Input::GetKey(eKeyCode::D))
    {
        mX += 0.01f;
    }
    
    if (Input::GetKey(eKeyCode::Up))
    {
        mY -= 0.01f;
    }

    if (Input::GetKey(eKeyCode::Down))
    {
        mY += 0.01f;
    }

}

void ya::GameObject::LateUpdate()
{

}

void ya::GameObject::Render(HDC hdc)
{
    // 파랑 브러쉬 생성
    HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));

    // 파랑 브러쉬 DC에 선택 그리고 흰색 브러쉬 반환
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

    HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

    Rectangle(hdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);

    // 파랑 브러쉬 삭제
    DeleteObject(blueBrush);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(redPen);
}
