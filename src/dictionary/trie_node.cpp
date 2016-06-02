#include "trie_node.h"

namespace wordfinder {
namespace dictionary {

TrieNode::TrieNode(std::string value) 
	: value(value)
	, is_word(false)
{}

TrieNode::~TrieNode() noexcept {
	for (const std::pair<std::string, TrieNode*>& pair : children) {
		delete pair.second;
	}
}

bool TrieNode::is_a_word() const noexcept {
	return is_word;
}

void TrieNode::mark_as_word() noexcept {
	is_word = true;
}

bool TrieNode::contains_character(const std::string& character) const noexcept {
	return children.find(character) != children.cend();
}

void TrieNode::add_child_for_character(const std::string& character) {
	children.emplace(character, new TrieNode(character));
}

TrieNode* TrieNode::get_child_for_character(const std::string& character) {
	return children.find(character)->second;
}

std::string TrieNode::get_value() const noexcept {
	return value;
}

}
}
