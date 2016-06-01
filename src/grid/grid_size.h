#ifndef GRID_SIZE_HEADER_GUARD
#define GRID_SIZE_HEADER_GUARD

namespace wordfinder {
namespace grid {

class Position;

class GridSize {
public:
    GridSize(size_t row_count, size_t column_count) noexcept;
    
    size_t calculate_cell_count() const noexcept;
    bool is_position_valid(const Position& position) const noexcept;
    size_t get_row_count() const noexcept;
    size_t get_column_count() const noexcept;

private:
    size_t row_count;
    size_t column_count;
};

}
}

#endif
