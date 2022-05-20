#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<unordered_map>
#include<array>
#include<string>


namespace _Game
{
    static const int COLS = 10, ROWS = 5;
    
    using Seed = std::array<int, COLS*ROWS>;
    using Grid = std::array<std::array<int, COLS>, ROWS>;

    enum State{Dead, Alive};
    static std::unordered_map<int,std::string> symbolMap
    {
        {State::Dead, "□"}, 
        {State::Alive, "■"},
    };


    struct Manager
    {
        Seed seed
        {
            0,0,0,0,0,0,0,0,0,1,
            0,0,0,0,0,0,0,0,1,0,
            0,0,0,0,0,0,0,0,0,0,
            0,1,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,1
        };

        Grid gameGrid{};


        // --- initialise ---
        void SeedInitialiseGrid(Seed&);
        void RandomInitialiseGrid();

        // --- utility ---
        Grid GenerateAdjacencyMatrix(Grid&);

        // --- output ---
        void PrintGrid(Grid&);
        void Run();
    };
}    

#endif