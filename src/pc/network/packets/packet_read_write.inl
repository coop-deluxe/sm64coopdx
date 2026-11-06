#ifndef PACKET_READ_WRITE_INL
#define PACKET_READ_WRITE_INL

#include "pc/debuglog.h"

INLINE OPTIMIZE_O3 void packet_clear(struct Packet *packet) {
    if (!packet) { return; }
    
    datagram_clear(&packet->dg);
    memset(packet, 0, sizeof(struct Packet));
}

INLINE OPTIMIZE_O3 u32 packet_hash(struct Packet *packet) {
    if (!packet) { return 0; }
    return datagram_hash(&packet->dg, datagram_length(&packet->dg));
}

/* |description|
Reads data from the current cursor position in the Packets Datagram.
Returns False on failure.
Returns True on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_read(struct Packet *packet, void *data, u32 length) {
    if (!packet || !data) { return FALSE; }
    
    datagram_read_data(&packet->dg, data, length);
    if (datagram_has_read_error(&packet->dg)) {
#ifdef DEVELOPMENT
        LOG_ERROR("Encountered read error for function \"%s\" at line %d.", __func__, __LINE__);
        assert(false);
#endif
        return FALSE; 
    }
    
    return TRUE;
}

/* |description|
Writes additionial data to the end of Packets Datagram and
then moves the cursor position forward by the length of the data.
Returns False on failure to write the new data to the Datagram.
Returns True on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write(struct Packet *packet, void *data, u32 length) {
    if (!packet || !data) { return FALSE; }
    
    datagram_append_data(&packet->dg, data, length);
    if (datagram_has_append_error(&packet->dg)) {
#ifdef DEVELOPMENT
        LOG_ERROR("Encountered append error for function \"%s\" at line %d.", __func__, __LINE__);
        assert(false);
#endif
        return FALSE; 
    }
    
    packet->dg.cursor += length;
    return TRUE;
}

/* |description|
Reads a boolean from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_read_bool(struct Packet *packet) {
    bool value = FALSE;
    packet_read(packet, &value, sizeof(bool));
    return value;
}

/* |description|
Reads a 8-bit signed integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s8 packet_read_int8(struct Packet *packet) {
    s8 value = 0;
    packet_read(packet, &value, sizeof(s8));
    return value;
}

/* |description|
Reads a 8-bit unsigned integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u8 packet_read_uint8(struct Packet *packet) {
    u8 value = 0;
    packet_read(packet, &value, sizeof(u8));
    return value;
}

/* |description|
Reads a 16-bit signed integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s16 packet_read_int16(struct Packet *packet) {
    s16 value = 0;
    if (packet_read(packet, &value, sizeof(s16))) {
        value = LE_TO_HOST16(value);
    }
    return value;
}

/* |description|
Reads a 16-bit unsigned integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u16 packet_read_uint16(struct Packet *packet) {
    u16 value = 0;
    if (packet_read(packet, &value, sizeof(u16))) {
        value = LE_TO_HOST16(value);
    }
    return value;
}

/* |description|
Reads a 32-bit signed integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s32 packet_read_int32(struct Packet *packet) {
    s32 value = 0;
    if (packet_read(packet, &value, sizeof(s32))) {
        value = LE_TO_HOST32(value);
    }
    return value;
}

/* |description|
Reads a 32-bit unsigned integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u32 packet_read_uint32(struct Packet *packet) {
    u32 value = 0;
    if (packet_read(packet, &value, sizeof(u32))) {
        value = LE_TO_HOST32(value);
    }
    return value;
}

/* |description|
Reads a 64-bit signed integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 s64 packet_read_int64(struct Packet *packet) {
    s64 value = 0;
    if (packet_read(packet, &value, sizeof(s64))) {
        value = LE_TO_HOST64(value);
    }
    return value;
}

/* |description|
Reads a 64-bit unsigned integer from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u64 packet_read_uint64(struct Packet *packet) {
    u64 value = 0;
    if (packet_read(packet, &value, sizeof(u64))) {
        value = LE_TO_HOST64(value);
    }
    return value;
}

/* |description|
Reads a 32-bit float from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 f32 packet_read_float32(struct Packet *packet) {
    union f32_bits value;
    value.f = 0.0f;

    if (packet_read(packet, &value.u, sizeof(u32))) {
        value.u = LE_TO_HOST32(value.u); 
    }
    return value.f;
}

/* |description|
Reads a 64-bit float from the current cursor position in the Packets Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 f64 packet_read_float64(struct Packet *packet) {
    union f64_bits value;
    value.f = 0.0;

    if (packet_read(packet, &value.u, sizeof(u64))) {
        value.u = LE_TO_HOST64(value.u);
    }
    return value.f;
}

/* |description|
Writes a boolean to the end of Packets Datagram and
then moves the cursor position forward by the size of a boolean.
Returns False on failure to write the boolean to the Datagram.
Returns True on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_bool(struct Packet *packet, bool value) {
    return packet_write(packet, &value, sizeof(bool));
}

/* |description|
Writes a 8-bit signed integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 8-bit signed integer.
Returns False on failure to write the 8-bit signed integer to the Datagram.
Returns True on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_int8(struct Packet *packet, s8 value) {
    return packet_write(packet, &value, sizeof(s8));
}

/* |description|
Writes a 8-bit unsigned integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 8-bit unsigned integer.
Returns False on failure to write the 8-bit unsigned integer to the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_uint8(struct Packet *packet, u8 value) {
    return packet_write(packet, &value, sizeof(u8));
}

/* |description|
Writes a 16-bit signed integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 16-bit signed integer.
Returns False on failure to write the 16-bit signed integer to the Datagram.
Returns True on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_int16(struct Packet *packet, s16 value) {
    value = HOST_TO_LE16(value);
    return packet_write(packet, &value, sizeof(s16));
}

/* |description|
Writes a 16-bit unsigned integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 16-bit unsigned integer.
Returns False on failure to write the 16-bit unsigned integer to the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_uint16(struct Packet *packet, u16 value) {
    value = HOST_TO_LE16(value);
    return packet_write(packet, &value, sizeof(u16));
}

/* |description|
Writes a 32-bit signed integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 32-bit signed integer.
Returns False on failure to write the 32-bit signed integer to the Datagram.
Returns True on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_int32(struct Packet *packet, s32 value) {
    value = HOST_TO_LE32(value);
    return packet_write(packet, &value, sizeof(s32));
}

/* |description|
Writes a 32-bit unsigned integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 32-bit unsigned integer.
Returns False on failure to write the 32-bit unsigned integer to the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_uint32(struct Packet *packet, u32 value) {
    value = HOST_TO_LE32(value);
    return packet_write(packet, &value, sizeof(u32));
}

/* |description|
Writes a 64-bit signed integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 64-bit signed integer.
Returns False on failure to write the 64-bit signed integer to the Datagram.
Returns True on success.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_int64(struct Packet *packet, s64 value) {
    value = HOST_TO_LE64(value);
    return packet_write(packet, &value, sizeof(s64));
}

/* |description|
Writes a 64-bit unsigned integer to the end of Packets Datagram and
then moves the cursor position forward by the size of a 64-bit unsigned integer.
Returns False on failure to write the 64-bit unsigned integer to the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_uint64(struct Packet *packet, u64 value) {
    value = HOST_TO_LE64(value);
    return packet_write(packet, &value, sizeof(u64));
}

/* |description|
Writes a 32-bit float to the end of Packets Datagram and
then moves the cursor position forward by the size of a 32-bit float.
Returns False on failure to write the 32-bit float to the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_float32(struct Packet *packet, f32 value) {
    union f32_bits data;
    data.f = value;
    data.u = HOST_TO_LE32(data.u);
    return packet_write(packet, &data.u, sizeof(u32));
}

/* |description|
Writes a 64-bit float to the end of Packets Datagram and
then moves the cursor position forward by the size of a 64-bit float.
Returns False on failure to write the 64-bit float to the Datagram.
|descriptionEnd| */
INLINE OPTIMIZE_O3 bool packet_write_float64(struct Packet *packet, f64 value) {
    union f64_bits data;
    data.f = value;
    data.u = HOST_TO_LE64(data.u);
    return packet_write(packet, &data.u, sizeof(u64));
}

/* |description|
Returns a copy of all the contents in the Packet after the current cursor 
position.
Returns NULL if there is no contents or if the Packets state is invalid.
! UNSAFE for LUA usage without a custom function. !
|descriptionEnd| */
INLINE OPTIMIZE_O3 u8 *packet_get_remaining_bytes(struct Packet *packet) {
    if (!packet) { return NULL; }
    return datagram_get_remaining_bytes(&packet->dg);
}


/* |description|
Returns the length of the remaining bytes after the current cursor position.
|descriptionEnd| */
INLINE OPTIMIZE_O3 u32 packet_get_remaining_size(struct Packet *packet) {
    if (!packet) { return 0; }
    return datagram_get_remaining_size(&packet->dg);
}

#endif // PACKET_READ_WRITE_INL