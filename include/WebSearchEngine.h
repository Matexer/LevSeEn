//#pragma once
//
//#include "SearchEngine.h"
//
//
//class WebSearchEngine {
//    typedef SearchEngine<std::string, char, u_int8_t> SearchEngineStr8;
//    typedef SearchEngine<std::u16string, char16_t, u_int8_t> SearchEngine16Str8;
//    typedef SearchEngine<std::u32string, char32_t, u_int8_t> SearchEngine32Str8;
//
//
//    void setUTF(const std::string& strUTF ) {
//        if (strUTF == "utf-8")
//            this->utf = 8;
//        else if (strUTF == "utf-16")
//            this->utf = 16;
//        else if (strUTF == "utf-32")
//            this->utf = 32;
//    }
//
//    void setMaxDistanceVal(uint32_t maxVal) {
//        if (maxVal < 255)
//            this->distanceSize = 8;
//        else if (maxVal < 65535)
//            this->distanceSize = 16;
//        else if (maxVal < 4294967295)
//            this->distanceSize = 32;
//    }
//
//    u_int8_t utf;
//    u_int8_t distanceSize;
//};