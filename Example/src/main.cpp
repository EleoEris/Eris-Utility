#define PREMADE_MACROS
#include "Eris_Utility/Log.h"

// Log.h contains the following includes:
// #include <fstream>
// #include <cstdarg>
// #include <iomanip>
// #include <iostream>
// #include <string>
// #include "_Time.h"
// I have yet to figure out a way to move them into the .cpp file while maintaining templates

int main() {
	LOG_INFO_R("Custom Info!", "This is an info message that'll only run in release!");
	LOG_INFO_D("Custom Warning!", "This is an info message that'll only run in debug!");
	LOG_ERR("Custom Error!", "This is an error message!");
	LOG_SUCC("This one has no body");
}