#include <chrono>
#include <string>
#include "Eris_Utility/_Time.h"

_Time::_Time(char* format) : format(format) {
	raw_time	= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&tm_time, &raw_time);
	strftime(buffer, sizeof(buffer), format, &tm_time);
	str			= buffer;
}

_Time::_Time() {
	format				= "%d %b %Y - %H:%M:%S";
	raw_time			= std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&tm_time, &raw_time);
	strftime(buffer, sizeof(buffer), format, &tm_time);
	str					= buffer;
}

void _Time::now() {
	raw_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	localtime_s(&tm_time, &raw_time);
	strftime(buffer, sizeof(buffer), format, &tm_time);
	str = buffer;
}

void _Time::changeFormat(char* newFormat) {
	format = newFormat;
	strftime(buffer, sizeof(buffer), format, &tm_time);
	str = buffer;
}

_Time& _Time::s_file = _Time("%Y-%m-%d_%H-%M-%S");
_Time& _Time::s_programStartTime = _Time("%Y-%m-%d_%H-%M-%S");
_Time& _Time::s_datetime = _Time();
_Time& _Time::s_date = _Time("%d %b %Y");
_Time& _Time::s_time = _Time("%H:%M:%S");

