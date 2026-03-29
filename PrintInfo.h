#ifndef PRINTINFO_H
#define PRINTINFO_H

#include <iostream>
#include "GameSetting.h"

using namespace std;

class PrintInfo
{
public:
     static void DrawChoiceInfo() {
          GameSetting::gotoXY(GameSetting::windows_width / 2 - 10, GameSetting::windows_height / 2 - 5);
          cout << "请选择游戏模式: ";

          GameSetting::gotoXY(GameSetting::windows_width / 2 - 10, GameSetting::windows_height / 2 - 3);
          cout << "1. 手动操作模式";

          GameSetting::gotoXY(GameSetting::windows_width / 2 - 10, GameSetting::windows_height / 2 - 1);
          cout << "2. 自动操作模式";

          GameSetting::gotoXY(GameSetting::windows_width / 2 - 10, GameSetting::windows_height / 2 + 1);
          cout << "请输入您的选择->";
     }

     static void DrawMap() {
          system("cls");  // 清屏
          // 第1行边框
          for(int i = 1; i <= GameSetting::windows_width; i++) cout << "-";
          cout << endl;

          // 信息栏左右边框+2-38行左右边框+中间地图空格
          for(int i = 1; i <= GameSetting::windows_height - 2; i++) {
               for(int j = 1; j <= GameSetting::windows_width; j++) {
                    if(i == 19 && j >= 61 && j <= 79) {
                         cout << "-";
                    }
                    else if(j == 1 || j == 60 || j == 80) {
                         cout << "|";
                    } else {
                         cout << " ";
                    }
               }
               cout << endl;
          }

          // 第40行
          for(int i = 1; i <= GameSetting::windows_width; i++) {
               cout << "-";
          }
     }

     static void GameOver(int score) {
          GameSetting::setColor(12, 0);

          GameSetting::gotoXY(GameSetting::windows_width / 2 - 18, GameSetting::windows_height / 2 - 2);
          cout << "游戏结束";
          GameSetting::gotoXY(GameSetting::windows_width / 2 - 18, GameSetting::windows_height / 2);
          cout << "得分: " << score;

          GameSetting::setColor(7, 0);
     }

     // 实时显示分数和速度
     static void DrawScore(int score, int speed) {
          GameSetting::gotoXY(GameSetting::windows_width - 18, 8);
          cout << "当前玩家分数: " << score;
          GameSetting::gotoXY(GameSetting::windows_width - 18, 10);
          cout << "当前玩家速度: " << 10 - speed / 25;
     }

     static void DrawGameInfo(bool model) {
          GameSetting::gotoXY(GameSetting::windows_width - 15, 26);
          if(model) cout << "模式: 手动";
          else cout << "模式: 自动";
          
          if(model) {
               GameSetting::gotoXY(GameSetting::windows_width - 15, 26);
               cout << "操作指南: ";
               GameSetting::gotoXY(GameSetting::windows_width - 17, 28);
               cout << "W: 上    S: 下";
               GameSetting::gotoXY(GameSetting::windows_width - 17, 30);
               cout << "A: 左    D: 右";
               GameSetting::gotoXY(GameSetting::windows_width - 19, 32);
               cout << "+: 加速   -: 减速";
               GameSetting::gotoXY(GameSetting::windows_width - 16, 34);
               cout << "Version 1.0 ";
          } else {
               GameSetting::gotoXY(GameSetting::windows_width - 15, 28);
               cout << "操作指南: ";
               GameSetting::gotoXY(GameSetting::windows_width - 17, 30);
               cout << "W: 上    S: 下";
               GameSetting::gotoXY(GameSetting::windows_width - 17, 32);
               cout << "A: 左    D: 右";
               GameSetting::gotoXY(GameSetting::windows_width - 16, 34);
               cout << "Version 1.0 ";
          }
     }
};

#endif
