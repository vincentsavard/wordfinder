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

int main() {
    using namespace wordfinder::grid;
	using namespace wordfinder::dictionary;

    GridSize grid_size(2, 2);
    std::unique_ptr<AdjacentPositionsFinder> adjacent_positions_finder = std::make_unique<DiagonalAdjacentPositionsFinder>(grid_size);
    Grid grid(grid_size, std::move(adjacent_positions_finder));

    grid.fill_cell(Position(0, 0), std::vector<std::string>{ "A" });
    grid.fill_cell(Position(0, 1), std::vector<std::string>{ "B" });
    grid.fill_cell(Position(1, 0), std::vector<std::string>{ "C" });
    grid.fill_cell(Position(1, 1), std::vector<std::string>{ "D" });

    std::vector<std::string> combinations(grid.generate_combinations());

    for (const std::string& combination : combinations) {
        std::cout << combination << std::endl;
    }

	std::unique_ptr<Dictionary> dictionary = std::make_unique<TrieDictionaryContainer>(get_allowed_characters());

	dictionary->add_word("cat");
	dictionary->add_word("cat");
	dictionary->add_word("car");
	dictionary->add_word("corn");
	dictionary->add_word("alpha");
	dictionary->add_word("aujourd'hui");
	dictionary->add_word("sur-le-champ");

	std::cout << dictionary->word_exists("abc") << std::endl;
	std::cout << dictionary->radix_exists("ab") << std::endl;
	std::cout << dictionary->word_exists("ab") << std::endl;

    return 0;
}
