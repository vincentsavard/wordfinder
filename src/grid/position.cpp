#include "position.h"

namespace wordfinder {
namespace grid {

Position::Position(size_t i, size_t j) noexcept
    : i(i)
    , j(j)
{}

bool Position::operator==(const Position& other_position) const noexcept {
    return i == other_position.i && j == other_position.j;
}

bool Position::operator!=(const Position& other_position) const noexcept {
    return !operator==(other_position);
}

bool Position::operator<(const Position& other_position) const noexcept {
    return i < other_position.i || i == other_position.i && j < other_position.j;
}

size_t Position::get_i() const noexcept {
    return i;
}

size_t Position::get_j() const noexcept {
    return j;
}

}
}
