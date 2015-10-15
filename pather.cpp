#include <iostream>
#include <cstdlib>
#include "pather.h"

using std::endl;
using std::cout;
int Pather::face[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
char Pather::action[13] = {'R', 'L', 'M', 'W', 'E', 'O', 'U', 'D', '<', '>', '^', 'v', 'B'};

Pather::Pather()
{
    x = 0;
    y = 0;
    slope = 1; //alegbraic slope to goal
    facing = 2; //0 north, 1 east, 2 south, 3 west
    cost = 1;
    createTree();
}
Pather::Pather(string input)
{
    x = 0;
    y = 0;
    slope = 1; //alegbraic slope to goal
    facing = 2; //0 north, 1 east, 2 south, 3 west
    cost = 1;
    createTree(input);
}

void Pather::cycle()
{
    int time_out = 0;
    cost = 0;
    while(x != 39 || y != 39)
    {
        if(time_out > 1000)
            break;
        time_out++;
        executeNode(decisions.getRoot());
    }
}
void Pather::executeNode(node* current)
{
    if(current == NULL);
    else
    {
        char symbol = current->info;
        bool check = true;

        if(symbol == 'R')
            turnRight();
        else if(symbol == 'L')
            turnLeft();
        else if(symbol == 'M')
            Move();
        else if(symbol == 'W')
            check =WaterAhead();
        else if(symbol == 'E')
            check =EnemyAhead();
        else if(symbol == 'O')
            check =Obstruction();
        else if(symbol == 'U')
            check =Uphill();
        else if(symbol == 'D')
            check =Downhill();
        else if(symbol == '<')
            check =GoalLeft();
        else if(symbol == '>')
            check =GoalRight();
        else if(symbol == '^')
            check =GoalAhead();
        else if(symbol == 'v')
            check =GoalBehind();
        else if(symbol == 'B')
        {
            check = doBoth();
            executeNode(current->right);
        }
        else
            cout <<"UNKNOWN ERROR";

        if(check)
            executeNode(current->left);
        else
            executeNode(current->right);
    }
}
void Pather::createTree()
{
    decisions.createTree(action);
}
void Pather::cross(node* n)
{
    decisions.append(decisions.getRand(), n);
}
void Pather::mut()
{
    Btree* t = new Btree;
    t->createTree(action);
    decisions.append(decisions.getRand(), t->getRoot());
    delete t;
}

void Pather::createTree(string input)
{
    decisions.createTreeStr(input);
}
void Pather::turnLeft()
{
    cost++;
    facing = (facing  - 1) % 4;
    if(facing < 0)
        facing += 4;
    slope = (40 - y) / (40 - x);
}
void Pather::turnRight()
{
    cost++;
    facing = (facing + 1) % 4;
    if(facing < 0)
        facing += 4;

    slope = (40 - y) / (40 - x);
}
void Pather::Move()
{
    cost++;
    if(x+face[facing][1] > 39 || y+face[facing][0] > 39 || y+face[facing][0] < 0 || x+face[facing][1] < 0);
    else if(map[y+face[facing][0]][x+face[facing][1]] == 'X');
    else
    {
        if(map[y][x] > 47 && map[y][x] < 58)
            cost+=(map[y][x] - '0') * 10;
        if(map[y][x] == '~')
            cost += 5;
        if(map[y][x] == 'V')
            cost += 100000;
        map[y][x] = '_';
        x +=face[facing][1];
        y +=face[facing][0];
    }
}
bool Pather::GoalLeft()    //Slope decreases as you move lower on the map
{                          // and increases as you move right
    if(facing == 2 && slope <= 1)
        return true;
    if(facing == 3 && slope > 1)
        return true;

    return false;
}
bool Pather::GoalRight()
{
    if(facing == 0 && slope <= 1)
        return true;
    if(facing == 1&& slope > 1)
        return true;

    return false;
}
bool Pather::GoalAhead()
{
    if(facing == 1 && slope <= 1)
        return true;
    if(facing == 2&& slope > 1)
        return true;

    return false;
}
bool Pather::GoalBehind()
{
    if(facing == 3 && slope <= 1)
        return true;
    if(facing == 0&& slope > 1)
        return true;

    return false;
}
bool Pather::Uphill()
{
    if(x+face[facing][1] > 39 || y+face[facing][0] > 39 || y+face[facing][0] < 0 || x+face[facing][1] < 0)
            return false;
    if(map[y+face[facing][0]][x+face[facing][1]] > map[y][x])
        return true;

    return false;
}
bool Pather::Downhill()
{
    if(x+face[facing][1] > 39 || y+face[facing][0] > 39 || y+face[facing][0] < 0 || x+face[facing][1] < 0)
            return false;
   if(map[y+face[facing][0]][x+face[facing][1]] < map[y][x])
        return true;

    return false;
}
bool Pather::WaterAhead()
{
    for(int a = 1; a <= 3; a++)
    {
        if(x+a*face[facing][1] > 39 || y+a*face[facing][0] > 39 || y+a*face[facing][0] < 0 || x+a*face[facing][1] < 0)
            return false;
        if(map[y+(face[facing][0] * a)][x+(face[facing][1] * a)] == '~')
            return true;
    }

    return false;
}
bool Pather::EnemyAhead()
{
    for(int a = 1; a <= 3; a++)
    {
        if(x+a*face[facing][1] > 39 || y+a*face[facing][0] > 39 || y+a*face[facing][0] < 0 || x+a*face[facing][1] < 0)
            return false;
        if(map[y+(face[facing][0] * a)][x+(face[facing][1] * a)] == 'v')
            return true;
    }

    return false;
}
bool Pather::Obstruction()
{
    if(x+face[facing][1] > 39 || y+face[facing][0] > 39 || y+face[facing][0] < 0 || x+face[facing][1] < 0)
            return true;
    for(int a = 1; a <= 3; a++)
    {
        if(map[y+(a*face[facing][0])][x+(a*face[facing][1])] == 'X')
            return true;
    }
    return false;
}
bool Pather::doBoth()
{
    return true;
}
string Pather::getOutput()
{
    decisions.str();
    return decisions.output;
}
