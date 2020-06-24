#pragma once
#include "Core.h"

/*+-------------------------------------------------
 *| <GameWind> 窗口管理类
 *| 2020/1/19
 *+-------------------------------------------------
 */

class AHLIN_API GameWind {
public:
    HWND mHwnd;
    RECT wcRect;//窗口位置
    RECT clientRect;//客户去矩形
    POINT mMouse;

    //按键函数指针
    bool (*KeyBoard)(char key, BUTTON_KEY bk);
    //鼠标按键函数指针
    bool (*keyMouse)(int x, int y, BUTTON_KEY bk);

    int mWidth;//宽
    int mHeight;//高
private:
    bool isShow;
    HINSTANCE mhInstance = nullptr;
    const wchar_t* mWndClassName;
public:
    GameWind(HINSTANCE hInstacne, int width, int height, const wchar_t* wndClassName);
    GameWind(const GameWind& wnd);
    ~GameWind();
    void ShowWind();
    bool ProcessMessage();
    void ShowMessageBox(const wchar_t* title, const wchar_t* msg);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

AHLIN_API GameWind* windCreate(HINSTANCE hInstance, int width, int hegiht, const wchar_t* wndClassName = L"GameWind v1.0.0");
AHLIN_API void safeDelete();
