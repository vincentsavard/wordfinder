#ifndef GRID_HEADER_GUARD
#define GRID_HEADER_GUARD

#include "grid_size.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace wordfinder {
namespace grid {

class AdjacentPositionsFinder;
class Position;

class Grid {
public:
    Grid(GridSize grid_size, std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder) noexcept;
    Grid(const Grid& grid) = delete;
    Grid& operator=(Grid grid) = delete;

    void fill_cell(const Position& position, std::vector<std::string> values);
    std::vector<std::string> generate_combinations() const;

private:
    std::vector<Position> generate_positions() const noexcept;
    void find_combinations_from_position(const Position& position, std::vector<std::vector<Position>>& combinations, std::vector<Position> current_combination, std::unordered_set<Position> visited_positions) const;
    size_t linearize_position(const Position& position) const noexcept;

    GridSize grid_size;
    std::vector<std::vector<std::string>> grid;
    std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder;
};

}
}

#endif
