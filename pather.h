#ifndef PATHER_H
#define PATHER_H
#include "btree.h"

extern const int MAPSIZE;
extern char map[40][40];

class Pather
{
    public:
        Pather();
        Pather(string);
        int x, y, slope;        //slope from current position to goal, always positive
        int facing;             //0 north, 1 east, 2 south, 3 west
        static int face[4][2];         //0 for neutral, 1 for down/right, -1 for up/left
        int cost;
        static char action[13]; //Array of actions as their char symbols
        Btree decisions;
        void cycle();

        void turnRight();       //'R'
        void turnLeft();        //'L'
        void Move();            //'M'
        bool WaterAhead();      //'W' Detect water within 3 squares
        bool EnemyAhead();  	//'E' Detect enemy units one square ahead
        bool Obstruction();  	//'O' Detect any roadblock within 3 squares
        bool Uphill();          //'U' TRUE if penalty for space 1 ahead is greater than current penalty
        bool Downhill();  	    //'D' TRUE if penalty for space 1 ahead is less than current penalty
        bool GoalLeft();        //'<' check relative direction of goal
        bool GoalRight();  	    //'>' check relative direction of goal
        bool GoalAhead();  	    //'^' check relative direction of goal
        bool GoalBehind();  	//'v' check relative direction of goal
        bool doBoth();  	    //'B' Execute both children, this allows a program to make a decision using memory

        void createTree();      //Create a random Tree
        void createTree(string);//Create a predefined Tree, stored as a string
        void executeNode(node*);
        string getOutput();     //Returns the tree as a string
        void cross(node*);      //Inserts the subtree at root n in a random location
        void mut();             //Inserts a random tree in a random location
};
#endif
