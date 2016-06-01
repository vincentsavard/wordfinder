#ifndef DIAGONAL_ADJACENT_INDICES_FINDER_HEADER_GUARD
#define DIAGONAL_ADJACENT_INDICES_FINDER_HEADER_GUARD

#include "adjacent_positions_finder.h"
#include "../grid_size.h"
#include "../position.h"

#include <set>
#include <vector>

namespace wordfinder {
namespace grid {

class DiagonalAdjacentPositionsFinder : public AdjacentPositionsFinder {
public:
    DiagonalAdjacentPositionsFinder(GridSize grid_size) noexcept;
    std::vector<Position> find_adjacent_non_visited_indices_from_position(const Position& position, const std::set<Position>& visited_positions) const override;

private:
    bool is_position_already_added(const Position& position, const std::vector<Position>& adjacent_positions) const;
    bool was_position_already_visited(const Position& position, const std::set<Position>& visited_positions) const;

    GridSize grid_size;
};

}
}

#endif
