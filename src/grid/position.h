#ifndef POSITION_HEADER_GUARD
#define POSITION_HEADER_GUARD

#include <functional>

namespace wordfinder {
namespace grid {

class Position {
public:
    Position(size_t i, size_t j) noexcept;

    bool operator==(const Position& other_position) const noexcept;
    bool operator!=(const Position& other_position) const noexcept;

    size_t get_i() const noexcept;
    size_t get_j() const noexcept;

private:
    size_t i;
    size_t j;
};

}
}

namespace std {
template <>
struct hash<wordfinder::grid::Position> {
    size_t operator()(const wordfinder::grid::Position& position) const {
        return (131 + std::hash<size_t>()(position.get_i())) * 131 + std::hash<size_t>()(position.get_j());
    }
};
}

#endif
