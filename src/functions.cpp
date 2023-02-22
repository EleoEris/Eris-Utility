#include <unordered_map>
#include <string>
#include <fstream>
#include <regex>

#include "Eris_Utility/functions.h"

namespace EUfuncs {

bool str2bool(std::string str) { // needs a copy because it modifies it
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	if (str == "true" || str == "1") {
		return true;
	} else if (str == "false" || str == "0") {
		return false;
	} else {
		throw std::invalid_argument( "The string doesn't conform to neither true nor false");
	}
}

bool str2bool(const char* str) {
	char str_bak[6] = { '\0', '\0', '\0', '\0', '\0', '\0' };

	for (char i = 0; i < 6; i++) {
		if (str[i] == '\0') {
			break;
		}
		str_bak[i] = ::tolower(str[i]);
	}

	if ((std::strcmp(str_bak, "true") == 0) || (std::strcmp(str_bak, "1") == 0)) {
		return true;
	}
	if ((std::strcmp(str_bak, "false") == 0) || (std::strcmp(str_bak, "0") == 0)) {
		return false;
	}
	throw std::invalid_argument("The char array doesn't conform to neither true nor false.");
}

std::unordered_map<std::string, std::string> mapFromIni(std::string path, int maxSettings, std::string errorKey) {
	std::ifstream ifs = std::ifstream(path);
	// 255 seems like a decent number (default value in constructor)
	int counter = 0; 

	std::string line = std::string();
	std::unordered_map<std::string, std::string> retval = std::unordered_map<std::string, std::string>();
	
	std::regex match_pattern = std::regex("^([a-zA-Z0-9_\\-]*)(?:\\s*(?:\\\\t)*\\s*=\\s*(?:\\\\t)*\\s*)([a-zA-Z0-9_\\-]*)", std::regex_constants::optimize);
	std::smatch match = std::smatch();

	retval.insert_or_assign(errorKey, "");

	if (ifs.is_open()) {
		while (ifs.good()) {
			std::getline(ifs, line);
			std::regex_search(line, match, match_pattern);
			if (match.size() == 3) { // match[0] is the whole line
				counter++;
				retval.insert_or_assign(match[1], match[2]);
			}
			if (counter > maxSettings) {
				retval.insert_or_assign(errorKey, "Too many lines in settings!");
				break;
			}
		}
	} else {
		retval.insert_or_assign(errorKey, "Could not load the file! ifs.is_open() == false");
	}
	ifs.close();

	return retval;
}

}