#ifndef TRIE_HEADER_GUARD
#define TRIE_HEADER_GUARD

#include "dictionary.h"

#include <memory>
#include <string>
#include <unordered_set>

namespace wordfinder {
namespace dictionary {

class TrieNode;

class TrieDictionary : public Dictionary {
public:
    TrieDictionary(const std::unordered_set<std::string>& allowed_characters);
    TrieDictionary(const TrieDictionary& grid) = delete;
    TrieDictionary& operator=(TrieDictionary grid) = delete;

    virtual void add_word(const std::string& word) override;
    virtual bool word_exists(const std::string& word) const noexcept override;
    virtual bool radix_exists(const std::string& radix) const noexcept override;

private:
    TrieNode* find_node_for_radix(const std::string& radix) const noexcept;
    bool is_word_allowed(const std::string& word) const noexcept;

    std::unique_ptr<TrieNode> root;
    std::unordered_set<std::string> allowed_characters;
};

}
}

#endif
