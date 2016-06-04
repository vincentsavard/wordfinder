#include "grid/grid.h"
#include "grid/grid_size.h"
#include "grid/position.h"
#include "grid/adjacent_indices_finder/diagonal_adjacent_positions_finder.h"
#include "dictionary/dictionary.h"
#include "dictionary/trie.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

constexpr const size_t ROW_COUNT = 2;
constexpr const size_t COLUMN_COUNT = 2;
constexpr const size_t MINIMUM_WORD_LENGTH = 3;
constexpr const char* ALLOWED_CHARACTERS = "abcdefghijklmnopqrstuvwxyz";

std::unordered_set<std::string> get_allowed_characters() {
    static const std::string allowed_characters_as_string = ALLOWED_CHARACTERS;
    static std::unordered_set<std::string> allowed_characters;

    if (allowed_characters.empty()) {
        for (const char character : allowed_characters_as_string) {
            allowed_characters.emplace(std::string(1, character));
        }
    }

    return allowed_characters;
}

void fill_dictionary(wordfinder::dictionary::Dictionary* dictionary, const std::string& filepath) {
    std::ifstream file_stream(filepath);
    std::string current_line;

    while (std::getline(file_stream, current_line)) {
        if (!current_line.empty()) {
            dictionary->add_word(current_line);
        }
    }
}

void fill_grid(wordfinder::grid::Grid* grid) {
    grid->fill_cell(wordfinder::grid::Position(0, 0), std::vector<std::string>{ "c" });
    grid->fill_cell(wordfinder::grid::Position(0, 1), std::vector<std::string>{ "a" });
    grid->fill_cell(wordfinder::grid::Position(1, 0), std::vector<std::string>{ "r" });
    grid->fill_cell(wordfinder::grid::Position(1, 1), std::vector<std::string>{ "t" });
}

std::unique_ptr<wordfinder::dictionary::Dictionary> build_dictionary(const std::string& filepath) {
    using namespace wordfinder::dictionary;

    std::unique_ptr<Dictionary> dictionary = std::make_unique<TrieDictionaryContainer>(get_allowed_characters());
    fill_dictionary(dictionary.get(), filepath);

    return std::move(dictionary);
}

std::unique_ptr<wordfinder::grid::Grid> build_grid(std::unique_ptr<wordfinder::dictionary::Dictionary> dictionary) {
    using namespace wordfinder::grid;

    GridSize grid_size(ROW_COUNT, COLUMN_COUNT);
    std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder = std::make_unique<DiagonalAdjacentPositionsFinder>(grid_size);
    std::unique_ptr<Grid> grid = std::make_unique<Grid>(grid_size, std::move(adjacent_positions_finder), std::move(dictionary), MINIMUM_WORD_LENGTH);

    fill_grid(grid.get());

    return std::move(grid);
}

int main(int argc, char* argv[]) {
    using namespace wordfinder::grid;
    using namespace wordfinder::dictionary;

    if (argc < 2) {
        std::cout << "usage: wordfinder.exe DICTIONARY" << std::endl;
        std::cout << "A DICTIONARY is a path to the file containing the words." << std::endl;
        return 1;
    }

    std::string dictionary_filepath(argv[1]);
    std::unique_ptr<Dictionary> dictionary = std::move(build_dictionary(dictionary_filepath));
    std::unique_ptr<Grid> grid = std::move(build_grid(std::move(dictionary)));

    std::vector<std::string> words_found(grid->find_words());

    for (const std::string& combination : words_found) {
        std::cout << combination << std::endl;
    }

    return 0;
}
