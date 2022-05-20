#include<iostream>
#include<iomanip>
#include<time.h>
#include"../inc/manager.hpp"


//void _Game::Manager::SeedInitialiseGrid(int seed[cols*rows])
void _Game::Manager::SeedInitialiseGrid(Seed seed)
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            //gameGrid[j][i] = State( seed[i*cols + j] );
            gameGrid[i][j] = State( seed[i*cols + j] );
        }
    }
}

void _Game::Manager::RandomInitialiseGrid()
{
    srand(time(NULL));
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            gameGrid[j][i] = State(rand()%2);
        }
    }
}

//void _Game::Manager::PrintGrid(int grid[cols][rows])
void _Game::Manager::PrintGrid(Grid grid)
{
    //grid[3][4] = 1;
    std::cout << "\n";
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            //std::cout << std::setw(2) << symbolMap[ grid[j][i] ];
            std::cout << std::setw(2) << symbolMap[ grid[i][j] ];
        }
        std::cout << "\n";
    }
}

void _Game::Manager::Run()
{
    SeedInitialiseGrid(seed);
    //RandomInitialiseGrid();
    PrintGrid(gameGrid);
}