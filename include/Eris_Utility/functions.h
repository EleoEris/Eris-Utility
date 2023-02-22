#pragma once

namespace EUfuncs {

bool str2bool(std::string str);
bool str2bool(const char* str);

std::unordered_map<std::string, std::string> __declspec(dllexport) mapFromIni(std::string path, int maxSettings = 255, std::string errorKey = "INTERNAL_ERROR");

}