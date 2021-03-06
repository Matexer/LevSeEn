#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "lev.h"
#include "SearchEngine.h"
#include "structs.h"


using namespace emscripten;


template<typename EngineT>
class_<EngineT> register_engine(const char* name) {
    return class_<EngineT>(name)
            .class_function("lookFor", &EngineT::lookFor)
            .class_function("filtrationEfficiency", &EngineT::filtrationEfficiency)
            .class_function("setDeletionCost", &EngineT::setDeletionCost)
            .class_function("setInsertionCost", &EngineT::setInsertionCost)
            .class_function("setSwapCost", &EngineT::setSwapCost)
            .class_function("setPurifyRange", &EngineT::setPurifyRange)
            .class_function("setFixRange", &EngineT::setFixRange)
            .class_function("setMultiThreading", &EngineT::setMultiThreading)
            .class_function("setMultiThreadingMinComplexity", &EngineT::setMultiThreadingMinComplexity)
            .class_function("setMaxNumOfThreads", &EngineT::setMaxNumOfThreads);
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
        register_engine<SearchEngineStr8>("SearchEngineUTF8Size8");
        register_engine<SearchEngine16Str8>("SearchEngineUTF16Size8");
        register_engine<SearchEngine32Str8>("SearchEngineUTF32Size8");

        register_engine<SearchEngineStr16>("SearchEngineUTF8Size16");
        register_engine<SearchEngine16Str16>("SearchEngineUTF16Size16");
        register_engine<SearchEngine32Str16>("SearchEngineUTF32Size16");

        register_engine<SearchEngineStr32>("SearchEngineUTF8Size32");
        register_engine<SearchEngine16Str32>("SearchEngineUTF16Size32");
        register_engine<SearchEngine32Str32>("SearchEngineUTF32Size32");
}