#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<unordered_map>
#include<array>
#include<string>


namespace _Game
{
    static const int COLS{10}, ROWS{5};
    
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
            0,0,0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,0,0,0,0,
            0,1,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,1
        };

        Grid cellGrid{};


        // --- initialise ---
        void SeedInitialiseGrid(Seed&);
        void RandomInitialiseGrid();

        // --- utility ---
        int CountAllCells(Grid&);
        int CountNeighbours(Grid&, const int, const int);
        bool CellLives(bool, const int);
        Grid AdvanceCellGrid(Grid&);

        // --- output ---
        void ClearScreen();
        void PrintGrid(Grid&);
        void PrintInfo();
        void Run();
    };
}    

#endif