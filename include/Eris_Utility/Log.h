#pragma once

//+//	Create variadic template with syntax something like (func_name, "Head{0}|Body{1}:{2}{1}-{0}", arg0, arg1, arg2)

//<3// thanks to https://codereview.stackexchange.com/questions/187183/create-a-c-string-using-printf-style-formatting printf-like variadic templates

#include <fstream>
#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <string>
#include "_Time.h"

#if defined(__linux__) || defined(LINUX)
constexpr char		DIR_DELIMITER		= '/';
const string		NULL_FILE_REDIRECT	= " 2> /dev/null";
#elif				defined(_WIN32)
constexpr char		DIR_DELIMITER		= '\\';
const std::string	NULL_FILE_REDIRECT	= " 2> nul";
#else
#error				_WIN32, __linux__ and LINUX undefined - system not recognized
#endif // defined(__linux__) or defined(LINUX)

//<3// thanks to https://stackoverflow.com/a/8488201/16614732 for the line below
#define __LOG_FILENAME__ (std::strrchr(__FILE__, DIR_DELIMITER) ? std::strrchr(__FILE__, DIR_DELIMITER) + 1 : __FILE__)

#ifdef				_DEBUG
constexpr char		LOG_DEBUG_CHAR		= 'D';		// D if debug, R if release
#else				// !_DEBUG
constexpr char		LOG_DEBUG_CHAR		= 'R';		// D if debug, R if release
#endif

class Log {
public:
	Log(const Log&) = delete;
	~Log();
private:
	const enum ThreatLevels : uint8_t {		// Warning level to log
		ErrorLvl, WarningLvl, InfoLvl
	}; ThreatLevels showThreatLevel;

	const enum VerboseLevels : uint8_t {		// Head, or head and body
		NoVerbose, LowVerbose, FullVerbose
	}; VerboseLevels verboseLevel;

	char logFilePath[100];

#pragma warning(suppress : 4251) // this file will be compiled with the rest of the code so this warning is superfluous
	std::ofstream logFile;

	short bodyLen;			// specifies how many character per line (after 3 tabs)
	char line[120];			// remember to change it each time

	void startup();
	Log(uint8_t threatLevel = 2, uint8_t verboseLevel = 2);
	static Log instance;

public:
	static Log& Get();

	inline void setLevel(uint8_t threatLevel, uint8_t verboseLevel) {
		this->showThreatLevel = (ThreatLevels)threatLevel;
		this->verboseLevel = (VerboseLevels)verboseLevel;
	}
	inline void setThreatLevel(uint8_t threatLevel) { this->showThreatLevel = (ThreatLevels)threatLevel; }
	inline void setVerboseLevel(uint8_t verbLevel) { this->showThreatLevel = (ThreatLevels)verbLevel; }

	// definitions in Log.tpp since they're templates
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void info(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void info(Fu func_name, Fi file_name, int line, H head);


	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void success(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void success(Fu func_name, Fi file_name, int line, H head);


	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void warn(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void warn(Fu func_name, Fi file_name, int line, H head);


	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void error(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void error(Fu func_name, Fi file_name, int line, H head);

	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void assert_(Fu func_name, Fi file_name, int line, bool condition, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void assert_(Fu func_name, Fi file_name, int line, bool condition, H head);
};

#include "../src/Log.tpp"

#ifdef PREMADE_MACROS

// ErisUtility _Time
#define			T_PROGRAM_START_TIME			_Time::s_programStartTime.getStr()		// returns string&, safe for file naming
#define			T_FILE_STR						_Time::s_file.getNowStr()				// returns string&, safe for file naming
#define			T_DATE_STR						_Time::s_date.getNowStr()				// returns string& with current date
#define			T_DATE_CHG_FORMAT(f)			_Time::s_date.changeFormat(f)			// changes date format
#define			T_TIME_STR						_Time::s_time.getNowStr()				// returns string& with current time
#define			T_TIME_CHG_FORMAT(f)			_Time::s_time.changeFormat(f)			// changes format of time
#define			T_DATETIME_STR					_Time::s_datetime.getNowStr()			// returns string& with current datetime
#define			T_DATETIMET_CHG_FORMAT(f)		_Time::s_datetime.changeFormat(f)		// changes format of datetime

// ErisUtility Log
#define			LOG_SETLEVEL(threat, verb)	Log::Get().setLevel(threat, verb)
#define			LOG_INFO(...)				Log::Get().info(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_WARN(...)				Log::Get().warn(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_SUCC(...)				Log::Get().success(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)	// head, body and args to format body in c-style
#define			LOG_ERR(...)				Log::Get().error(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style

#ifdef			_DEBUG
#define			LOG_INFO_D(...)		Log::Get().info(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_WARN_D(...)		Log::Get().warn(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_SUCC_D(...)		Log::Get().success(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)	// head, body and args to format body in c-style
#define			LOG_ERR_D(...)		Log::Get().error(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style

#define			LOG_INFO_R(...)
#define			LOG_WARN_R(...)
#define			LOG_SUCC_R(...)
#define			LOG_ERR_R(...)
// macros with _R suffix will work in release
#else			// !_DEBUG
#define			LOG_INFO_R(...)				Log::Get().info(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_WARN_R(...)				Log::Get().warn(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_SUCC_R(...)				Log::Get().success(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)	// head, body and args to format body in c-style
#define			LOG_ERR_R(...)				Log::Get().error(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style

#define			LOG_INFO_D(...)
#define			LOG_WARN_D(...)
#define			LOG_SUCC_D(...)
#define			LOG_ERR_D(...)
#endif				// _DEBUG

#endif //PREMADE_MACROS