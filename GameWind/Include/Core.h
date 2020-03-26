#pragma once
//第一步:包含头文件
//第二步:引用项目
//第三步:输出目录修改

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容

//宏定义到导出函数
#ifndef AL_BUILD_DLL
#define AL_BUILD_DLL
#define AHLIN_API __declspec(dllexport)
#else
#define AHLIN_API __declspec(dllimport)
#endif // AL_BUILD_DLL

// Windows 头文件
#include <windows.h>

#define WIDTH 800
#define HEIGHT 600

//鼠标按键枚举
enum BUTTON_KEY
{
    L_BUTTON_DOWN = 0,
    L_BUTTON_UP = 1,
    R_BUTTON_DOWN = 2,
    R_BUTTON_UP = 3,

    KB_DOWN = 4,
    KB_UP = 5,
};