#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<unordered_map>
#include<array>
#include<string>


namespace _Game
{
    static const int COLS{10}, ROWS{5}, SLEEP{1200};
    
    using Seed = std::array<int, COLS*ROWS>;
    using Grid = std::array<std::array<int, COLS>, ROWS>;

    enum CellState{Dead, Alive};

    static std::unordered_map<int,std::string> symbolMap
    {
        {CellState::Dead, /* "□" */ "~"}, 
        {CellState::Alive, /* "■" */ "O"},
    };


    struct CellsManager
    {
        int generationCount{0};
        Seed seed
        {
            0,0,0,0,0,0,0,0,0,1,
            0,1,1,1,0,0,0,0,1,0,
            0,0,0,0,0,0,0,0,0,1,
            0,1,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,1
        };

        Grid initGrid{}, cellGrid{};


        // --- initialise ---
        void SeedInitialiseGrid(Seed&);
        void RandomInitialiseGrid();
        void Initialise(bool&);

        // --- restart / pause ---
        void Restart();
        void Pause();
        char CheckForUserInput();
        void ProcessUserInput(const char&);

        // --- utility ---
        int CountAllCells(Grid&);
        int CountNeighbours(Grid&, const int, const int);
        bool CellLives(bool, const int);
        void AdvanceCellGrid(Grid&);

        // --- output ---
        void ClearScreen();
        void PrintCommands();
        void PrintGrid(Grid&);
        void PrintInfo();
        void Run();
    };
}    

#endif