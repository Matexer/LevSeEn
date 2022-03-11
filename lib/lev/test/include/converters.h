#pragma once
#include <gtest/gtest.h>
#include <string>

template <class internT, class externT, class stateT>
struct codecvt : std::codecvt<internT,externT,stateT>
{ ~codecvt(){} };

extern std::wstring_convert<::codecvt<char16_t,char,std::mbstate_t>, char16_t> convert16;
extern std::wstring_convert<::codecvt<char32_t,char,std::mbstate_t>, char32_t> convert32;
