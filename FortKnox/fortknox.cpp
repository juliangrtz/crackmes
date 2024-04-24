#include <iostream>
#include <Windows.h>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "obfuscation.h"
#include "junk.h"
#include "stringcrypter.h"
#include "hidecall.h"
#include "anti_disas.h"
#include "anti_dbg.h"

std::string usernamePrompt, passwordPrompt;

void checkSecurity() {
	if (security::check_security() != security::internal::debug_results::none) {
		__asm {
		byebye:
			push 0xFFFFFFFF;
			call malloc
				test eax, eax
				jnz byebye
		}
	}
}

void setupStrings() {
	usernamePrompt = make_string("Username: ", 'X');
	passwordPrompt = make_string("Password: ", 'A');
}

unsigned int hash(const std::string& str) {
	unsigned int hashValue = 0;
	for (char c : str) {
		hashValue = (hashValue * 31) + c;
	}
	return hashValue;
}

std::string generatePassword(const std::string& username) {
	DEATHRAYS;
	STATIC_HIDE_CALL(&checkSecurity);

	unsigned int usernameHash = hash(username);
	unsigned int passwordHash = usernameHash;

	PUSH_POP_GARBAGE; PUSH_POP_GARBAGE; PUSH_POP_GARBAGE; PUSH_POP_GARBAGE; PUSH_POP_GARBAGE;

	for (int i = 0; i < 10; ++i) {
		passwordHash ^= (usernameHash << (i % 16));
		STATIC_HIDE_CALL(&checkSecurity);
		passwordHash += 0x3F;
		passwordHash *= 0x3E;
		passwordHash &= 0xFFFF;
		passwordHash ^= 0xAAAA;
	}

	STATIC_HIDE_CALL(&checkSecurity);

	std::stringstream ss;
	ss << std::hex << passwordHash;
	std::string password = ss.str();

	return password;
}

bool check(std::string username, std::string password) {
	STATIC_HIDE_CALL(&checkSecurity);
	return generatePassword(username) == password;
}

void fortKnox() {
	ROGUE_BYTE;
	STATIC_HIDE_CALL(&checkSecurity);
	DEATHRAYS;

	setupStrings();
	std::string username, password;

	std::cout << usernamePrompt;
	DEATHRAYS;
	std::cin >> username;
	std::cout << passwordPrompt;

	STATIC_HIDE_CALL(&checkSecurity);

	std::cin >> password;
	DEATHRAYS;

	if (STATIC_HIDE_CALL(&check, username, password)) {
		std::cout << make_string("flag{w3ll_d0ne_y0u_g0t_m3}", 'A');
	}
	else {
		std::cout << make_string("That is not a valid combination.", 'X');
	}

	DEATHRAYS;
}

int main(int argc, char* argv[]) {
	// A little message for reverse engineers ;)
	WATERMARK("Get the fuck out of here.");

	// Confuse disassembly
	ROGUE_BYTE_2;

	// Garbage code
	if ((argc + 1) * 0x1239 == 0) {
		DEATHRAYS;

		if (argc % 5000 < 1) {
			SEMANTIC_NOP_2;
			PUSH_POP_GARBAGE;

			for (int i = 0; i < argc; i++) {
				SEMANTIC_NOP_2;
			}
			DEATHRAYS;
			SEMANTIC_NOP_2;
		}
		FUCK_YOU_MSG;
	}
	else if (argc > 0 && strlen(argv[0]) > 3 && (argv[0][0] == '@' || argv[0][1] == 'x' || argv[0][2] == 'U')) {
		SEMANTIC_NOP_2;
		SEMANTIC_NOP_1;
		DEATHRAYS;

		STATIC_HIDE_CALL(&checkSecurity);
		DYNAMIC_HIDE_CALL(&fortKnox);
	}
	else {
		DEATHRAYS;

		STATIC_HIDE_CALL(&checkSecurity);
		DYNAMIC_HIDE_CALL(&fortKnox);
	}
}
