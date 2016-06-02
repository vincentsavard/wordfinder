#ifndef TRIE_NODE_HEADER_GUARD
#define TRIE_NODE_HEADER_GUARD

#include <functional>
#include <string>
#include <unordered_map>

namespace wordfinder {
namespace dictionary {

class TrieNode {
public:
	TrieNode(std::string value);
	~TrieNode() noexcept;

	bool is_a_word() const noexcept;
	void mark_as_word() noexcept;
	bool contains_character(const std::string& character) const noexcept;
	void add_child_for_character(const std::string& character);
	TrieNode* get_child_for_character(const std::string& character);
	std::string get_value() const noexcept;

private:
	std::string value;
	bool is_word;
	std::unordered_map<std::string, TrieNode*> children;
};

}
}

#endif
