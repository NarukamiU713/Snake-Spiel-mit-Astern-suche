#include <iostream>
#include <string.h>
#include "Snake.h"

Snake::Snake (bool model) : m_model(model) { // 初始化列表 默认手动
     // 1. 初始化地图大小
     map_size.x = GameSetting::windows_width - 20;
     map_size.y = GameSetting::windows_height;

     // 2. 初始化移动方向和生命状态
     m_dir = UP;
     m_diff_speed = 0;
     m_is_alive = true;

     // 3. 初始化蛇身（3节）
     COORDINATE snake_head;
     snake_head.x = (GameSetting::windows_width - 20) / 2;
     snake_head.y = GameSetting::windows_height / 2;
     
     // 添加三节蛇头身
     m_coordinate.push_back(snake_head); snake_head.y++;
     m_coordinate.push_back(snake_head); snake_head.y++;
     m_coordinate.push_back(snake_head);
}

void Snake::listen_keyboard() {
     if(_kbhit()) { // 如果有键按下
          char ch = _getch();
          switch (ch) 
          {
          case 'W':
          case 'w':
               // 如果当前向下，按W无效
               if(m_dir != DOWN) m_dir = UP;
               break;
          
          case 'S':
          case 's':
               if(m_dir != UP) m_dir = DOWN;
               break;

          case 'A':
          case 'a':
               if(m_dir != RIGHT) m_dir = LEFT;
               break;
               
          case 'D':
          case 'd':
               if(m_dir != LEFT) m_dir = RIGHT;
               break;

          case '+':
               m_diff_speed += 25;
               break;

          case '-':
               m_diff_speed -= 25;
               break;
          }

     }
}

void Snake::build_chess() {
     // 初始化棋盘 for AI（将所有位置设为无障碍）
     memset(m_chess, false, sizeof(m_chess));
     // 标记棋盘边缘
     for(int i = 0; i < GameSetting::windows_width - 20; i++) {
          m_chess[i][0] = true;
          m_chess[i][GameSetting::windows_height - 1] = true;
     }
     for(int j = 0; j < GameSetting::windows_height; j++) {
          m_chess[0][j] = true;
          m_chess[GameSetting::windows_width - 21][j] = true;
     }

     // 标记蛇身
     for(unsigned int i = 0; i < m_coordinate.size(); i++) {
          m_chess[m_coordinate[i].x][m_coordinate[i].y] = true;
     }

     COORDINATE head = m_coordinate[0];
     m_chess[head.x][head.y] = false;
}

void Snake::AI_search(Food& f) {
     build_chess();
     m_astar.InitBlock(m_chess);

     COORDINATE start = m_coordinate[0];
     COORDINATE goal = f.GetFoodCoordinate();
     int next_dir = m_astar.GetNextDir(start, goal);
     if(next_dir != 0) {
          m_dir = next_dir;
     }
}

void Snake::move_snake(Food& f) {
     // 1. 监听键盘得到更新的 m_dir
     if(m_model) {
          listen_keyboard();
     } else {
          AI_search(f);
     }

     // 2. 获取蛇头坐标
     COORDINATE head = m_coordinate[0];
     switch (m_dir)
     {
     case UP:
          head.y--;
          break;
     case DOWN:
          head.y++;
          break;
     case LEFT:
          head.x--;
          break;
     case RIGHT:
          head.x++;
          break;
     }

     m_coordinate.insert(m_coordinate.begin(), head);
     /*
     每次移动都先插入新蛇头，让蛇往前走
     如果吃到食物，就不删除蛇尾 → 蛇变长
     如果没吃到，就删除蛇尾 → 蛇长度不变
     */
}

bool Snake::is_eat_food(Food& f) {
     COORDINATE food_coordinate = f.GetFoodCoordinate();

     // 检测食物与蛇头是否重合
     if(food_coordinate.x == m_coordinate[0].x && food_coordinate.y == m_coordinate[0].y) {
          // 吃到
          f.RandomXY(m_coordinate);
          return true; // 此时蛇长度不变（已经+1，不删除尾部）
     } else {
          // 没吃到
          m_coordinate.pop_back(); // 删除蛇尾
          return false;
     }
}

bool Snake::self_collision(COORDINATE head) {
     // true: 碰撞 false: 未碰撞
     for(unsigned int i = 1; i < m_coordinate.size(); i++) {
          if(head.x == m_coordinate[i].x && head.y == m_coordinate[i].y) {
               return true;
          }
     }
     return false;
}

bool Snake::snake_is_alive() {
     // 检查1：是否超出边界
     if(m_coordinate[0].x <= 0 || m_coordinate[0].x >= GameSetting::windows_width - 21
          || m_coordinate[0].y <= 0 || m_coordinate[0].y >= GameSetting::windows_height - 1) {
               m_is_alive = false;
               return false;
          }

     // 检查2：是否碰到自己
     if(self_collision(m_coordinate[0])) {
          m_is_alive = false;
          return false;
     }

     m_is_alive = true;
     return true;
}

void Snake::draw_snake() {
     GameSetting::setColor(10, 0); // green

     for(unsigned int i = 0; i < m_coordinate.size(); i++) {
          GameSetting::gotoXY(m_coordinate[i].x, m_coordinate[i].y);
          cout << "*";
     }

     GameSetting::setColor(7, 0); // white
}

void Snake::clear_snake() {
     // 清空蛇身在棋盘上的标记 for A* search
     for(unsigned int i = 0; i < m_coordinate.size(); i++) {
          m_chess[m_coordinate[i].x][m_coordinate[i].y] = false;
     }
                                          
     // 清除移动后重复打印的蛇尾
     GameSetting::gotoXY(m_coordinate.back().x, m_coordinate.back().y);
     cout << " ";
}

int Snake::GetSnakeSize() {
     return m_coordinate.size();
}

bool Snake::GetModel() {
     return m_model;
}

int Snake::GetDiffSpeed() {
     int temp = m_diff_speed;
     m_diff_speed = 0;
     return temp;
}