#ifndef DICTIONARY_HEADER_GUARD
#define DICTIONARY_HEADER_GUARD

#include <string>

namespace wordfinder {
namespace dictionary {

class Dictionary {
public:
	virtual ~Dictionary() noexcept {}

	virtual void add_word(const std::string& word) = 0;	
	virtual bool word_exists(const std::string& word) const noexcept = 0;
	virtual bool radix_exists(const std::string& radix) const noexcept = 0;
};

}
}
#endif
