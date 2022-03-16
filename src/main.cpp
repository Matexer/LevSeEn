#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "SearchEngine.h"
#include "structs.h"


using namespace emscripten;


template<typename EngineT>
class_<EngineT> register_engine(const char* name) {
    return class_<EngineT>(name)
            .class_function("lookFor", &EngineT::lookFor)
            .class_function("setDeletionCost", &EngineT::setDeletionCost)
            .class_function("setInsertionCost", &EngineT::setInsertionCost)
            .class_function("setSwapCost", &EngineT::setSwapCost)
            .class_function("setPurifyRange", &EngineT::setPurifyRange)
            .class_function("setFixRange", &EngineT::setFixRange);
}


template<typename OutputT>
class_<OutputT> register_output(const char* name) {
    return class_<OutputT>(name)
        .constructor<>()
        .property("index", &OutputT::index)
        .property("distance", &OutputT::distance)
        .property("length", &OutputT::length);
}


typedef FixedSearchOutput<uint8_t> FixedSearchOutput8;
typedef FixedSearchOutput<uint16_t> FixedSearchOutput16;
typedef FixedSearchOutput<uint32_t> FixedSearchOutput32;


typedef SearchEngine<std::string, char, uint8_t> SearchEngineStr8;
typedef SearchEngine<std::u16string, char16_t, uint8_t> SearchEngine16Str8;
typedef SearchEngine<std::u32string, char32_t, uint8_t> SearchEngine32Str8;

typedef SearchEngine<std::string, char, uint16_t> SearchEngineStr16;
typedef SearchEngine<std::u16string, char16_t, uint16_t> SearchEngine16Str16;
typedef SearchEngine<std::u32string, char32_t, uint16_t> SearchEngine32Str16;

typedef SearchEngine<std::string, char, uint32_t> SearchEngineStr32;
typedef SearchEngine<std::u16string, char16_t, uint32_t> SearchEngine16Str32;
typedef SearchEngine<std::u32string, char32_t, uint32_t> SearchEngine32Str32;


EMSCRIPTEN_BINDINGS(Ouput) {
        register_vector<FixedSearchOutput<uint8_t>>("vector<FixedOutput8>");
        register_vector<FixedSearchOutput<uint16_t>>("vector<FixedOutput16>");
        register_vector<FixedSearchOutput<uint32_t>>("vector<FixedOutput32>");

        register_output<FixedSearchOutput8>("FixedSearchOutput8");
        register_output<FixedSearchOutput16>("FixedSearchOutput16");
        register_output<FixedSearchOutput32>("FixedSearchOutput32");
}


EMSCRIPTEN_BINDINGS(Engine) {
        register_engine<SearchEngineStr8>("SearchEngineStr8");
        register_engine<SearchEngine16Str8>("SearchEngine16Str8");
        register_engine<SearchEngine32Str8>("SearchEngine32Str8");

        register_engine<SearchEngineStr16>("SearchEngineStr16");
        register_engine<SearchEngine16Str16>("SearchEngine16Str16");
        register_engine<SearchEngine32Str16>("SearchEngine32Str16");

        register_engine<SearchEngineStr32>("SearchEngineStr32");
        register_engine<SearchEngine16Str32>("SearchEngine16Str32");
        register_engine<SearchEngine32Str32>("SearchEngine32Str32");
}