#include "trie_node.h"

namespace wordfinder {
namespace dictionary {

TrieNode::TrieNode(std::string value) 
	: value(value)
	, is_word(false)
{}

TrieNode::~TrieNode() noexcept {
	for (auto& pair : children) {
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
	return children.find(character) != children.end();
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

std::size_t TrieNode::hash() const {
	return std::hash<std::string>()(value);
}

}
}
