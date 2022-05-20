#include<iostream>
#include<iomanip>
#include<time.h>
#include"../inc/manager.hpp"


// --- initialise ---
void _Game::Manager::SeedInitialiseGrid(Seed& seed)
{
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            gameGrid[r][c] = State( seed[r*COLS + c] );
        }
    }
}

void _Game::Manager::RandomInitialiseGrid()
{
    srand(time(NULL));
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            gameGrid[r][c] = State( (int) (rand()%10 < 3) );
        }
    }
}


// --- utility ---
_Game::Grid _Game::Manager::GenerateAdjacencyMatrix(Grid& grid)
{
    Grid adjGrid{};
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            int count = 0;
            //if(grid[r][c]) // RESUME HERE
        }
    }
    return adjGrid;
}

// --- output ---
void _Game::Manager::PrintGrid(Grid& grid)
{
    std::cout << "\n";
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            std::cout << std::setw(4) << symbolMap[ grid[r][c] ];
        }
        std::cout << "\n";
    }
}

void _Game::Manager::Run()
{
    //SeedInitialiseGrid(seed);
    RandomInitialiseGrid();
    PrintGrid(gameGrid);
}