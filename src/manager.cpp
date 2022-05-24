#include<iostream>
#include<iomanip>
#include<time.h>
#include"../inc/manager.hpp"


// --- initialise ---
void _Game::CellsManager::SeedInitialiseGrid(Seed& seed)
{
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            initGrid[r][c] = CellState( seed[r*COLS + c] );
        }
    }
}

void _Game::CellsManager::RandomInitialiseGrid()
{
    srand(time(NULL));
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            initGrid[r][c] = CellState( (int) (rand()%10 < 3) );
        }
    }
}


// --- utility ---
int _Game::CellsManager::CountNeighbours(Grid& grid, const int row, const int col)
{
    return 
    (col > 0 && grid[row][col-1] == CellState::Alive) + // left
	(col < COLS-1 && grid[row][col+1] == CellState::Alive) + // right
	(row > 0 && grid[row-1][col] == CellState::Alive) + // above
	(row < ROWS-1 && grid[row+1][col] == CellState::Alive) + // below
	(row > 0 && col > 0 && grid[row-1][col-1] == CellState::Alive) + // top left
	(row > 0 && col < COLS-1 && grid[row-1][col+1] == CellState::Alive) + // top right
	(row < ROWS-1 && col > 0 && grid[row+1][col-1] == CellState::Alive) + // bottom left
	(row < ROWS-1 && col < COLS-1 && grid[row+1][col+1] == CellState::Alive); // bottom right
}

bool _Game::CellsManager::CellLives(bool isAlive, int neighbours)
{
    return (isAlive) ? neighbours == 2 || neighbours == 3 : neighbours == 3;
}

_Game::Grid _Game::CellsManager::AdvanceCellGrid(Grid& grid) // change to modify the input grid (void return)?
{
    Grid nextGrid{};
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            nextGrid[r][c] = CellState( (int)CellLives(grid[r][c], CountNeighbours(grid, r, c) ) );
        }
    }
    return nextGrid;
}


// --- output ---
void _Game::CellsManager::PrintGrid(Grid& grid)
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

void _Game::CellsManager::Run()
{
    //SeedInitialiseGrid(seed);
    RandomInitialiseGrid();
    PrintGrid(initGrid);
    Grid nextGrid = AdvanceCellGrid(initGrid);
    PrintGrid(nextGrid);
}