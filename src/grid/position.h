#ifndef POSITION_HEADER_GUARD
#define POSITION_HEADER_GUARD

namespace wordfinder {
namespace grid {

class Position {
public:
    Position(size_t i, size_t j) noexcept;

    bool operator==(const Position& other_position) const noexcept;
    bool operator!=(const Position& other_position) const noexcept;
    bool operator<(const Position& other_position) const noexcept;

    size_t get_i() const noexcept;
    size_t get_j() const noexcept;

private:
    size_t i;
    size_t j;
};

}
}

#endif POSITION_HEADER_GUARD
