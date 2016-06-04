#include "trie_dictionary.h"
#include "trie_node.h"

#include <algorithm>

namespace wordfinder {
namespace dictionary {

TrieDictionary::TrieDictionary(const std::unordered_set<std::string>& allowed_characters)
    : root(std::make_unique<TrieNode>(""))
    , allowed_characters(allowed_characters)
{}

void TrieDictionary::add_word(const std::string& word) {
    if (!is_word_allowed(word)) {
        return;
    }

    TrieNode* current_node = root.get();

    for (const char c_character : word) {
        std::string character(1, c_character);

        if (!current_node->contains_character(character)) {
            current_node->add_child_for_character(character);
        }

        current_node = current_node->get_child_for_character(character);
    }

    current_node->mark_as_word();
}

bool TrieDictionary::word_exists(const std::string& word) const noexcept {
    TrieNode* node = find_node_for_radix(word);

    return node != nullptr && node->is_a_word();
}

bool TrieDictionary::radix_exists(const std::string& radix) const noexcept {
    return find_node_for_radix(radix) != nullptr;
}

TrieNode* TrieDictionary::find_node_for_radix(const std::string& radix) const noexcept {
    TrieNode* current_node = root.get();

    for (const char c_character : radix) {
        std::string character(1, c_character);

        if (!current_node->contains_character(character)) {
            return nullptr;
        } else {
            current_node = current_node->get_child_for_character(character);
        }
    }

    return current_node;
}

bool TrieDictionary::is_word_allowed(const std::string& word) const noexcept {
    return std::all_of(word.cbegin(), word.cend(), [this](const char character) {
        return allowed_characters.find(std::string(1, character)) != allowed_characters.cend();
    });
}

}
}
