# Eris-Log
This is going to make the logs pretty. Documentation WIP

This has not been tested with multithreading. I have yet to implement mutexes and similar safeguards.    
Yet to be tested on Linux and MacOS.
## To do in the future:
- Make it safe for multithreading
- Create variadic template with syntax like this: Log::Get().info(func_name, file_name, line, "Head{0}|Body{1}:{2}{1}-{0}", arg0, arg1, arg2)
- Make a seperate namespace
## Documentation
#### Log.h
Log is a singleton, you can access it with Log.Get()
- `void setLevel(uint8_t threatLevel, uint8_t verboseLevel)`    - used to set levels as below
- `const enum Log::ThreatLevels : uint8_t { ErrorLvl, WarningLvl, InfoLvl }`     
`ThreatLevels Log::showThreatLevel`    - it tells Log to display only logs above a certain level 
- `const enum VerboseLevels : uint8_t { NoVerbose, LowVerbose, FullVerbose }`      
`VerboseLevels Log::verboseLevel`    - it tells Log to display nothing, only the head or both head and body of the messages
- 	`template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>`    
	`void info(Fu func_name, Fi file_name, int line, H head, B body, ...);`    - print a message with the name of the function from which it was called, the filename:line of the output, a colored header and a body. (You can change the parameters at your own leisure, it's only a proposition)      
  same goes for LOG::warn(), LOG::success() and LOG::warn()    
  `Log::assert` is completely the same but takes `bool condition` as parameter before head, it will print only if condition is true. !!! It doesn't actually assert !!!    
  I highly suggest using a macro that will call a platform-specific assert together with Log::assert or use my macro LOG_ASSERT
#### _Time.h
#### functions.h


Define `PREMADE_MACROS` if you want to have the macros written by me
