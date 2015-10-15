#ifndef BTREE_H
#define BTREE_H
#include <cstdlib>
#include <iostream>
#include <string>
using std::string;
struct node
{
  char info;
  node *left;
  node *right;
};
class Btree
{
    public:
        Btree();
        ~Btree();
        Btree(Btree &source);
        void destroyTree(node*);        //recursively deletes every node in the subtree with root n

        int check(char);                //Returns an int based on what type of function is indicated by char
        node* createTree(char[]);       //generates a random tree using the array of actions
        void createTreeStr(string);     //generates a tree from the predetermined string

        node* getRoot();                //returns the root node
        void append(node*, node*);      //replaces the subtree with root node1 with the subtree with root node2
        node* getRand();                //returns a random node

        void str();                     //generates the tree's string and stores it in output
        void display();                 //calls str() and prints output to the screen
        string output;

    private:

        void copyTree(node*&, node*&);  //recursive copy constructor
        void display(node*);
        void str(node*);

        node *root;
        int size;

        node* arr[1000];                //Used to create a node from a string, tree is built backwards using a stack
        int top;
        void push(node*);
        node* pop();
};

#endif
