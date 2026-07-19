# Dense-254 Changelog

### Added

* Added support for up to 254 total player slots.
* Added chunked player roster synchronization for large lobbies.
* Added generation tracking for roster updates.
* Added support for roster chunks arriving out of order.
* Added duplicate and stale roster chunk rejection.
* Added validation before applying a completed roster update.
* Added removal of players missing from a newer completed roster.
* Added network metrics for:

  * transmitted and received packets;
  * compressed and uncompressed bytes;
  * compression ratio;
  * compression and decompression time;
  * per-packet traffic;
  * per-client traffic;
  * broadcast fanout;
  * packet drops;
  * send errors;
  * receive errors.

### Changed

* Increased the multiplayer limit from 16 total players to 254 total players.
* Increased the maximum remote-client count from 15 to 253.
* Split large roster updates across multiple packets instead of using one fixed-size packet.
* Changed roster updates to be applied only after every chunk has been received and validated.
* Updated protocol compatibility checks so clients with incompatible packet formats cannot connect.
* Changed compressed packet allocation to use zlib's calculated worst-case output size.
* Improved player ID and player index validation throughout the networking code.
* Improved fanout accounting for packets relayed by the server.
* Added configurable network metrics reporting intervals.
* Added a compile-time option to disable network metrics.

### Fixed

* Fixed a packet buffer overflow when the full player roster exceeded the original packet size.
* Fixed packet writes continuing after an overflow condition was detected.
* Fixed packet reads using invalid or incomplete packet lengths.
* Fixed unsafe packet duplication and hash validation for malformed packets.
* Fixed off-by-one checks that allowed `playerIndex == MAX_PLAYERS`.
* Fixed invalid player indexes reaching connection, settings, model, ordered-packet, and receive paths.
* Fixed malformed join packets advertising invalid player limits.
* Fixed player roster updates incorrectly handling duplicate, missing, stale, or out-of-order data.
* Fixed disconnected players remaining present after a newer roster update.
* Fixed swimming state initialization only working correctly for the original 16 player slots.
* Fixed server-relayed player packets not contributing to fanout metrics.

### Capacity

The current protocol supports:

```text
254 total player slots
1 host or server slot
253 remote client slots
```

The current one-byte player ID layout is:

```text
0-253    player IDs
254      server destination
255      broadcast destination
```

Supporting more than 254 total player slots requires widening player and destination IDs.

### Performance

Testing with 37 connected peers reported:

```text
704,378 transmitted packet deliveries
78.09 MiB compressed payload
321.32 MiB uncompressed payload
0.243 compression ratio
204.6 KiB/s average outbound payload
13.24 seconds total compression time over 390.7 seconds
24.75 average fanout
0 packet drops
0 send errors
0 receive errors
```

The current practical target is approximately 96 to 128 active players under similar conditions.

The current addressable maximum is 254 players, but dense rooms above the practical target are expected to become limited by repeated per-recipient compression and packet delivery overhead before saturating a 1 Gbit network interface.

### Known Limitations

* Player packets are still compressed separately for every recipient.
* Player visibility is still primarily filtered by course, act, level, and area.
* Spatial interest management has not yet been added.
* Per-client packet and byte budgets have not yet been added.
* Stale movement packet coalescing has not yet been added.
* Synchronized object replication still uses the original recipient behavior.
* Client rendering and simulation costs increase with every visible remote player.
* Headless servers require software frame pacing to avoid an unbounded CPU loop.

Recommended headless configuration:

```text
vsync false
framerate_mode 1
frame_limit 30
```

### Compatibility

Servers and clients must use the same modified protocol version.

Original SM64CoopDX clients are not network-compatible with this branch.

### Planned

* Reuse compressed packet bodies across recipients.
* Batch packet sends to reduce syscall overhead.
* Add per-client packet and byte budgets.
* Coalesce replaceable movement updates.
* Add spatial interest management.
* Add distance-based replication rates.
* Add recipient planning for synchronized objects.
* Add lightweight headless load-testing clients.
* Widen player and destination IDs for more than 254 total players.
