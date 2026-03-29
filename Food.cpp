#include <iostream>
#include "Food.h"

// 食物坐标为 m_coordinate
Food::Food() {}
Food::Food(vector<COORDINATE>& Snake) {
     // 通过调用蛇身坐标引用，直接初始化食物位置
     RandomXY(Snake);
}

void Food::RandomXY(vector<COORDINATE>& Snake) {
     m_coordinate.x = rand() % (GameSetting::windows_width - 22) + 1;
     // x: 1 ~ 58
     m_coordinate.y = rand() % (GameSetting::windows_height - 2) + 1;
     // y: 1 ~ 38

     // 检查是否和蛇身重合
     for(int i = 0; i < Snake.size(); i++) {
          if(Snake[i].x == m_coordinate.x && Snake[i].y == m_coordinate.y) {
               // 如果蛇的某一节和食物重合
               m_coordinate.x = rand() % (GameSetting::windows_width - 22) + 1;
               m_coordinate.y = rand() % (GameSetting::windows_height - 2) + 1;
               
               i = -1;  // 从头开始 i++后变为0
          }
     }
}


void Food::draw_food(){
     GameSetting::setColor(12, 0);
     GameSetting::gotoXY(m_coordinate.x, m_coordinate.y);
     cout << "@";
     
     GameSetting::setColor(7, 0);  // 恢复为默认颜色(7 = 亮白色)
}

// 获取食物坐标，用于判断是否吃到食物
COORDINATE Food::GetFoodCoordinate(){
     return m_coordinate;
}
