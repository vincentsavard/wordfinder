#include "grid_size.h"
#include "position.h"

namespace wordfinder {
namespace grid {

GridSize::GridSize(size_t row_count, size_t column_count) noexcept
    : row_count(row_count)
    , column_count(column_count)
{}

size_t GridSize::calculate_cell_count() const noexcept {
    return row_count * column_count;
}

bool GridSize::is_position_valid(const Position& position) const noexcept {
    return position.get_i() < row_count && position.get_j() < column_count;
}

size_t GridSize::get_row_count() const noexcept {
    return row_count;
}

size_t GridSize::get_column_count() const noexcept {
    return column_count;
}

}
}
