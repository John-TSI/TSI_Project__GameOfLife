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
int _Game::Manager::CountNeighbours(Grid& grid, const int row, const int col)
{
    return 
    (col > 0 && grid[row][col-1] == State::Alive) + // left
	(col < COLS-1 && grid[row][col+1] == State::Alive) + // right
	(row > 0 && grid[row-1][col] == State::Alive) + // above
	(row < ROWS-1 && grid[row+1][col] == State::Alive) + // below
	(row > 0 && col > 0 && grid[row-1][col-1] == State::Alive) + // top left
	(row > 0 && col < COLS-1 && grid[row-1][col+1] == State::Alive) + // top right
	(row < ROWS-1 && col > 0 && grid[row+1][col-1] == State::Alive) + // bottom left
	(row < ROWS-1 && col < COLS-1 && grid[row+1][col+1] == State::Alive); // bottom right
}

bool _Game::Manager::CellLives(bool isAlive, int neighbours)
{
    return (isAlive) ? neighbours == 2 || neighbours == 3 : neighbours == 3;
}

/* _Game::Grid _Game::Manager::GenerateAdjacencyMatrix(Grid& grid)
{
    Grid adjGrid{};
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            int count = 0;
            //if(grid[r][c])
        }
    }
    return adjGrid;
} */

_Game::Grid _Game::Manager::AdvanceCellGrid(Grid& grid) // change to modify the input grid (void return)?
{
    Grid nextGrid{};
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            nextGrid[r][c] = State( (int)CellLives(grid[r][c], CountNeighbours(grid, r, c) ) );
        }
    }
    return nextGrid;
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
    std::cout << "\n";
    Grid nextGrid = AdvanceCellGrid(gameGrid);
    PrintGrid(nextGrid);
}