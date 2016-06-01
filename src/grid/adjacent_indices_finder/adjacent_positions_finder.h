#ifndef ADJACENT_INDICES_FINDER_HEADER_GUARD
#define ADJACENT_INDICES_FINDER_HEADER_GUARD

#include "../position.h"

#include <set>
#include <vector>

namespace wordfinder {
namespace grid {

class AdjacentPositionsFinder {
public:
    virtual std::vector<Position> find_adjacent_non_visited_indices_from_position(const Position& position, const std::set<Position>& visited_positions) const = 0;
};

}
}

#endif
