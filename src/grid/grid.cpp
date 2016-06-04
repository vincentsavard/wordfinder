#include "grid.h"
#include "position.h"
#include "adjacent_indices_finder/adjacent_positions_finder.h"
#include "../dictionary/dictionary.h"

#include <algorithm>
#include <cassert>
#include <iterator>
#include <sstream>

namespace wordfinder {
namespace grid {

Grid::Grid(
    GridSize grid_size,
    std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder,
    std::unique_ptr<dictionary::Dictionary> dictionary,
    size_t minimum_word_length
) noexcept
    : grid_size(grid_size)
    , grid(grid_size.calculate_cell_count())
    , adjacent_positions_finder(std::move(adjacent_positions_finder))
    , dictionary(std::move(dictionary))
    , minimum_word_length(minimum_word_length)
{}

void Grid::fill_cell(const Position& position, std::vector<std::string> values) {
    grid[linearize_position(position)] = values;
}

std::vector<std::string> Grid::find_words() const {
    std::vector<std::string> words;

    for (const Position& position : generate_positions()) {
        std::vector<std::vector<Position>> position_combinations;
        std::vector<Position> current_combination;
        std::unordered_set<Position> visited_positions;

        find_combinations_from_position(
            position,
            position_combinations,
            current_combination,
            visited_positions
        );

        for (const std::vector<Position>& combination : position_combinations) {
            std::ostringstream word_stream;
            std::string current_word;
            
            // Each cell can currently only contain a single character.
            // This will need to be fixed once a cell can hold more than one
            // character.
            for (const Position& position_in_combination : combination) {
                word_stream << grid[linearize_position(position_in_combination)][0];
            }

            current_word = word_stream.str();

            if (current_word.size() >= minimum_word_length && dictionary->word_exists(current_word)) {
                words.push_back(current_word);
            }
        }
    }

    std::sort(words.begin(), words.end(), [](const std::string& s, const std::string& t) {
        return s.length() > t.length(); 
    });

    return words;
}

std::vector<Position> Grid::generate_positions() const noexcept {
    std::vector<Position> positions;

    for (size_t i = 0; i < grid_size.get_row_count(); i++) {
        for (size_t j = 0; j < grid_size.get_column_count(); j++) {
            positions.push_back(Position(i, j));
        }
    }

    return positions;
}

void Grid::find_combinations_from_position(
    const Position& position, std::vector<std::vector<Position>>& combinations,
    std::vector<Position> current_combination,
    std::unordered_set<Position> visited_positions
) const {
    current_combination.push_back(position);

    if (!is_any_string_at_combination_a_radix(current_combination)) {
        return;
    }

    combinations.push_back(current_combination);
    visited_positions.emplace(position);

    for (const Position& adjacent_position : adjacent_positions_finder->find_adjacent_non_visited_indices_from_position(position, visited_positions)) {
        find_combinations_from_position(
            adjacent_position,
            combinations,
            current_combination,
            visited_positions
        );
    }
}

size_t Grid::linearize_position(const Position& position) const noexcept {
    assert(grid_size.is_position_valid(position));
    return position.get_i() * grid_size.get_row_count() + position.get_j();
}

std::vector<std::string> Grid::find_words_at_combination(const std::vector<Position>& combination) const {
    std::vector<std::string> words;
    std::ostringstream current_word;

    for (const Position& position : combination) {
        // Each cell can currently only contain a single character.
        // This will need to be fixed once a cell can hold more than one
        // character.
        for (const std::string& character : grid[linearize_position(position)]) {
            current_word << character;
        }
    }

    words.push_back(current_word.str());

    return words;
}

bool Grid::is_any_string_at_combination_a_radix(const std::vector<Position>& combination) const noexcept {
    std::vector<std::string> words(find_words_at_combination(combination));

    return std::any_of(words.cbegin(), words.cend(), [this](const std::string& word) {
        return dictionary->radix_exists(word);
    });
}

}
}
