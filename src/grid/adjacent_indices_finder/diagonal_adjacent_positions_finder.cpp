#include "diagonal_adjacent_positions_finder.h"

#include <algorithm>

namespace wordfinder {
namespace grid {

DiagonalAdjacentPositionsFinder::DiagonalAdjacentPositionsFinder(GridSize grid_size) noexcept
    : grid_size(grid_size)
{}

std::vector<Position> DiagonalAdjacentPositionsFinder::find_adjacent_non_visited_indices_from_position(const Position& position, const std::unordered_set<Position>& visited_positions) const {
    std::vector<Position> adjacent_positions;
    size_t i, j;

    position.get_i();
    visited_positions.empty();

    for (int i_modifier = -1; i_modifier <= 1; i_modifier++) {
        for (int j_modifier = -1; j_modifier <= 1; j_modifier++) {
            i = static_cast<size_t>(std::max(0, static_cast<int>(position.get_i()) + i_modifier));
            j = static_cast<size_t>(std::max(0, static_cast<int>(position.get_j()) + j_modifier));
            Position adjacent_position(i, j);
            bool is_already_added = is_position_already_added(adjacent_position, adjacent_positions);
            bool is_already_visited = was_position_already_visited(adjacent_position, visited_positions);

            if (grid_size.is_position_valid(adjacent_position)
                && adjacent_position != position
                && !is_already_added
                && !is_already_visited)
            {
                adjacent_positions.push_back(adjacent_position);
            }
        }
    }

    return adjacent_positions;
}

bool DiagonalAdjacentPositionsFinder::is_position_already_added(const Position& position, const std::vector<Position>& adjacent_positions) const {
    return std::find(adjacent_positions.cbegin(), adjacent_positions.cend(), position) != adjacent_positions.end();
}

bool DiagonalAdjacentPositionsFinder::was_position_already_visited(const Position& position, const std::unordered_set<Position>& visited_positions) const {
    return visited_positions.find(position) != visited_positions.cend();
}

}
}
