function getDistance8(pattern, word) {
    let patternBuffer = Module._malloc(pattern.length + 1);
    Module.stringToUTF8(pattern, patternBuffer, pattern.length);

    let wordBuffer = Module._malloc(word.length + 1);
    Module.stringToUTF8(word, wordBuffer, word.length);

    let result = Module.ccall(
        'getDistance8',  // name of C function
        'number',  // return type
        ['number', 'number', 'number', 'number'],  // argument types
        [patternBuffer, wordBuffer, pattern.length, word.length]  // arguments
    );

    Module._free(patternBuffer);
    Module._free(wordBuffer);

    return result;
}