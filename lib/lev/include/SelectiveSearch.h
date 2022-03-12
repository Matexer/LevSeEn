#pragma once

#include "Search.h"
#include "Filter.h"


namespace Levenshtein {


template<typename StringT, typename CharT, typename SizeT>
class SelectiveSearch : protected Filter<StringT, CharT, SizeT> {

};


}