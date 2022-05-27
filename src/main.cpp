#include "../lib/grid.h"

#include <iostream>
#include <string>

// #define ALIVE "*"
// #define DEAD "."

#define ALIVE "\033[40m \033[00m"
#define DEAD "\033[47m \033[00m"

void update(Grid<char> &grid)
{
    Grid<char> copyGrid(grid);
    for (auto row : grid.rows())
    {
        for (auto col : grid.cols())
        {
            int neighboursAlive = 0;
            auto indexNeighbours = copyGrid.get_neighbours(row, col);
            for (auto index : indexNeighbours)
            {
                neighboursAlive += copyGrid.at(index.row, index.col);
            }

            // if the cell is alive
            if (copyGrid.at(row, col))
            {
                if (neighboursAlive < 2 || neighboursAlive > 3)
                    grid.at(row, col) = 0;
            }
            // if the cell is dead
            else
            {
                if (neighboursAlive == 3)
                    grid.at(row, col) = 1;
            }
        }
    }
}

void show_grid(const Grid<char> &grid)
{
    for (auto row : grid.rows())
    {
        for (auto col : grid.cols())
        {
            std::cout << (grid.atConst(row, col) ? ALIVE : DEAD);
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    // srand(NULL);
    Grid<char> grid(10, 5, [](void)
                    { return (char)(rand() % 2); });
    for (auto turn : range(100))
    {
        show_grid(grid);
        update(grid);
        system("sleep 1");
        system("cls");
    }
    return 0;
}
