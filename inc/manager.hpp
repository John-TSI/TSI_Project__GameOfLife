#ifndef MANAGER_HPP
#define MANAGER_HPP

#include<unordered_map>
#include<array>
#include<string>

using Seed = std::array<int, 50/* (_Game::Manager::cols)*(_Game::Manager::rows) */>;
//using Grid = std::array<std::array<int, (_Game::Manager::cols)>, (_Game::Manager::rows)>;
using Grid = std::array<std::array<int, 10>, 5>;

namespace _Game
{
    enum State{Dead, Alive};
    static std::unordered_map<int,char> symbolMap = {
        {State::Dead, '.'}, 
        {State::Alive, '@'}, };
 /*    static std::unordered_map<int,std::string> symbolMap2 = {
        {State::Dead, "\x25A2"}, 
        {State::Alive, "\x25A3"}, }; */
    /*static std::unordered_map<int,char> symbolMap3 = {
        {State::Dead, '▢'}, 
        {State::Alive, '▣'}, }; */


    struct Manager
    {
        // --- attributes ---
        static const int cols = 10, rows = 5;
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