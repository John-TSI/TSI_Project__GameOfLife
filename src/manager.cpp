#include<iostream>
#include<iomanip>
#include<limits>
#include<windows.h> // ClearScreen()
#include<conio.h> // getch()
#include<time.h>
#include<chrono>
#include<thread>
#include"../inc/manager.hpp"
//#include"../inc/mingw.invoke.h"
//#include"../inc/mingw.thread.h" 


// --- initialise ---
void _Game::CellsManager::SeedInitialiseGrid(Seed& seed)
{
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            cellGrid[r][c] = CellState( seed[r*COLS + c] );
        }
    }
    // store initial configuration for calls to Restart()
    initGrid = cellGrid;
}

void _Game::CellsManager::RandomInitialiseGrid()
{
    srand(time(NULL));
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            cellGrid[r][c] = CellState( (int) (rand()%10 < 3) );
        }
    }
    // store initial configuration for calls to Restart()
    initGrid = cellGrid;
}


// --- restart / pause ---
void _Game::CellsManager::Restart()
{
    generationCount = 0;
    cellGrid = initGrid;
}

void _Game::CellsManager::Pause()
{   
    std::cout << "\nGame has been paused. Enter any key to resume:\n> ";
    _getch(); // wait for key input
    system("cls||clear");
}

char _Game::CellsManager::CheckForUserInput()
{
    char c = 'z';
    if( _kbhit() ) { c = _getch(); }
    return c;
}

void _Game::CellsManager::ProcessUserInput(const char& c)
{
    switch(c)
    {
        case 'r':
        {
            Restart();
            break;
        }
        case 'p':
        {
            Pause();
            break;
        }
        default: {}
    }
}


// --- utility ---
int _Game::CellsManager::CountAllCells(Grid& grid)
{
    int totalCellCount = 0;
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            if(cellGrid[r][c] == CellState::Alive) { ++totalCellCount; }
        }
    }
    return totalCellCount;
}

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

void _Game::CellsManager::AdvanceCellGrid(Grid& grid)
{
    for(int r=0; r<ROWS; r++)
    {
        for(int c=0; c<COLS; c++)
        {
            grid[r][c] = CellState( (int)CellLives(grid[r][c], CountNeighbours(grid, r, c) ) );
        }
    }
}


// --- output ---
void _Game::CellsManager::ClearScreen()
{
    COORD cursorPosition(0,0);
    SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition );
}

void _Game::CellsManager::PrintCommands()
{
    std::cout << "Inputs:  'r' - restart , 'p' - pause , 'q' - quit\n";
}

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
    std::cout << "\n";
}

void _Game::CellsManager::PrintInfo()
{
    std::cout << "Generation " << std::setfill('0') << std::setw(2) << ++generationCount << " :\n";
    std::cout << std::setfill('0') << std::setw(2) << CountAllCells(cellGrid) << " cells are alive.\n";
    std::cout <<  std::setfill(' ');
}

void _Game::CellsManager::Run()
{
    system("cls||clear");

    //SeedInitialiseGrid(seed);
    RandomInitialiseGrid();

    while(true)
    {
        ClearScreen();
        PrintCommands();
        PrintGrid(cellGrid);
        PrintInfo();
        AdvanceCellGrid(cellGrid);

        char userRequest = CheckForUserInput();
        if(userRequest == 'q') { break; }
        else if(userRequest != 'z')
        { 
            ProcessUserInput(userRequest);
            continue; 
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    }
}