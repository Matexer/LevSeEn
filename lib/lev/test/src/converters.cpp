#include <gtest/gtest.h>
#include <string>

#include "converters.h"

std::wstring_convert<codecvt<char16_t,char,std::mbstate_t>, char16_t> convert16;
std::wstring_convert<codecvt<char32_t,char,std::mbstate_t>, char32_t> convert32;