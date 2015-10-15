#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "pather.h"
const int MAPSIZE = 40;
const int pop = 50;
const int gen = 100;
char map[40][40] = {0};
char tmap[40][40] = {0}; //Clean copy of the map to refresh from
using namespace std;

struct tag    //tags each cost with its program so they can be sorted
{
    int cost;
    int t;
};
void read_map(char[][MAPSIZE]);
void output_map(char[][MAPSIZE]);
void quickSort(tag arr[], int left, int right);
void reproduce(Pather**, Pather**, tag[]);      //Genetic Operations
void crossover(Pather**, Pather**, tag[]);
void mutate(Pather**, Pather**, tag[]);
void results(Pather**, Pather**, tag[]);

int main()
{
    int repeat = 0, average = 0;
    srand(time(NULL));
    Pather *test[pop];
    Pather *save[pop];
    tag cost[pop];

    read_map(map);
    output_map(map);
    cout << endl << endl;

    for(int x = 0; x < pop; x++)    //Generate the initial population
    {
        save[x] = new Pather;
    }

    while(repeat <= gen)
    {
        average = 0;
        for(int x = 0; x < pop; x++) //Cycle through all of the current generation
        {
            for(int z=0; z < MAPSIZE; z++)      //Refresh the map
                for(int y=0; y < MAPSIZE; y++)
                    map[y][z] = tmap[y][z];

            test[x] = new Pather(save[x]->getOutput()); //grab the next Pather to test
            test[x]->cycle();                           //Test it
            cost[x].cost = test[x]->cost;               //Store the path score
            cost[x].t = x;
            average += cost[x].cost;
        }
        cout << "Average for gen " << repeat << " is " << average/pop << endl;
        for(int x=0; x < pop; x++) //clear the saved Pathers
        {
            delete save[x];
        }

        quickSort(cost, 0, pop);        //Sort the Pather by score

        repeat++;


        if(repeat > gen)
            break;

        reproduce(test, save, cost); //generate the new generation in save[]
        crossover(test, save, cost);
        mutate(test, save, cost);

        for(int x=0; x < pop; x++) //clear the tested Pathers
        {
            delete test[x];
        }

    }

    results(test, save, cost);
    int temp;
    cin >> temp;
    return (0);
}
void results(Pather* test[], Pather* save[], tag cost[])
{
    for(int x=0; x < MAPSIZE; x++)
        for(int y=0; y < MAPSIZE; y++)
            map[y][x] = tmap[y][x];

    save[0] = new Pather(test[cost[0].t]->getOutput()); //Print the best Pather generated
    save[0]->cycle();

    output_map(map);
    cout << "Solved in " << save[0]->cost << " steps";

}
void reproduce(Pather* test[], Pather* save[], tag cost[])
{
    for(int x=0; x < 3; x++)
    {
        save[x] = new Pather(test[cost[x].t]->getOutput());
    }

}
void crossover(Pather* test[], Pather* save[], tag cost[])
{
    for(int x=3; x< pop*9/10; x++)
    {
        save[x] = new Pather(save[rand()%3]->getOutput());
        save[x]->cross(save[rand()%3]->decisions.getRand());
    }
}
void mutate(Pather* test[], Pather* save[], tag cost[])
{
    for(int x=pop*9/10; x < pop; x++)
    {
        save[x] = new Pather;
    }

}
void quickSort(tag arr[], int left, int right)    //Use quicksort for speed
 {
      int i = left, j = right;
      tag tmp;
      int pivot = arr[(left + right) / 2].cost;

      while (i <= j)
      {
        while (arr[i].cost < pivot)
              i++;
        while (arr[j].cost > pivot)
              j--;
        if (i <= j)
        {
              tmp = arr[i];
              arr[i] = arr[j];
              arr[j] = tmp;
              i++;
              j--;
        }
    }
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
            quickSort(arr, i, right);
}
void read_map(char rmap [][MAPSIZE])
{
    string mapn, filename;
    cout << "Choose a map (1-5) ";
    cin >> mapn;
    filename = "map_" + mapn + ".txt";

    ifstream mydata(filename.c_str());   //Input from file
    string line;

    int line_num = 0;
    int space_num = 0;

    while(mydata >> line)
    {
        for(int x = 0; x < MAPSIZE; x++)
        {
          rmap[line_num][space_num] = line[x];
          space_num++;
        }
        line_num++;
        space_num = 0;
    }
    for(int x=0; x < MAPSIZE; x++)
        for(int y=0; y < MAPSIZE; y++)
            tmap[y][x] = rmap[y][x];
}
void output_map(char rmap [][MAPSIZE])
{
    for(int y = 0; y < MAPSIZE; y++)
    {
    for(int x = 0; x < MAPSIZE; x++)
        {
          cout << rmap[y][x];
        }
        cout << endl;
    }
}
