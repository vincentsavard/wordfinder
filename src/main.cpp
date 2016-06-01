#include "grid/grid.h"
#include "grid/grid_size.h"
#include "grid/position.h"
#include "grid/adjacent_indices_finder/diagonal_adjacent_positions_finder.h"

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

int main() {
    using namespace wordfinder::grid;

    GridSize grid_size(2, 2);
    std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder = std::make_unique<DiagonalAdjacentPositionsFinder>(grid_size);
    Grid grid(grid_size, std::move(adjacent_positions_finder));

    grid.fill_cell(Position(0, 0), std::vector<std::string>{ "A" });
    grid.fill_cell(Position(0, 1), std::vector<std::string>{ "B" });
    grid.fill_cell(Position(1, 0), std::vector<std::string>{ "C" });
    grid.fill_cell(Position(1, 1), std::vector<std::string>{ "D" });

    std::vector<std::string> combinations(grid.generate_combinations());

    for (const std::string& combination : combinations) {
        std::cout << combination << std::endl;
    }

    return 0;
}
