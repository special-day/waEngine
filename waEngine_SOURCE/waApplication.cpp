#include "waApplication.h"
#include "waInput.h"
#include "waTime.h"

ya::Application::Application()
    : mHwnd(nullptr)
    , mHdc(nullptr)
    , mWidth(0)
    , mHeight(0)
    , mBackHdc(NULL)
    , mBackBitmap(NULL)
{
}

ya::Application::~Application()
{
}

void ya::Application::Initialize(HWND hwnd, UINT width, UINT height)
{
	mHwnd = hwnd;
	mHdc = GetDC(hwnd);

    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, WS_OVERLAPPED, false);

    mWidth = rect.right - rect.left;
    mHeight = rect.bottom - rect.top;

    SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);
    ShowWindow(mHwnd, true);

    // 윈도우 해상도에 맞는 백버퍼(도화지) 생성
    mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

    // 백버퍼를 가리킬 DC 생성
    mBackHdc = CreateCompatibleDC(mHdc);

    HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
    DeleteObject(oldBitmap);

    mPlayer.SetPosition(0, 0);
   //  mObj.SetPosition(0, 0);

    Input::Initialize();
    Time::Initialize();
}

void ya::Application::Run()
{
	Update();
	LateUpdate();
	Render();
}

void ya::Application::Update()
{
    Input::Update();
    Time::Update();
    mPlayer.Update();
    // mObj.Update();
}

void ya::Application::LateUpdate()
{
}

void ya::Application::Render()
{
    Rectangle(mBackHdc, 0, 0, 1600, 900);

    Time::Render(mBackHdc);
    mPlayer.Render(mBackHdc);
    
    // BackBuffer에 있는 걸 원본 Buffer로 복사
    BitBlt(mHdc, 0, 0, mWidth, mHeight
        , mBackHdc, 0, 0, SRCCOPY);






    // mObj.Render(mHdc);

    // 기본으로 자주 사용되는 GDI 오브젝트를 미리 DC 안에 만들어 두었는데
    // 그 오브젝트들을 스톡 오브젝트라고 한다.

    // DC란 화면에 출력에 필요한 모든 정보를 가지는 데이터 구조체이며
    // GDI 모듈에 의해서 관리된다.
    // 어떤 폰트를 사용할 것인가? 어떤 선의 굵기를 정해줄 것인지? 어떤 색상으로 그려줄 것인지?
    // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행할 수 있다.
}
