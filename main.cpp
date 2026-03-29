#include <iostream>
#include <windows.h>
#include <conio.h>
#include "GameSetting.h"
#include "Food.h"
#include "Snake.h"
#include "PrintInfo.h"

using namespace std;

int main()
{
     GameSetting::GameInit(); // 设置窗口大小、隐藏光标、初始化随机数种子
     PrintInfo::DrawChoiceInfo(); // 打印选择界面
     bool model;
     
     char ch = _getch();
     switch (ch)
     {
          case '1':
          model = true;  // 设置模式为手动
          break;
          
          case '2':
          model = false;  // 设置模式为自动
          break;

          default:
          model = true;
          break;
     }
     
     PrintInfo::DrawMap(); 
     PrintInfo::DrawGameInfo(model); 

     Snake snake(model); // 初始化3节蛇身 棋盘数组 默认方向 模式
     snake.draw_snake();
     Food food(snake.m_coordinate); // 初始化食物坐标
     food.draw_food();
     
     int score = 0;
     int speed = 225;

     while(1) { 
          snake.move_snake(food);
          if(!snake.snake_is_alive()) break;
          
          snake.draw_snake();
          snake.clear_snake();
          
          if(snake.is_eat_food(food)) {
               score++;
               speed -= 25;
               food.draw_food();
          }

          speed -= snake.GetDiffSpeed();
          if(speed > 250) speed = 250;
          else if(speed <= 0) speed = 25;

          PrintInfo::DrawScore(score, speed);
          Sleep(speed);
     }
     PrintInfo::GameOver(score);

     GameSetting::gotoXY(0, GameSetting::windows_height - 1);
     while (_kbhit()) _getch();   // 清掉残留输入
     _getch();                    // 等重新按一次就结束

     return 0;
}