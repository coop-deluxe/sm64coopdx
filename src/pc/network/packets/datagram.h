#ifndef DATAGRAM_H
#define DATAGRAM_H

#include "types.h"
#include "pc/platform.h"

#include <PR/ultratypes.h>

#include <assert.h>
#include <time.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BUFFER_LENGTH 200
#define MAX_DECOMPRESS_LENGTH 5000

union f32_bits {
    u32  u;
    f32  f;
};

union f64_bits {
    u64  u;
    f64  f;
};

struct Datagram {
    u32 length;
    u32 cursor; // For read iteration.
    union {
        u8 *addr;
        u8 buffer[BUFFER_LENGTH];
    };
    u8 flags;
};
typedef struct Datagram Datagram;

/* |description|
Initializes a Datagram to the default state and prepares it for use.
|descriptionEnd| */
OPTIMIZE_O3 void datagram_init(struct Datagram *dg);

/* |description|
Clears a Datagram and resets it to the default state for use.
Returns false on failure.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_clear(struct Datagram *dg);

/* |description|
Copies the contents and state of Datagram A into Datagram B.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_copy(struct Datagram *a, struct Datagram *b);

/* |description|
Truncates the Datagram by the amount specified by length.
Returns false on failure.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_truncate(struct Datagram *dg, u32 length);

/* |description|
Generates a hash for the amount of contents in the Datagram specified by the length.
|descriptionEnd| */
OPTIMIZE_O3 u32 datagram_hash(struct Datagram *dg, u32 length);

/* |description|
Seeks (Moves the cursor) to the specified position in the Datagram.
Returns false on failure.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_seek(struct Datagram *dg, u32 offset);

/* |description|
Appends data to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_append_data(struct Datagram *dg, void *data, u32 length);

/* |description|
Reads data from the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_read_data(struct Datagram *dg, void *data, u32 length);

/* |description|
Writes data to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_write_data(struct Datagram *dg, void *data, u32 length);

/* |description|
Adds the amount of empty padding specified to the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_add_padding(struct Datagram *dg, u32 length);

/* |description|
Returns a copy of all the contents in the Datagram.
Returns NULL if there is no contents or if the Datagram state is invalid.
! UNSAFE for LUA usage without a custom function. !
|descriptionEnd| */
OPTIMIZE_O3 u8 *datagram_get_message(struct Datagram *dg);

/* |description|
Returns a copy of all the contents after the current cursor 
position in the Datagram.
Returns NULL if there is no contents or if the Datagram state is invalid.
! UNSAFE for LUA usage without a custom function. !
|descriptionEnd| */
OPTIMIZE_O3 u8 *datagram_get_remaining_bytes(struct Datagram *dg);

/* |description|
Compresses the contents inside of the Datagram, All of the old contents will be 
replaced with the now compressed contents.
Returns TRUE on success or FALSE on failure.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_compress(struct Datagram *dg);

/* |description|
Decompresses the contents inside of the Datagram, All of the old contents will be 
replaced with the now decompressed contents.
Returns TRUE on success or FALSE on failure.
Error flag will also be set on failure to decompress as the Datagram will be left 
in a invalid state, Please use datagram_clear() to reset the Datagram.
|descriptionEnd| */
OPTIMIZE_O3 bool datagram_decompress(struct Datagram *dg);

// Include the INLINE functions.
#include "datagram.inl"

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // DATAGRAM_H
