#include <stdio.h>
#include <zlib.h>
#include "pc/network/network.h"
#include "pc/network/packets/datagram.h"
#include "pc/debuglog.h"

OPTIMIZE_O3 void datagram_init(struct Datagram *dg) {
    if (!dg) { return; }

    memset(dg, 0, sizeof(struct Datagram));
    dg->flags |= SET_BIT(1, 0); // Initialized
}

OPTIMIZE_O3 bool datagram_clear(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    
    if (dg->length >= BUFFER_LENGTH && dg->addr) { free(dg->addr); }
    memset(dg, 0, sizeof(struct Datagram));
    dg->flags |= SET_BIT(1, 0); // Initialized
    return TRUE;
}

OPTIMIZE_O3 bool datagram_copy(struct Datagram *a, struct Datagram *b) {
    if (!a || !b) { return FALSE; }
    if (a == b) { return TRUE; }
    
    // Make sure to properly deallocate any buffers.
    if (datagram_is_initialized(b) && b->length >= BUFFER_LENGTH && b->addr) {
        free(b->addr);
    }
    
    // Copy over the state from Datagram A into Datagram B.
    memcpy(b, a, sizeof(struct Datagram));
    
    // We want to allocate a new copy of the internal allocated buffer
    // if that is needed, otherwise we're using the stack and it was already copied.
    if (a->length >= BUFFER_LENGTH) {
        if (!a->addr) {
            a->flags |= SET_BIT(1, 2); // Error
            b->flags |= SET_BIT(1, 2); // Error
            b->addr = NULL;
            b->length = 0;
            SOFT_ASSERT_RETURN(a->addr, FALSE);
            return FALSE;
        }
        
        // Allocate the new buffer to copy into.
        u8 *buffer = calloc(1, a->length + 1);
        // Copy the contents of the buffer into the new one.
        memcpy(buffer, a->addr, a->length);
        // We're done.
        b->addr = buffer;
    }
    
    return TRUE;
}

OPTIMIZE_O3 bool datagram_truncate(struct Datagram *dg, u32 length) {
    if (!dg) { return FALSE; }
    
    s64 truncated_size = (s64)dg->length - (s64)length;
    if (truncated_size <= 0) {
        if (dg->length >= BUFFER_LENGTH && dg->addr) { free(dg->addr); }
        memset(dg->buffer, 0, BUFFER_LENGTH);
        dg->cursor = 0;
        dg->length = 0;
        return TRUE;
    }
    
    // Choose the current buffer in use.
    void *buffer = NULL;
    if (dg->length < BUFFER_LENGTH) {
        buffer = dg->buffer;
    } else {
        buffer = dg->addr;
    }
    
    if (truncated_size < BUFFER_LENGTH) {
        // We will now use the stack buffer.
        if (buffer != dg->buffer) { // Using heap for buffer.
            // Copy contents to a temporary buffer.
            u8 temp_buffer[BUFFER_LENGTH];
            temp_buffer[truncated_size] = 0;
            memcpy(temp_buffer, buffer, truncated_size);
            
            // Free the heap buffer.
            free(dg->addr);
            
            // Copy contents from temp buffer.
            memcpy(dg->buffer, temp_buffer, truncated_size);
            memset(&dg->buffer[truncated_size], 0, BUFFER_LENGTH - truncated_size);
            dg->length = (u32)truncated_size;
            
            return TRUE;
        }
        
        memset(&dg->buffer[truncated_size], 0, length);
        dg->length = (u32)truncated_size;
        return TRUE;
    }
    
    // We will now use the heap buffer.

    if (buffer != dg->addr) { // Using stack for buffer.
        // Allocate our new buffer.
        u8 *heap_buffer = malloc(truncated_size + 1);
        heap_buffer[truncated_size] = 0;
#ifdef DEBUG
        assert(heap_buffer != NULL);
#endif
        // Copy over the contents that were not truncated.
        memcpy(heap_buffer, buffer, truncated_size);
        
        // Clear out the stack buffer.
        memset(dg->buffer, 0, BUFFER_LENGTH);
        
        // Set the new buffer.
        dg->addr = heap_buffer;
        dg->length = (u32)truncated_size;
        return TRUE;
    }
    
    memset(&dg->addr[truncated_size], 0, length);
    dg->length = (u32)truncated_size;
    return TRUE;
}

OPTIMIZE_O3 u32 datagram_hash(struct Datagram *dg, u32 length) {
    u32 hash = 0;
    u16 byte = 0;
    
    if (length > dg->length) {
        dg->flags |= SET_BIT(1, 2); // Error
        SOFT_ASSERT_RETURN(length <= dg->length, 0);
        return 0;
    }
    
    bool using_buff = dg->length < BUFFER_LENGTH;
    for (u32 i = 0; i < length; i++) {
        u32 data = 0;
        if (using_buff) {
            // We are using the stack buffer still. So we read from it instead of a allocated buffer.
            data = (u32)dg->buffer[i];
        } else {
            // We are no longer using the stack buffer, so we read out of the allocated buffer.
            data = (u32)dg->addr[i];
        }
        hash ^= data << (8 * byte);
        byte = (byte + 1) % sizeof(u32);
    }
    return hash;
}

OPTIMIZE_O3 bool datagram_seek(struct Datagram *dg, u32 offset) {
    if (!dg) { return FALSE; }
    
    if (offset > dg->length) {
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 3); // Seek Error
        SOFT_ASSERT_RETURN(offset < dg->length, FALSE);
        return FALSE; 
    }
    
    dg->cursor = offset;
    return TRUE;
}

OPTIMIZE_O3 bool datagram_append_data(struct Datagram *dg, void *data, u32 length) {
    if (!dg || !data) { return FALSE; }
    
    u32 old_length = dg->length;
    u32 new_length = old_length + length;
    
    // Uh-oh! We've encountered either a wrap around or memory corruption!
    // We should probably abort here and cross our fingers.
    if (new_length < old_length) {
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 4); // Append Error
        SOFT_ASSERT_RETURN(new_length >= old_length, FALSE);
        return FALSE;
    }
    
    if (new_length < BUFFER_LENGTH) {
        // We are using the stack buffer still. So we write into it instead of allocating.
        memcpy(&dg->buffer[old_length], data, length);
        dg->length = new_length;
    } else if (old_length < BUFFER_LENGTH && new_length >= BUFFER_LENGTH) {
        // We ARE using the stack buffer but we no longer can use the stack buffer
        // as the needed space exceeds it. 
        // We'll allocate a brand new buffer just for that purpose.
        
        // Allocate our new buffer.
        u8 *buffer = malloc(new_length + 1);
        buffer[new_length] = 0;
#ifdef DEBUG
        assert(buffer != NULL);
#endif
        // Copy over the old contents.
        memcpy(buffer, dg->buffer, old_length);
        // Copy over the new contents.
        memcpy(&buffer[old_length], data, length);
        // Clear the buffer so it's in a default state.
        // This isn't NEEDED. But better to not mistake the contents for memory
        // corruption. It's part of a union.
        memset(dg->buffer, 0, BUFFER_LENGTH);
        // We're done, Now we can set what we need too.
        dg->addr = buffer;
        dg->length = new_length;
    } else {
        // We are no longer using the stack buffer, So just do a normal reallocation
        // and normally copy in the data.
        dg->addr = realloc(dg->addr, new_length + 1);
        dg->addr[new_length] = 0;
        memcpy(&dg->addr[old_length], data, length);
        dg->length = new_length;
    }
    
    return TRUE;
}

OPTIMIZE_O3 bool datagram_read_data(struct Datagram *dg, void *data, u32 length) {
    if (!dg || !data) { return FALSE; }
    
    if (dg->cursor > dg->length || length > dg->length - dg->cursor) {
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 5); // Read Error
        SOFT_ASSERT_RETURN(dg->cursor <= dg->length && length <= dg->length - dg->cursor, FALSE);
        return FALSE; 
    }
    u32 new_position = dg->cursor + length;
    
    if (dg->length < BUFFER_LENGTH) {
        // We are using the stack buffer still. So we read from it instead of a allocated buffer.
        memcpy(data, &dg->buffer[dg->cursor], length);
    } else {
        // We are no longer using the stack buffer, so we read out of the allocated buffer.
        memcpy(data, &dg->addr[dg->cursor], length);
    }
    dg->cursor = new_position;
    
    return TRUE;
}

OPTIMIZE_O3 bool datagram_write_data(struct Datagram *dg, void *data, u32 length) {
    if (!dg || !data) { return FALSE; }
    
    if (dg->cursor > dg->length || length > dg->length - dg->cursor) {
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 6); // Write Error
        SOFT_ASSERT_RETURN(dg->cursor <= dg->length && length <= dg->length - dg->cursor, FALSE);
        return FALSE; 
    }
    u32 new_position = dg->cursor + length;
    
    if (dg->length < BUFFER_LENGTH) {
        // We are using the stack buffer still. So we write into it instead of a allocated buffer.
        memcpy(&dg->buffer[dg->cursor], data, length);
    } else {
        // We are no longer using the stack buffer, so we write into the allocated buffer.
        memcpy(&dg->addr[dg->cursor], data, length);
    }
    dg->cursor = new_position;
    
    return TRUE;
}

OPTIMIZE_O3 bool datagram_add_padding(struct Datagram *dg, u32 length) {
    if (!dg) { return FALSE; }
    
    u32 old_length = dg->length;
    u32 new_length = old_length + length;
    
    // Uh-oh! We've encountered either a wrap around or memory corruption!
    // We should probably abort here and cross our fingers.
    if (new_length < old_length) {
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 4); // Append Error
        SOFT_ASSERT_RETURN(new_length >= old_length, FALSE);
        return FALSE;
    }
    
    if (new_length < BUFFER_LENGTH) {
        // We are using the stack buffer still. So we write into it instead of allocating.
        memset(&dg->buffer[old_length], 0, length);
        dg->length = new_length;
    } else if (old_length < BUFFER_LENGTH && new_length >= BUFFER_LENGTH) {
        // We ARE using the stack buffer but we no longer can use the stack buffer
        // as the needed space exceeds it. 
        // We'll allocate a brand new buffer just for that purpose.
        
        // Allocate our new buffer.
        u8 *buffer = calloc(1, new_length + 1);
#ifdef DEBUG
        assert(buffer != NULL);
#endif
        // Copy over the old contents.
        memcpy(buffer, dg->buffer, old_length);
        // Clear the buffer so it's in a default state.
        // This isn't NEEDED. But better to not mistake the contents for memory
        // corruption. It's part of a union.
        memset(dg->buffer, 0, BUFFER_LENGTH);
        // We're done, Now we can set what we need too.
        dg->addr = buffer;
        dg->length = new_length;
    } else {
        // We are no longer using the stack buffer, So just do a normal reallocation
        // and normally write the data.
        dg->addr = realloc(dg->addr, new_length + 1);
        dg->addr[new_length] = 0;
        memset(&dg->addr[old_length], 0, length);
        dg->length = new_length;
    }
    
    return TRUE;
}

OPTIMIZE_O3 u8 *datagram_get_message(struct Datagram *dg) {
    if (!dg || dg->length <= 0) { return NULL; }
    
    u8 *buffer = malloc(dg->length + 1);
#ifdef DEBUG
    assert(buffer != NULL);
#endif
    buffer[dg->length] = 0;
    if (dg->length < BUFFER_LENGTH) {
        // We are using the stack buffer still. So we copy from it.
        memcpy(buffer, dg->buffer, dg->length);
    } else {
        // We are no longer using the stack buffer, Copy from here instead.
        memcpy(buffer, dg->addr, dg->length);
    }
    return buffer;
}

OPTIMIZE_O3 u8 *datagram_get_remaining_bytes(struct Datagram *dg) {
    if (!dg) { return NULL; }
  
    u32 length = datagram_get_remaining_size(dg);
    if (length <= 0) { return NULL; }
    
    u8 *buffer = malloc(length + 1);
#ifdef DEBUG
    assert(buffer != NULL);
#endif
    buffer[length] = 0;
    if (dg->length < BUFFER_LENGTH) {
        // We are using the stack buffer still. So we copy from it.
        memcpy(buffer, &dg->buffer[dg->cursor], length);
    } else {
        // We are no longer using the stack buffer, Copy from here instead.
        memcpy(buffer, &dg->addr[dg->cursor], length);
    }
    return buffer;
}

OPTIMIZE_O3 bool datagram_compress(struct Datagram *dg) {
    if (!dg || datagram_is_compressed(dg)) { return FALSE; }
    
    u32 length = dg->length;
    
    // Allocate our buffer for compression.
    uLongf compression_length = compressBound(length);
    u8 *buffer = malloc(compression_length + 1);
#ifdef DEBUG
    assert(buffer != NULL);
#endif
    buffer[compression_length] = 0;
    
    bool result = FALSE;
    if (length < BUFFER_LENGTH) {
        // We are using the stack buffer still.
        result = compress2((Bytef *)buffer, &compression_length, (Bytef *)dg->buffer, length, Z_BEST_COMPRESSION) == Z_OK;
    } else {
        // We are no longer using the stack buffer.
        result = compress2((Bytef *)buffer, &compression_length, (Bytef *)dg->addr, length, Z_BEST_COMPRESSION) == Z_OK;
    }
    if (!result) {
        // Set the error flag as the Datagram has failed to compress.
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 7); // Compression Error
        free(buffer);
        return result; 
    }
    
    // Clear out the old contents.
    datagram_clear(dg);
    
    // Set our flags to indicate that the Datagram is compressed.
    dg->flags |= SET_BIT(1, 1);
    
    // Store the uncompressed length.
    datagram_add_uint32(dg, length);
    
    // Store the compressed length.
    datagram_add_uint32(dg, compression_length);
    
    // Append the compressed data.
    datagram_append_data(dg, (u8 *)buffer, compression_length);
    
    // Free the compression buffer.
    free(buffer);
    
    return TRUE;
}

OPTIMIZE_O3 bool datagram_decompress(struct Datagram *dg) {
    if (!dg || !datagram_is_compressed(dg)) { return FALSE; }
    
    // Read the lengths for the compressed Datagram.
    u32 length = datagram_read_uint32(dg);
    u32 compressed_length = datagram_read_uint32(dg);
    
    // Abort if we had any read errors.
    if (datagram_has_read_error(dg)) {
        dg->flags |= SET_BIT(1, 7); // Compression Error
        return FALSE; 
    }
    
    // We shouldn't accept anything past these sizes.
    if (length >= MAX_DECOMPRESS_LENGTH || compressed_length >= MAX_DECOMPRESS_LENGTH) {
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 7); // Compression Error
        return FALSE; 
    }
    
    // Allocate our buffer for the compressed data.
    u8 *buffer = malloc(compressed_length + 1);
#ifdef DEBUG
    assert(buffer != NULL);
#endif
    buffer[compressed_length] = 0;
  
    // Read the compressed data out of our Datagram.
    datagram_read_data(dg, buffer, compressed_length);
    
    // Clear out the old contents.
    datagram_clear(dg);
    
    // Add padding for the decompression to write into.
    datagram_add_padding(dg, length);
    
    bool result = FALSE;
    uLongf decompressed_length = length;
    if (length < BUFFER_LENGTH) {
        // We are using the stack buffer still.
        result = uncompress((Bytef *)dg->buffer, &decompressed_length, (Bytef *)buffer, compressed_length) == Z_OK;
    } else {
        // We are no longer using the stack buffer.
        result = uncompress((Bytef *)dg->addr, &decompressed_length, (Bytef *)buffer, compressed_length) == Z_OK;
    }
    if (!result) {
        // Set the error flag as the contents are no longer usuable.
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 7); // Compression Error
        free(buffer);
        return result; 
    }
    
    // We failed to decompress all of the data?
    if (decompressed_length < length) {
        // Set the error flag as the contents are no longer usuable.
        dg->flags |= SET_BIT(1, 2); // Error
        dg->flags |= SET_BIT(1, 7); // Compression Error
        free(buffer);
        return FALSE; 
    }
    
    // We sucessfully decompressed the data.
    
    // Free the compressed data buffer.
    free(buffer);
    
    return result;
}