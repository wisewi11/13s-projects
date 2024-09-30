#include "hangman_helpers.h"

int main() {
	char lower_a = 'a';
	char upper_a = 'A';

	assert(is_lowercase_letter(lower_a), "is lower case didnt detect lower a");
	assert(!is_lowercase_letter(upper_a), "is lower case didnt detect upper a");

	return 0;
}
