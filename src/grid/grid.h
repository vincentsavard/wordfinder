#ifndef GRID_HEADER_GUARD
#define GRID_HEADER_GUARD

#include "grid_size.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace wordfinder {
namespace dictionary {
class Dictionary;
}

namespace grid {

class AdjacentPositionsFinder;
class Position;

class Grid {
public:
    Grid(
        GridSize grid_size,
        std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder,
        std::unique_ptr<dictionary::Dictionary> dictionary
    ) noexcept;

    Grid(const Grid& grid) = delete;
    Grid& operator=(Grid grid) = delete;

    void fill_cell(const Position& position, std::vector<std::string> values);
    std::vector<std::string> find_words() const;

private:
    std::vector<Position> generate_positions() const noexcept;
    size_t linearize_position(const Position& position) const noexcept;
    std::vector<std::string> find_words_at_combination(const std::vector<Position>& combination) const;
    bool is_any_string_at_combination_a_radix(const std::vector<Position>& combination) const noexcept;

    void find_combinations_from_position(
        const Position& position,
        std::vector<std::vector<Position>>& combinations,
        std::vector<Position> current_combination,
        std::unordered_set<Position> visited_positions
    ) const;

    GridSize grid_size;
    std::vector<std::vector<std::string>> grid;
    std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder;
    std::unique_ptr<dictionary::Dictionary> dictionary;
};

}
}

#endif
