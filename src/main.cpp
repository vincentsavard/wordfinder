#include "grid/grid.h"
#include "grid/grid_size.h"
#include "grid/position.h"
#include "grid/adjacent_indices_finder/diagonal_adjacent_positions_finder.h"
#include "dictionary/dictionary.h"
#include "dictionary/trie.h"

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

const constexpr size_t ROW_COUNT = 2;
const constexpr size_t COLUMN_COUNT = 2;
const constexpr size_t MINIMUM_WORD_LENGTH = 3;

std::unordered_set<std::string> get_allowed_characters() {
    static const std::string allowed_characters_as_string = "abcdefghijklmnopqrstuvwxyz";
    static std::unordered_set<std::string> allowed_characters;

    if (allowed_characters.empty()) {
        for (const char character : allowed_characters_as_string) {
            allowed_characters.emplace(std::string(1, character));
        }
    }

    return allowed_characters;
}

void fill_dictionary(wordfinder::dictionary::Dictionary* dictionary) {
    dictionary->add_word("cat");
    dictionary->add_word("car");
    dictionary->add_word("cart");
    dictionary->add_word("corn");
    dictionary->add_word("alpha");
    dictionary->add_word("art");
    dictionary->add_word("rat");
    dictionary->add_word("tar");
}

void fill_grid(wordfinder::grid::Grid& grid) {
    grid.fill_cell(wordfinder::grid::Position(0, 0), std::vector<std::string>{ "c" });
    grid.fill_cell(wordfinder::grid::Position(0, 1), std::vector<std::string>{ "a" });
    grid.fill_cell(wordfinder::grid::Position(1, 0), std::vector<std::string>{ "r" });
    grid.fill_cell(wordfinder::grid::Position(1, 1), std::vector<std::string>{ "t" });
}

int main() {
    using namespace wordfinder::grid;
    using namespace wordfinder::dictionary;

    std::unique_ptr<Dictionary> dictionary = std::make_unique<TrieDictionaryContainer>(get_allowed_characters());
    GridSize grid_size(ROW_COUNT, COLUMN_COUNT);
    std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder = std::make_unique<DiagonalAdjacentPositionsFinder>(grid_size);

    fill_dictionary(dictionary.get());

    Grid grid(grid_size, std::move(adjacent_positions_finder), std::move(dictionary), MINIMUM_WORD_LENGTH);

    fill_grid(grid);

    std::vector<std::string> combinations(grid.find_words());

    for (const std::string& combination : combinations) {
        std::cout << combination << std::endl;
    }

    return 0;
}
