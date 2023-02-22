#pragma once

template<typename Fu, typename Fi, typename H, typename B>
void Log::info(Fu func_name, Fi file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[36m[" << _Time::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";

			logFile << std::left
				<< "[" << _Time::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		if (verboseLevel == FullVerbose && buf[0] != '\0') {
			std::cout	<< buf << "\n";
			logFile		<< buf << "\n";
		}
		std::cout << "\x1B[36m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}

template<typename Fu, typename Fi, typename H>
void Log::info(Fu func_name, Fi file_name, int codeline, H head) {
	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[36m[" << _Time::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";

			logFile << std::left
				<< "[" << _Time::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(INFO)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[36m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}



template<typename Fu, typename Fi, typename H, typename B>
void Log::success(Fu func_name, Fi file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[32m[" << _Time::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << _Time::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		if (verboseLevel == FullVerbose && buf[0] != '\0') {
			std::cout	<< buf << "\n";
			logFile		<< buf << "\n";
		}
		std::cout << "\x1B[32m" << this->line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}

template<typename Fu, typename Fi, typename H>
void Log::success(Fu func_name, Fi file_name, int codeline, H head) {
	if (showThreatLevel == InfoLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[32m[" << _Time::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << _Time::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(SUCCESS)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[32m" << this->line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}



template<typename Fu, typename Fi, typename H, typename B>
void Log::warn(Fu func_name, Fi file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (showThreatLevel >= WarningLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[33m[" << _Time::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << _Time::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		if (verboseLevel == FullVerbose && buf[0] != '\0') {
			std::cout	<< buf << "\n";
			logFile		<< buf << "\n";
		}
		std::cout << "\x1B[33m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";

		logFile.flush();
	}
}

template<typename Fu, typename Fi, typename H>
void Log::warn(Fu func_name, Fi file_name, int codeline, H head) {
	if (showThreatLevel >= WarningLvl) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[33m[" << _Time::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << _Time::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(WARNING)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[33m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";

		logFile.flush();
	}
}



template<typename Fu, typename Fi, typename H, typename B>
void Log::error(Fu func_name, Fi file_name, int codeline, H head, B body, ...) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (verboseLevel >= LowVerbose) {
		std::cout << std::left 
			<< "\x1B[31m[" << _Time::s_time.getNowStr() << "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\033[0m\n";
		logFile << std::left
			<< "[" << _Time::s_time.getNowStr()<< "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\n";
	}
	if (verboseLevel == FullVerbose && buf[0] != '\0') {
		std::cout	<< buf << "\n";
		logFile		<< buf << "\n";
	}
	std::cout << "\x1B[31m" << line << "\033[0m\n\n";
	logFile << line << "\n\n";
	logFile.flush();
}

template<typename Fu, typename Fi, typename H>
void Log::error(Fu func_name, Fi file_name, int codeline, H head) {
	if (verboseLevel >= LowVerbose) {
		std::cout << std::left 
			<< "\x1B[31m[" << _Time::s_time.getNowStr() << "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\033[0m\n";
		logFile << std::left
			<< "[" << _Time::s_time.getNowStr()<< "]  "
			<< std::setw(15) << "(ERROR)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head	<< "\n";
	}
	if (verboseLevel == FullVerbose && buf[0] != '\0') {
		std::cout	<< body << "\n";
		logFile		<< body << "\n";
	}
	std::cout << "\x1B[31m" << line << "\033[0m\n\n";
	logFile << line << "\n\n";
	logFile.flush();
}



template<typename Fu, typename Fi, typename H, typename B>
void Log::assert_(Fu func_name, Fi file_name, int codeline, bool condition, H head, B body, ...) {
if (condition) {
	char buf[256];

	if constexpr (std::is_same_v<B, const char*>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body, args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else if constexpr (std::is_same_v<B, std::string>) {
		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body.c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	} else {
		std::ostringstream body_os; // convert body to string since we need to do a string check
		body_os << body;

		va_list args;
		va_start(args, body);
		const int r = std::vsnprintf(buf, sizeof buf, body_os.str().c_str(), args);
		va_end(args);
		if (r < 0)
			throw std::invalid_argument("Could not convert body. Isn't it too long? (over 255 chars)");
	}

	if (verboseLevel >= LowVerbose) {
		std::cout << std::left
			<< "\x1B[31m[" << _Time::s_time.getNowStr() << "]  "
			<< std::setw(15) << "(ASSERTION)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head << "\033[0m\n";
		logFile << std::left
			<< "[" << _Time::s_time.getNowStr() << "]  "
			<< std::setw(15) << "(ASSERTION)"
			<< std::setw(65) << func_name
			<< file_name << ":" << codeline << "\n"
			<< head << "\n";
	}
	if (verboseLevel == FullVerbose && buf[0] != '\0') {
		std::cout	<< buf << "\n";
		logFile		<< buf << "\n";
	}
	std::cout << "\x1B[31m" << line << "\033[0m\n\n";
	logFile << line << "\n\n";
	logFile.flush();
}
}

template<typename Fu, typename Fi, typename H>
void Log::assert_(Fu func_name, Fi file_name, int codeline, bool condition, H head) {
	if (condition) {
		if (verboseLevel >= LowVerbose) {
			std::cout << std::left 
				<< "\x1B[31m[" << _Time::s_time.getNowStr() << "]  "
				<< std::setw(15) << "(ASSERTION)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\033[0m\n";
			logFile << std::left
				<< "[" << _Time::s_time.getNowStr()<< "]  "
				<< std::setw(15) << "(ASSERTION)"
				<< std::setw(65) << func_name
				<< file_name << ":" << codeline << "\n"
				<< head	<< "\n";
		}
		std::cout << "\x1B[31m" << line << "\033[0m\n\n";
		logFile << line << "\n\n";
		logFile.flush();
	}
}
