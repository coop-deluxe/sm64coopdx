#include "dynos.cpp.h"

void SkipBytes(FILE *aFile, size_t amount) {
    // If we're at end of file. There is no more to skip.
    if (feof(aFile)) { return; }
    
    int failure = fseek(aFile, amount, SEEK_CUR);
    // If we failed to skip bytes. Print the error.
    if (failure) { perror("The following error occured when skipping bytes"); }
}