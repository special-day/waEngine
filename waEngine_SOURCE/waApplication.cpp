#include "waApplication.h"
#include "waInput.h"

ya::Application::Application()
    : mHwnd(nullptr)
    , mHdc(nullptr)
{
}

ya::Application::~Application()
{
}

void ya::Application::Initialize(HWND hwnd)
{
	mHwnd = hwnd;
	mHdc = GetDC(hwnd);

    mPlayer.SetPosition(0, 0);
   //  mObj.SetPosition(0, 0);

    Input::Initialize();
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
    mPlayer.Update();
    // mObj.Update();
}

void ya::Application::LateUpdate()
{
}

void ya::Application::Render()
{
    mPlayer.Render(mHdc);
    // mObj.Render(mHdc);

    // 기본으로 자주 사용되는 GDI 오브젝트를 미리 DC 안에 만들어 두었는데
    // 그 오브젝트들을 스톡 오브젝트라고 한다.

    // DC란 화면에 출력에 필요한 모든 정보를 가지는 데이터 구조체이며
    // GDI 모듈에 의해서 관리된다.
    // 어떤 폰트를 사용할 것인가? 어떤 선의 굵기를 정해줄 것인지? 어떤 색상으로 그려줄 것인지?
    // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행할 수 있다.
}
