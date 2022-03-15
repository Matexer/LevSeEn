#pragma once
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "SearchEngine.h"


typedef SearchEngine<std::string, char, u_int8_t> SearchEngineStr8;
typedef SearchEngine<std::u16string, char16_t, u_int8_t> SearchEngine16Str8;
typedef SearchEngine<std::u32string, char32_t, u_int8_t> SearchEngine32Str8;


EMSCRIPTEN_BINDINGS(Lev) {
        register_vector<FixedSearchOutput<uint8_t>>("vector<FixedOutput8>");
        register_vector<FixedSearchOutput<uint16_t>>("vector<FixedOutput16>");
        register_vector<FixedSearchOutput<uint32_t>>("vector<FixedOutput32>");

        class_<SearchEngineStr8>("SearchEngineStr8")
        .class_function("lookFor", &SearchEngineStr8::lookFor)
        .class_function("setDeletionCost", &SearchEngineStr8::setDeletionCost)
        .class_function("setInsertionCost", &SearchEngineStr8::setInsertionCost)
        .class_function("setSwapCost", &SearchEngineStr8::setSwapCost)
        .class_function("setPurifyRange", &SearchEngineStr8::setPurifyRange)
        .class_function("setFixRange", &SearchEngineStr8::setFixRange)
        ;
}