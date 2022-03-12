#pragma once
#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <iostream>


template <class internT, class externT, class stateT>
struct codecvt : std::codecvt<internT,externT,stateT>
{ ~codecvt(){} };

extern std::wstring_convert<::codecvt<char16_t,char,std::mbstate_t>, char16_t> convert16;
extern std::wstring_convert<::codecvt<char32_t,char,std::mbstate_t>, char32_t> convert32;


template<typename StringT, typename CharT>
StringT loadText(std::string path, int length) {
    std::basic_ifstream<CharT> ifs(path, std::ifstream::in);
    if (!ifs) std::cerr << "Nie można załadować pliku " << path;
    CharT out[length];
    ifs.read(out, length);
    return StringT(out, length);
}