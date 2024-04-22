#include <iostream>
#include <Windows.h>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "obf.h"
#include "junk.h"
#include "stringcrypter.h"
#include "hidecall.h"
#include "anti_disas.h"
#include "anti_dbg.h"
#include <filesystem>

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
	usernamePrompt = make_string3("Username: ");
	passwordPrompt = make_string("Password: ");
}

unsigned int hash(const std::string& str) {
	unsigned int hashValue = 0;
	for (char c : str) {
		hashValue = (hashValue * 31) + c;
	}
	return hashValue;
}

// Function to generate password from username
std::string generatePassword(const std::string& username) {
	DEATHRAYS;
	STATIC_HIDE_CALL(&checkSecurity);

	unsigned int usernameHash = hash(username);
	unsigned int passwordHash = usernameHash;

	PUSH_POP_GARBAGE; PUSH_POP_GARBAGE; PUSH_POP_GARBAGE; PUSH_POP_GARBAGE; PUSH_POP_GARBAGE;

	// Apply iterative hashing and bitwise operations to derive password
	for (int i = 0; i < 10; ++i) {
		passwordHash ^= (usernameHash << (i % 16));
		STATIC_HIDE_CALL(&checkSecurity);
		passwordHash += 0x3F;
		passwordHash *= 0x3E;
		passwordHash &= 0xFFFF;
		passwordHash ^= 0xAAAA;
	}

	// Convert password hash to hexadecimal string
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
		std::cout << make_string("flag{w3ll_d0ne_y0u_g0t_m3}");
	}
	else {
		std::cout << make_string3("That is not a valid combination.");
	}

	DEATHRAYS;
}

int main(int argc, char* argv[]) {
	WATERMARK("Get the fuck out of here.");
	ROGUE_BYTE_2;

	if ((argc + 1) * 0x1239 == 0) {
		DEATHRAYS;

		if (argc % 5000 < 1) {
			TWO_BYTE_NOP;
			PUSH_POP_GARBAGE;

			for (int i = 0; i < argc; i++) {
				THREE_BYTE_NOP;
			}
			DEATHRAYS;
			THREE_BYTE_NOP;
		}
		FUCK_YOU_MSG;
	}
	else if (argc > 0 && strlen(argv[0]) > 3 && (argv[0][0] == '@' || argv[0][1] == 'x' || argv[0][2] == 'U')) {
		THREE_BYTE_NOP;
		TWO_BYTE_NOP;
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
