#pragma once

class _Time {
private:
	time_t raw_time;
	tm tm_time;

#	pragma warning( suppress : 4251 )
	std::string str;
	char* format;
	char buffer[32];
public:
	_Time(char* format);
	_Time();
	void now();
	void changeFormat(char* newFormat);
	inline const std::string&	getNowStr()		{ now(); return this->str; };
	inline const std::string&	getStr() const	{ return this->str; }
	inline const time_t&		getRaw() const	{ return this->raw_time; }
	inline const tm&			getTm()	 const	{ return this->tm_time; }

	static _Time& s_programStartTime;
	static _Time& s_datetime;
	static _Time& s_file;
	static _Time& s_date;
	static _Time& s_time;
};
