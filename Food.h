#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include "GameSetting.h"

using namespace std;

class Food
{
private:
     // 食物坐标
     COORDINATE m_coordinate;
public:
     Food();
     Food(vector<COORDINATE>& Snake);

     void RandomXY(vector<COORDINATE>& Snake);
     void draw_food();

     // 获取食物坐标，用于判断是否吃到食物
     COORDINATE GetFoodCoordinate();
};

#endif