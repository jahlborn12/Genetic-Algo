
#include "BTree.h"
using std::cout;
using std::endl;

Btree::Btree()
{
    root=NULL;
    size = 0;
    output = "";
    top = -1;
}
Btree::~Btree()
{
  destroyTree(root);
  delete arr;
}
Btree::Btree(Btree &source)
{
    if(source.root == NULL)
        root = NULL;
    else
        copyTree(this->root, source.root);
}
void Btree::copyTree(node *&thisRoot, node *&sourceRoot)
{
    if(sourceRoot == NULL)
    {
        thisRoot = NULL;
    }
    else
    {
        thisRoot = new node;
        thisRoot->info = sourceRoot->info;
        copyTree(thisRoot->left, sourceRoot->left);
        copyTree(thisRoot->right, sourceRoot->right);
    }
}
void Btree::destroyTree(node *leaf)
{
  if(leaf!=NULL)
  {
    destroyTree(leaf->left);
    destroyTree(leaf->right);
    delete leaf;
  }

}
int Btree::check(char inputchar)
{
    if(inputchar=='D' || inputchar=='U' || inputchar=='O' || inputchar=='E' || inputchar=='W' || inputchar=='<' || inputchar=='>' || inputchar=='^' || inputchar=='v')
      return(-1);
     else if(inputchar=='R' || inputchar=='L' || inputchar=='M')
      return(1);
      else if(inputchar == 'B')
      return(2);
}
void Btree::append(node* oldN, node* newN)
{
    destroyTree(oldN->left);
    oldN->left = newN;
}
node* Btree::getRand()
{
    int lr;
    node* n = root;
    while(n->left != NULL)
    {
        if(rand() % 5 == 0)
            break;
        lr = rand() % 2;
        if(lr == 0)
            n = n->left;
        if(lr == 1)
            n = n->right;
    }
    return n;
}
node* Btree::createTree(char act[13])
{
    size++;

    char symbol;
    node *newl;
    int flag;


    if(size < 5)
        symbol = act[(rand() % 10) + 3];
    else if(size > 1000)
      symbol = act[rand() % 3];
    else
        symbol = act[rand() % 13];

    //cout << symbol;

    flag=check(symbol);

    if(flag == 1) //Action
    {
        newl = new node;
        newl->info = symbol;
        newl->right = NULL;
        newl->left = NULL;
    }
    else if(flag == -1) //Question
    {
        newl = new node;
        if(size == 1)
            root = newl;
        newl->info = symbol;
        newl->right = createTree(act);
        newl->left = createTree(act);

    }
    else //Do both (ensures that there are not 2 paths of execution
    {
        newl = new node;
        if(size == 1)
            root = newl;
        newl->info = symbol;
        newl->right = new node;
        newl->right->info = act[rand() % 3];
        newl->right->right = NULL;
        newl->right->left = NULL;
        newl->left = createTree(act);
    }
    return newl;
}
void Btree::createTreeStr(string input)
{
    int i = 1;

    char symbol;
    node *newl, *t1, *t2;
    int flag;

    symbol = input[0];
    while(1)
    {

        flag=check(symbol);

        if(flag == 1) //Action
        {
            newl = new node;
            newl->info = symbol;
            newl->right = NULL;
            newl->left = NULL;
            push(newl);
        }
        else //Question
        {
            t1 = pop();
            t2 = pop();
            newl = new node;
            newl->info = symbol;
            newl->right = t2;
            newl->left = t1;
            push(newl);
        }
        if(i == input.size())
        {
            root = newl;
            break;
        }
        symbol = input[i];
        i++;
    }
}
void Btree::push(node* tree)
{
    top++;
    arr[top]=tree;
}

node* Btree::pop()
{
    top--;
    return(arr[top+1]);
}

node* Btree::getRoot()
{
    return root;
}
void Btree::display()
{
    output = "";
    str(root);
    cout << output << endl;
}
void Btree::str()
{
    output = "";
    str(root);
}
void Btree::str(node *tree)
{
    if( tree!=NULL)
    {
        str(tree->right);
        str(tree->left);
        output += tree->info;
    }
}

