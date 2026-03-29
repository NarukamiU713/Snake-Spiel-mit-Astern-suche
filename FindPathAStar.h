#ifndef FINDPATHASTAR_H
#define FINDPATHASTAR_H

#include <queue>
#include <string.h>
#include <cmath>
#include "GameSetting.h"

using namespace std;

struct AStarNode
{
     COORDINATE pos;
     int g;
     int h;
     int f;
     bool operator < (const AStarNode& a) const {
          return a.f < f;
     }
};

class FindPathAStar
{
private:
     static const int MAP_W = GameSetting::windows_width - 20; // 地图宽度是 60
     static const int MAP_H = GameSetting::windows_height; // 地图高是 40

     int g_cost[MAP_W][MAP_H];
     bool block[MAP_W][MAP_H];
     bool visited[MAP_W][MAP_H];
     COORDINATE parents[MAP_W][MAP_H];

     int dir[4][2] = {
          {0, -1}, // UP
          {0, 1},  // DOWN
          {-1, 0}, // LEFT
          {1, 0}   // RIGHT
     };

private:
     bool in_map(COORDINATE p) {
          // 可活动区域 x: 1-38 y: 1-58
          return p.x >= 1 && p.x <= MAP_W - 2 && p.y >= 1 && p.y <= MAP_H - 2;
     }

     int heuristic(COORDINATE a, COORDINATE b) {
          return abs(a.x - b.x) + abs(a.y - b.y);
     }

public:
     void InitBlock(bool chess[][GameSetting::windows_height]) {
          for(int i = 1; i < MAP_W - 1; i++) {
               for(int j = 1; j < MAP_H - 1; j++) {
                    block[i][j] = chess[i][j];
               }
          }
     }

     int GetNextDir(COORDINATE start, COORDINATE goal) {
          memset(g_cost, -1, sizeof(g_cost));
          memset(visited, false, sizeof(visited));
          priority_queue<AStarNode> pq;

          AStarNode start_node;
          start_node.pos = start;
          start_node.g = 0;
          start_node.h = heuristic(start, goal);
          start_node.f = start_node.g + start_node.h;
          
          g_cost[start.x][start.y] = 0;
          parents[start.x][start.y] = start;
          pq.push(start_node);

          while(!pq.empty()) {
               AStarNode cur = pq.top(); pq.pop();
               AStarNode next_node;
               if(visited[cur.pos.x][cur.pos.y]) continue;
               visited[cur.pos.x][cur.pos.y] = true;

               if(cur.pos.x == goal.x && cur.pos.y == goal.y) break;

               for(int i = 0; i < 4; i++) {
                    COORDINATE next;
                    next.x = cur.pos.x + dir[i][0];
                    next.y = cur.pos.y + dir[i][1];

                    // 检查地图越界/碰上障碍物/死循环
                    if(!in_map(next)) continue;
                    if(block[next.x][next.y]) continue;

                    int new_g = cur.g + 1;
                    // 判断这个点以前来过吗 这次来的路径是不是更优
                    if (g_cost[next.x][next.y] != -1 && new_g >= g_cost[next.x][next.y]) continue;

                    next_node.g = new_g;
                    next_node.h = heuristic(next, goal);
                    next_node.f = next_node.g + next_node.h;

                    next_node.pos = next;
                    g_cost[next.x][next.y] = next_node.g;
                    parents[next.x][next.y] = cur.pos;
                    pq.push(next_node);
               }
          }

          if(g_cost[goal.x][goal.y] == -1) return 0; // 没找到路

          COORDINATE cur = goal;
          while(parents[cur.x][cur.y].x != start.x || parents[cur.x][cur.y].y != start.y) {
          // 回溯的终止条件：parents[cur.x][cur.y].x == start.x && parents[cur.x][cur.y].y == start.y
               cur = parents[cur.x][cur.y];
          }

          if(cur.y == start.y - 1 && cur.x == start.x) return 1; // UP
          if(cur.y == start.y + 1 && cur.x == start.x) return 2; // DOWN
          if(cur.x == start.x - 1 && cur.y == start.y) return 3; // LEFT
          if(cur.x == start.x + 1 && cur.y == start.y) return 4; // RIGHT

          return 0;
     }  
};

#endif