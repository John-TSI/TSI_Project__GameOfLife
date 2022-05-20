#include<iostream>
#include<iomanip>
#include<time.h>
#include"../inc/manager.hpp"


// --- initialise ---
void _Game::Manager::SeedInitialiseGrid(Seed& seed)
{
    for(int r=0; r<rows; r++)
    {
        for(int c=0; c<cols; c++)
        {
            gameGrid[r][c] = State( seed[r*cols + c] );
        }
    }
}

void _Game::Manager::RandomInitialiseGrid()
{
    srand(time(NULL));
    for(int r=0; r<rows; r++)
    {
        for(int c=0; c<cols; c++)
        {
            gameGrid[r][c] = State(rand()%2);
        }
    }
}


// --- utility ---
Grid _Game::Manager::GenerateAdjacencyMatrix(Grid& grid)
{
    Grid adjGrid{};
    for(int r=0; r<rows; r++)
    {
        for(int c=0; c<cols; c++)
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
    for(int r=0; r<rows; r++)
    {
        for(int c=0; c<cols; c++)
        {
/*             gameGrid[i][j] = State::Dead;
            gameGrid[1][5] = State::Alive; */
            std::cout << std::setw(2) << symbolMap[ grid[r][c] ];
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