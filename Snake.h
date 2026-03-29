#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <conio.h>  // 用于 _kbhit() 和 _getch()
#include "Food.h"
#include "GameSetting.h"
#include "FindPathAStar.h"

using namespace std;

class Snake {
private:
     bool m_model; // true: 手动 false: 自动
     int m_dir;
     enum Dir {
          UP = 1,
          DOWN,
          LEFT,
          RIGHT,
     };
     // 1 = UP
	// 2 = DOWN
	// 3 = LEFT
	// 4 = RIGHT
     int m_diff_speed;
     bool m_is_alive;

private: // AI功能相关
     FindPathAStar m_astar;
	bool m_chess[GameSetting::windows_width - 20][GameSetting::windows_height];
	// m_chess[60][40]：59行 × 39列的二维数组放x y
     // 实际上只用 1-58/1-38 的可活动区域
	// 用来标记哪些位置是障碍（蛇身、边界）
	
	COORDINATE map_size;    // 记录可活动范围的大小

public:
	vector<COORDINATE> m_coordinate; // 蛇每一节的坐标
     Snake(bool model = true);

     void listen_keyboard();
     void build_chess();
     void AI_search(Food& f);
     void move_snake(Food& f);
     bool is_eat_food(Food& f);
     bool self_collision(COORDINATE head);
     bool snake_is_alive();
     void draw_snake();
     void clear_snake();

     int GetSnakeSize();
     bool GetModel();
     int GetDiffSpeed();
};

#endif
