
#include <sstream>
#include <string_view>

#include "Eris_Utility/Log.h"

Log &Log::Get() {
	static Log instance;
	return instance;
}


void Log::startup() {
	//!// May break without correct permissions,
	//!// redirects *all* errors to null (might try to fix later)
	system((std::string("mkdir logs") + DIR_DELIMITER + "console " + NULL_FILE_REDIRECT).c_str());
	logFile.open(logFilePath);

	std::cout << std::boolalpha << std::left;
	std::cout << (LOG_DEBUG_CHAR == 'D' ? "\x1B[35m[DEBUG]\033[0m" : "\x1B[35m[RELEASE]\033[0m") << std::endl;
	std::cout << std::setw(36) << "\x1B[35m[VS STUDIO VERSION]\033[0m" << _MSC_FULL_VER << " (1916: Visual Studio 17)" << std::endl;
	std::cout << std::setw(36) << "\x1B[35m[C++ VERSION]\033[0m" << _MSVC_LANG << std::endl;
	std::cout << std::setw(36) << "\x1B[35m[START DATETIME]\033[0m" << _Time::s_datetime.getNowStr() << std::endl;
	std::cout << "\x1B[35m" << line << "\033[0m\n" << std::endl;

	if (logFile.is_open()) {
		logFile << std::boolalpha << std::left;
		logFile << (LOG_DEBUG_CHAR == 'D' ? "[DEBUG]" : "[RELEASE]") << std::endl;
		logFile << std::setw(36) << "[VS STUDIO VERSION]" << _MSC_FULL_VER << " (1916: Visual Studio 17)" << std::endl;
		logFile << std::setw(36) << "[C++ VERSION]" << _MSVC_LANG << std::endl;
		logFile << std::setw(36) << "[START DATETIME]" << _Time::s_datetime.getNowStr() << std::endl;
		logFile << line << std::endl;
	} else {

		std::cout << std::left 
			<< "\x1B[31m[" << _Time::s_time.getNowStr() << "]  " << "(ERROR)\n"
			<< "FAILED TO OPEN LOG FILE" << "\033[0m\n" << logFilePath << "\n";
		system(std::string("pause" + NULL_FILE_REDIRECT).c_str());
	}
}


Log::Log(uint8_t threatLevel, uint8_t verboseLevel) 
	: showThreatLevel((ThreatLevels)threatLevel)
	, verboseLevel((VerboseLevels)verboseLevel) {
	
#	ifdef OVERWRITE_STL_SYNC
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
#	endif

	bodyLen = 90;
	std::fill(line, line + 120, '_');

	strcpy_s(logFilePath, "logs/console/LOG_");
	strcat_s(logFilePath, _Time::s_programStartTime.getStr().c_str());
	strcat_s(logFilePath, "_");
	strcat_s(logFilePath, &LOG_DEBUG_CHAR);
	strcat_s(logFilePath, ".log");

	this->startup();
}

Log::~Log() {
	info(__FUNCTION__, __LOG_FILENAME__, __LINE__, "Session ended");
	logFile.close();
}
