#include "grid.h"
#include "position.h"
#include "adjacent_indices_finder/adjacent_positions_finder.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <set>
#include <sstream>

namespace wordfinder {
namespace grid {

Grid::Grid(GridSize grid_size, std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder) noexcept
    : grid_size(grid_size)
    , grid(grid_size.calculate_cell_count())
    , adjacent_positions_finder(std::move(adjacent_positions_finder))
{}

void Grid::fill_cell(const Position& position, std::vector<std::string> values) {
    grid[linearize_position(position)] = values;
}

std::vector<std::string> Grid::generate_combinations() const {
    std::vector<std::string> combinations;

    for (const Position& position : generate_positions()) {
        std::vector<std::vector<Position>> position_combinations;
        std::vector<Position> current_combination;
        std::set<Position> visited_positions;

        find_combinations_from_position(position, position_combinations, current_combination, visited_positions);

        for (const std::vector<Position>& combination : position_combinations) {
            std::ostringstream combination_stream;

            for (const Position& position_in_combination : combination) {
                combination_stream << grid[linearize_position(position_in_combination)][0];
            }

            combinations.push_back(combination_stream.str());
        }
    }

    return combinations;
}

std::vector<Position> Grid::generate_positions() const noexcept {
    std::vector<Position> positions;

    for (size_t i = 0; i < grid_size.get_row_count(); i++) {
        for (size_t j = 0; j < grid_size.get_column_count(); j++) {
            positions.push_back(Position(i, j));
        }
    }

    return positions;
}

void Grid::find_combinations_from_position(const Position& position, std::vector<std::vector<Position>>& combinations, std::vector<Position> current_combination, std::set<Position> visited_positions) const {
    current_combination.push_back(position);
    combinations.push_back(current_combination);
    visited_positions.emplace(position);

    for (const Position& adjacent_position : adjacent_positions_finder->find_adjacent_non_visited_indices_from_position(position, visited_positions)) {
        find_combinations_from_position(
            adjacent_position,
            combinations,
            current_combination,
            visited_positions
        );
    }
}

size_t Grid::linearize_position(const Position& position) const noexcept {
    assert(grid_size.is_position_valid(position));
    return position.get_i() * grid_size.get_row_count() + position.get_j();
}

}
}
