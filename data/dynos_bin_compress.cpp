#include "dynos.cpp.h"
#include <zlib.h>

static const u64 DYNOS_BIN_COMPRESS_MAGIC = 0x4E4942534F4E5944llu;
static FILE  *sFile = NULL;
static Bytef *sBufferUncompressed = NULL;
static Bytef *sBufferCompressed = NULL;
static uLongf sLengthUncompressed = 0;
static uLongf sLengthCompressed = 0;

static inline void DynOS_Bin_Compress_Init() {
    sFile = NULL;
    sBufferUncompressed = NULL;
    sBufferCompressed = NULL;
    sLengthUncompressed = 0;
    sLengthCompressed = 0;
}

static inline void DynOS_Bin_Compress_Close() {
    if (sFile) fclose(sFile);
    sFile = NULL;
}

static inline void DynOS_Bin_Compress_Free() {
    if (sBufferCompressed) free(sBufferCompressed);
    if (sBufferUncompressed) free(sBufferUncompressed);
    DynOS_Bin_Compress_Close();
}

static inline bool DynOS_Bin_Compress_Check(bool condition, const char *function, const char *filename, const char *message) {
    if (!condition) {
        Print("ERROR: %s: File \"%s\": %s", function, filename, message);
        DynOS_Bin_Compress_Free();
        return false;
    }
    return true;
}

bool DynOS_Bin_IsCompressed(const SysPath &aFilename) {
    DynOS_Bin_Compress_Init();

    // Open input file
    if (!DynOS_Bin_Compress_Check(
        (sFile = fopen(aFilename.c_str(), "rb")) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot open file"
    )) return false;

    // Read magic
    u64 _Magic = 0;
    if (!DynOS_Bin_Compress_Check(
        fread(&_Magic, sizeof(u64), 1, sFile) == 1,
        __FUNCTION__, aFilename.c_str(), "Cannot read magic"
    )) return false;

    // Compare with magic constant
    if (_Magic != DYNOS_BIN_COMPRESS_MAGIC) {
        DynOS_Bin_Compress_Free();
        return false;
    }

    // It is a compressed file
    DynOS_Bin_Compress_Free();
    return true;
}

bool DynOS_Bin_Compress(const SysPath &aFilename) {
    DynOS_Bin_Compress_Init();
    PrintNoNewLine("Compressing file \"%s\"...", aFilename.c_str());

    // Open input file
    if (!DynOS_Bin_Compress_Check(
        (sFile = fopen(aFilename.c_str(), "rb")) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot open file"
    )) return false;

    // Retrieve file length
    if (!DynOS_Bin_Compress_Check(
        fseek(sFile, 0, SEEK_END) == 0,
        __FUNCTION__, aFilename.c_str(), "Cannot retrieve file length"
    )) return false;

    // Check file length
    if (!DynOS_Bin_Compress_Check(
        (sLengthUncompressed = (uLongf) ftell(sFile)) != 0,
        __FUNCTION__, aFilename.c_str(), "Empty file"
    )) return false;

    // Allocate memory for uncompressed buffer
    if (!DynOS_Bin_Compress_Check(
        (sBufferUncompressed = (Bytef *) calloc(sLengthUncompressed, sizeof(Bytef))) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot allocate memory for compression"
    )) return false; else rewind(sFile);

    // Read input data
    if (!DynOS_Bin_Compress_Check(
        fread(sBufferUncompressed, sizeof(Bytef), sLengthUncompressed, sFile) == sLengthUncompressed,
        __FUNCTION__, aFilename.c_str(), "Cannot read uncompressed data"
    )) return false; else DynOS_Bin_Compress_Close();

    // Compute maximum output file size
    if (!DynOS_Bin_Compress_Check(
        (sLengthCompressed = compressBound(sLengthUncompressed)) != 0,
        __FUNCTION__, aFilename.c_str(), "Cannot compute compressed size"
    )) return false;

    // Allocate memory for compressed buffer
    if (!DynOS_Bin_Compress_Check(
        (sBufferCompressed = (Bytef *) calloc(sLengthCompressed, sizeof(Bytef))) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot allocate memory for compression"
    )) return false;

    // Compress data
    if (!DynOS_Bin_Compress_Check(
        compress2(sBufferCompressed, &sLengthCompressed, sBufferUncompressed, sLengthUncompressed, Z_BEST_COMPRESSION) == Z_OK,
        __FUNCTION__, aFilename.c_str(), "Cannot compress data"
    )) return false;

    // Check output length
    // If the compression generates a bigger file, skip the process, but don't return a failure
    if (!DynOS_Bin_Compress_Check(
        sLengthCompressed < sLengthUncompressed,
        __FUNCTION__, aFilename.c_str(), "Compressed data is bigger than uncompressed; Skipping compression"
    )) return true;

    // Open output file
    if (!DynOS_Bin_Compress_Check(
        (sFile = fopen(aFilename.c_str(), "wb")) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot open file"
    )) return false;

    // Write magic
    if (!DynOS_Bin_Compress_Check(
        fwrite(&DYNOS_BIN_COMPRESS_MAGIC, sizeof(u64), 1, sFile) == 1,
        __FUNCTION__, aFilename.c_str(), "Cannot write magic"
    )) return false;

    // Write uncompressed file size
    if (!DynOS_Bin_Compress_Check(
        fwrite(&sLengthUncompressed, sizeof(uLongf), 1, sFile) == 1,
        __FUNCTION__, aFilename.c_str(), "Cannot write uncompressed file size"
    )) return false;

    // Write compressed data
    if (!DynOS_Bin_Compress_Check(
        fwrite(sBufferCompressed, sizeof(Bytef), sLengthCompressed, sFile) == sLengthCompressed,
        __FUNCTION__, aFilename.c_str(), "Cannot write compressed data"
    )) return false;

    // Done, free buffers and files
    DynOS_Bin_Compress_Free();
    Print(" Done.");
    return true;
}

BinFile *DynOS_Bin_Decompress(const SysPath &aFilename) {
    DynOS_Bin_Compress_Init();

    // Open input file
    if (!DynOS_Bin_Compress_Check(
        (sFile = fopen(aFilename.c_str(), "rb")) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot open file"
    )) return NULL;

    // Read magic
    u64 _Magic = 0;
    if (!DynOS_Bin_Compress_Check(
        fread(&_Magic, sizeof(u64), 1, sFile) == 1,
        __FUNCTION__, aFilename.c_str(), "Cannot read magic"
    )) return NULL;

    // Compare with magic constant
    // If not equal, it's not a compressed file
    if (_Magic != DYNOS_BIN_COMPRESS_MAGIC) {
        DynOS_Bin_Compress_Free();
        return BinFile::OpenR(aFilename.c_str());
    }
    PrintNoNewLine("Decompressing file \"%s\"...", aFilename.c_str());

    // Read expected uncompressed file size
    if (!DynOS_Bin_Compress_Check(
        fread(&sLengthUncompressed, sizeof(uLongf), 1, sFile) == 1,
        __FUNCTION__, aFilename.c_str(), "Cannot read uncompressed file size"
    )) return NULL;

    // Retrieve file length
    if (!DynOS_Bin_Compress_Check(
        fseek(sFile, 0, SEEK_END) == 0,
        __FUNCTION__, aFilename.c_str(), "Cannot retrieve file length"
    )) return NULL;

    // Check file length
    uLongf _LengthHeader = (uLongf) (sizeof(u64) + sizeof(uLongf));
    if (!DynOS_Bin_Compress_Check(
        (sLengthCompressed = (uLongf) ftell(sFile)) >= _LengthHeader,
        __FUNCTION__, aFilename.c_str(), "Empty file"
    )) return NULL;

    // Allocate memory for compressed buffer
    if (!DynOS_Bin_Compress_Check(
        (sBufferCompressed = (Bytef *) calloc(sLengthCompressed - _LengthHeader, sizeof(Bytef))) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot allocate memory for decompression"
    )) return NULL; else fseek(sFile, _LengthHeader, SEEK_SET);

    // Read input data
    if (!DynOS_Bin_Compress_Check(
        fread(sBufferCompressed, sizeof(Bytef), sLengthCompressed - _LengthHeader, sFile) == sLengthCompressed - _LengthHeader,
        __FUNCTION__, aFilename.c_str(), "Cannot read compressed data"
    )) return NULL; else DynOS_Bin_Compress_Close();

    // Allocate memory for uncompressed buffer
    if (!DynOS_Bin_Compress_Check(
        (sBufferUncompressed = (Bytef *) calloc(sLengthUncompressed, sizeof(Bytef))) != NULL,
        __FUNCTION__, aFilename.c_str(), "Cannot allocate memory for decompression"
    )) return NULL;

    // Uncompress data
    int uncompressRc = uncompress(sBufferUncompressed, &sLengthUncompressed, sBufferCompressed, sLengthCompressed);
    if (!DynOS_Bin_Compress_Check(
        uncompressRc == Z_OK,
        __FUNCTION__, aFilename.c_str(), "Cannot uncompress data"
    )) {
        Print("ERROR: uncompress RC: %d", uncompressRc);
        return NULL;
    }

    // Return uncompressed data as a BinFile
    BinFile *_BinFile = BinFile::OpenB(sBufferUncompressed, sLengthUncompressed);
    DynOS_Bin_Compress_Free();
    Print(" Done.");
    return _BinFile;
}
