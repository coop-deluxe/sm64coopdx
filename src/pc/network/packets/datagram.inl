#ifndef DATAGRAM_INL
#define DATAGRAM_INL

/* |description|
Returns the length of the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u32 datagram_length(struct Datagram *dg) {
    if (!dg) { return 0; }
    return dg->length;
}

/* |description|
Returns the internal buffer currently used by the Datagram.
Use at your own risk, The buffer can become invalid at any time.
! UNSAFE for LUA usage. !
|descriptionEnd| */
INLINE OPTIMIZE_O3 u8 *datagram_data(struct Datagram *dg) {
    if (!dg) { return NULL; }
    
    if (dg->length >= BUFFER_LENGTH) {
        return dg->addr;
    }
    return dg->buffer;
}

/* |description|
Returns the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u32 datagram_cursor_position(struct Datagram *dg) {
    if (!dg) { return 0; }
    return dg->cursor;
}

/* |description|
Seeks (Moves the cursor) to the ending position in the Datagram.
Returns false on failure.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_seek_end(struct Datagram *dg) {
    if (!dg || dg->length <= 0) { return FALSE; }
    
    dg->cursor = dg->length - 1;
    return TRUE;
}

/* |description|
Seeks (Moves the cursor) to the starting position in the Datagram.
Returns false on failure.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_seek_start(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    
    dg->cursor = 0;
    return TRUE;
}

/* |description|
Returns the length of the remaining bytes after the current cursor position.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u32 datagram_get_remaining_size(struct Datagram *dg) {
    if (!dg || dg->length <= 0) { return 0; }
    s64 length = dg->length - dg->cursor;
    if (length <= 0) { return 0; }
    return (u32)length;
}

/* |description|
Appends a boolean to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_bool(struct Datagram *dg, bool value) {
    return datagram_append_data(dg, &value, sizeof(bool));
}

/* |description|
Appends a 8-bit signed integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_int8(struct Datagram *dg, s8 value) {
    return datagram_append_data(dg, &value, sizeof(s8));
}

/* |description|
Appends a 8-bit unsigned integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_uint8(struct Datagram *dg, u8 value) {
    return datagram_append_data(dg, &value, sizeof(u8));
}

/* |description|
Appends a 16-bit signed integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_int16(struct Datagram *dg, s16 value) {
    value = HOST_TO_LE16(value);
    return datagram_append_data(dg, &value, sizeof(s16));
}

/* |description|
Appends a 16-bit unsigned integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_uint16(struct Datagram *dg, u16 value) {
    value = HOST_TO_LE16(value);
    return datagram_append_data(dg, &value, sizeof(u16));
}

/* |description|
Appends a 32-bit signed integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_int32(struct Datagram *dg, s32 value) {
    value = HOST_TO_LE32(value);
    return datagram_append_data(dg, &value, sizeof(s32));
}

/* |description|
Appends a 32-bit unsigned integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_uint32(struct Datagram *dg, u32 value) {
    value = HOST_TO_LE32(value);
    return datagram_append_data(dg, &value, sizeof(u32));
}

/* |description|
Appends a 64-bit signed integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_int64(struct Datagram *dg, s64 value) {
    value = HOST_TO_LE64(value);
    return datagram_append_data(dg, &value, sizeof(s64));
}

/* |description|
Appends a 64-bit unsigned integer to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_uint64(struct Datagram *dg, u64 value) {
    value = HOST_TO_LE64(value);
    return datagram_append_data(dg, &value, sizeof(u64));
}

/* |description|
Appends a 32-bit float to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_float32(struct Datagram *dg, f32 value) {
    union f32_bits data;
    data.f = value;
    data.u = HOST_TO_LE32(data.u);
    return datagram_append_data(dg, &data.u, sizeof(u32));
}

/* |description|
Appends a 64-bit float to the end of the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_add_float64(struct Datagram *dg, f64 value) {
    union f64_bits data;
    data.f = value;
    data.u = HOST_TO_LE64(data.u);
    return datagram_append_data(dg, &data.u, sizeof(u64));
}

/* |description|
Reads a boolean from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_read_bool(struct Datagram *dg) {
    bool value = FALSE;
    datagram_read_data(dg, &value, sizeof(bool));
    return value;
}

/* |description|
Reads a 8-bit signed integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s8 datagram_read_int8(struct Datagram *dg) {
    s8 value = 0;
    datagram_read_data(dg, &value, sizeof(s8));
    return value;
}

/* |description|
Reads a 8-bit unsigned integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u8 datagram_read_uint8(struct Datagram *dg) {
    u8 value = 0;
    datagram_read_data(dg, &value, sizeof(u8));
    return value;
}

/* |description|
Reads a 16-bit signed integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s16 datagram_read_int16(struct Datagram *dg) {
    s16 value = 0;
    if (datagram_read_data(dg, &value, sizeof(s16))) {
        value = LE_TO_HOST16(value);
    }
    return value;
}

/* |description|
Reads a 16-bit unsigned integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u16 datagram_read_uint16(struct Datagram *dg) {
    u16 value = 0;
    if (datagram_read_data(dg, &value, sizeof(u16))) {
        value = LE_TO_HOST16(value);
    }
    return value;
}

/* |description|
Reads a 32-bit signed integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s32 datagram_read_int32(struct Datagram *dg) {
    s32 value = 0;
    if (datagram_read_data(dg, &value, sizeof(s32))) {
        value = LE_TO_HOST32(value);
    }
    return value;
}

/* |description|
Reads a 32-bit unsigned integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u32 datagram_read_uint32(struct Datagram *dg) {
    u32 value = 0;
    if (datagram_read_data(dg, &value, sizeof(u32))) {
        value = LE_TO_HOST32(value);
    }
    return value;
}

/* |description|
Reads a 64-bit signed integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s64 datagram_read_int64(struct Datagram *dg) {
    s64 value = 0;
    if (datagram_read_data(dg, &value, sizeof(s64))) {
        value = LE_TO_HOST64(value);
    }
    return value;
}

/* |description|
Reads a 64-bit unsigned integer from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u64 datagram_read_uint64(struct Datagram *dg) {
    u64 value = 0;
    if (datagram_read_data(dg, &value, sizeof(u64))) {
        value = LE_TO_HOST64(value);
    }
    return value;
}

/* |description|
Reads a 32-bit float from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 datagram_read_float32(struct Datagram *dg) {
    union f32_bits value;
    value.f = 0.0f;

    if (datagram_read_data(dg, &value.u, sizeof(u32))) {
        value.u = LE_TO_HOST32(value.u);
    }
    return value.f;
}

/* |description|
Reads a 64-bit float from the current cursor position in the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 f64 datagram_read_float64(struct Datagram *dg) {
    union f64_bits value;
    value.f = 0.0;
    
    if (datagram_read_data(dg, &value.u, sizeof(u64))) {
        value.u = LE_TO_HOST64(value.u);
    }
    return value.f;
}

/* |description|
Writes a boolean to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_bool(struct Datagram *dg, bool value) {
    return datagram_write_data(dg, &value, sizeof(bool));
}

/* |description|
Writes a 8-bit signed integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_int8(struct Datagram *dg, s8 value) {
    return datagram_write_data(dg, &value, sizeof(s8));
}

/* |description|
Writes a 8-bit unsigned integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_uint8(struct Datagram *dg, u8 value) {
    return datagram_write_data(dg, &value, sizeof(u8));
}

/* |description|
Writes a 16-bit signed integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_int16(struct Datagram *dg, s16 value) {
    value = HOST_TO_LE16(value);
    return datagram_write_data(dg, &value, sizeof(s16));
}

/* |description|
Writes a 16-bit unsigned integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_uint16(struct Datagram *dg, u16 value) {
    value = HOST_TO_LE16(value);
    return datagram_write_data(dg, &value, sizeof(u16));
}

/* |description|
Writes a 32-bit signed integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_int32(struct Datagram *dg, s32 value) {
    value = HOST_TO_LE32(value);
    return datagram_write_data(dg, &value, sizeof(s32));
}

/* |description|
Writes a 32-bit unsigned integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_uint32(struct Datagram *dg, u32 value) {
    value = HOST_TO_LE32(value);
    return datagram_write_data(dg, &value, sizeof(u32));
}

/* |description|
Writes a 64-bit signed integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_int64(struct Datagram *dg, s64 value) {
    value = HOST_TO_LE64(value);
    return datagram_write_data(dg, &value, sizeof(s64));
}

/* |description|
Writes a 64-bit unsigned integer to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_uint64(struct Datagram *dg, u64 value) {
    value = HOST_TO_LE64(value);
    return datagram_write_data(dg, &value, sizeof(u64));
}

/* |description|
Writes a 32-bit float to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_float32(struct Datagram *dg, f32 value) {
    union f32_bits data;
    data.f = value;
    data.u = HOST_TO_LE32(data.u);
    return datagram_write_data(dg, &data.u, sizeof(u32));
}

/* |description|
Writes a 64-bit float to the current cursor position in the Datagram.
Returns false on failure or if an error occurs.
Returns true on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_write_float64(struct Datagram *dg, f64 value) {
    union f64_bits data;
    data.f = value;
    data.u = HOST_TO_LE64(data.u);
    return datagram_write_data(dg, &data.u, sizeof(u64));
}

/* |description|
Returns if a error has occured while working with this Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_has_error(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 2);
}

/* |description|
Returns if a seek error has occured while working with this Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_has_seek_error(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 3);
}

/* |description|
Returns if a append error has occured while working with this Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_has_append_error(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 4);
}

/* |description|
Returns if a read error has occured while working with this Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_has_read_error(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 5);
}

/* |description|
Returns if a write error has occured while working with this Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_has_write_error(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 6);
}

/* |description|
Returns if a compression error has occured while working with this Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_has_compression_error(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 7);
}

/* |description|
Returns if the Datagram is valid and is ready for use.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_is_initialized(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 0);
}

/* |description|
Returns if the Datagram has compressed its contents.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool datagram_is_compressed(struct Datagram *dg) {
    if (!dg) { return FALSE; }
    return GET_BIT(dg->flags, 1);
}

#endif // DATAGRAM_INL