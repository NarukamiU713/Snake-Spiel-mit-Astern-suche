#ifndef GAMESETTING_H
#define GAMESETTING_H

#include <iostream>

class GameSetting
{
public:
     // 游戏窗口的长宽
     static const int windows_height = 40;
     static const int windows_width = 80;
public:
     static void GameInit();
     static void gotoXY(int x, int y);
     static void setColor(int foreground, int background);
}; 

struct COORDINATE {
    int x;
    int y;
};

#endif
