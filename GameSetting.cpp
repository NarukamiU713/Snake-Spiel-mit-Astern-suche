#include <windows.h>
#include <cstdio>
#include <ctime>
#include "GameSetting.h"

void GameSetting::GameInit() {
     // 1. 设置窗口
     char buffer[100]; // 用来存储 Windows 命令
     // 用缓存区的数据设置游戏窗口大小
     sprintf(buffer, "mode con cols=%d lines=%d", windows_width, windows_height);
     system(buffer);

     SetConsoleOutputCP(CP_UTF8);
     SetConsoleCP(CP_UTF8);


     // 2. 隐藏光标
     HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // HANDLE = Windows 句柄，理解为对控制台的"引用"
     CONSOLE_CURSOR_INFO CursorInfo; // 创建一个结构体变量，用来存储光标信息
     GetConsoleCursorInfo(handle, &CursorInfo);
     CursorInfo.bVisible = false; // 修改光标不可见
     SetConsoleCursorInfo(handle, &CursorInfo); // 把修改后的光标信息设置回控制台
     // 3. 初始化随机数种子
     srand((unsigned int)time(0));
}

void GameSetting::gotoXY(int x, int y) {
     COORD pos = { (short)x, (short)y };
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameSetting::setColor(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + background * 16);
}