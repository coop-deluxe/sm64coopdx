.channel12:
chan_largenoteson
chan_setinstr 0
chan_setpanmix 127
chan_setnotepriority 14
chan_setval 0
chan_iowriteval 5
chan_stereoheadseteffects 1
chan_setdyntable .channel12_table
chan_jump .main_loop_toad

.main_loop_toad:
chan_delay1
chan_ioreadval 0
chan_bltz .main_loop_toad
.start_playing_toad:
chan_freelayer 0
chan_freelayer 1
chan_freelayer 2
chan_setval 0
chan_iowriteval 5
chan_ioreadval 4
chan_dyncall


.poll_toad:
chan_delay1
chan_ioreadval 0
chan_bltz .skip_toad
  chan_beqz .force_stop_toad
  chan_jump .start_playing_toad
.skip_toad:
chan_testlayerfinished 0
chan_beqz .poll_toad
chan_jump .main_loop_toad
.force_stop_toad:
chan_freelayer 0
chan_freelayer 1
chan_freelayer 2
chan_jump .main_loop_toad

.channel12_table:
sound_ref .sound_toad_jump_yah
sound_ref .sound_toad_jump_wah
sound_ref .sound_toad_jump_hoo
sound_ref .sound_toad_hoohoo
sound_ref .sound_toad_yahoo
sound_ref .sound_toad_uh
sound_ref .sound_toad_hrmm
sound_ref .sound_toad_wah2
sound_ref .sound_toad_whoa
sound_ref .sound_toad_eeuh
sound_ref .sound_toad_attacked
sound_ref .sound_toad_ooof
sound_ref .sound_toad_here_we_go
sound_ref .sound_toad_yawning
sound_ref .sound_toad_snoring1
sound_ref .sound_toad_snoring2
sound_ref .sound_toad_waaaooow
sound_ref .sound_toad_haha
sound_ref .sound_toad_panting1
sound_ref .sound_toad_uh2
sound_ref .sound_toad_on_fire
sound_ref .sound_toad_dying
sound_ref .sound_toad_panting_cold
sound_ref .sound_toad_coughing3
sound_ref .sound_toad_panting1
sound_ref .sound_toad_panting2
sound_ref .sound_toad_panting3
sound_ref .sound_toad_coughing1
sound_ref .sound_toad_coughing2
sound_ref .sound_toad_coughing3
sound_ref .sound_toad_punch_yah
sound_ref .sound_toad_punch_hoo
sound_ref .sound_toad_mama_mia
sound_ref .sound_toad_okey_dokey
sound_ref .sound_toad_ground_pound_wah
sound_ref .sound_toad_drowning
sound_ref .sound_toad_punch_wah
sound_ref .sound_toad_uh
sound_ref .sound_toad_hrmm
sound_ref .sound_toad_wah2
.ifdef VERSION_JP
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
.else
  sound_ref .sound_peach_dear_toad
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_jump_hoo
  sound_ref .sound_toad_yahoo
  sound_ref .sound_toad_yahoo
  sound_ref .sound_toad_yahoo
  sound_ref .sound_toad_waha
  sound_ref .sound_toad_yippee
  sound_ref .sound_toad_doh
  sound_ref .sound_toad_game_over
  sound_ref .sound_toad_hello
  sound_ref .sound_toad_press_start_to_play
  sound_ref .sound_toad_twirl_bounce
  sound_ref .sound_toad_snoring3
  sound_ref .sound_toad_so_longa_bowser
  sound_ref .sound_toad_ima_tired
  sound_ref .sound_toad_lets_a_go
.endif

.sound_toad_jump_hoo:
chan_setbank 15
chan_setinstr 0
chan_setlayer 0, .layer_toad_C3C
chan_end

.layer_toad_C3C:
.ifdef VERSION_EU
.endif
layer_note1 39, 0x14, 127
layer_end

.sound_toad_jump_wah:
chan_setbank 15
chan_setinstr 1
chan_setlayer 0, .layer_toad_C4C
chan_end

.layer_toad_C4C:
.layer_toad_C4E:
layer_note1 39, 0x18, 127
layer_end

.sound_toad_jump_yah:
chan_setbank 16
chan_setinstr 9
chan_setlayer 0, .layer_toad_C5A
chan_end

.layer_toad_C5A:
.layer_toad_C5C:
layer_note1 39, 0x24, 127
layer_end

.sound_toad_hoohoo:
chan_setbank 16
chan_setinstr 1
chan_setlayer 0, .layer_toad_C6C
chan_end

.layer_toad_C6C:
.ifdef VERSION_EU
.endif
layer_note1 39, 0x30, 127
layer_end

.sound_toad_yahoo:
chan_setbank 15
chan_setinstr 4
chan_setlayer 0, .layer_toad_C7C
chan_end

.layer_toad_C7C:

layer_somethingon
layer_note1 39, 0x1e, 127
layer_note1 39, 0x41, 127
layer_end

.sound_toad_uh:
chan_setbank 15
chan_setinstr 5
chan_setlayer 0, .layer_toad_C92
chan_end

.layer_toad_C92:
layer_note1 39, 0x2b, 127
layer_end

.sound_toad_hrmm:
chan_setbank 15
chan_setinstr 6
chan_setlayer 0, .layer_toad_CA4
chan_end

.layer_toad_CA4:
layer_note1 39, 0x1e, 127
layer_end

.sound_toad_wah2:
chan_setbank 15
chan_setinstr 7
chan_setlayer 0, .layer_toad_CB2
chan_end

.layer_toad_CB2:
layer_note1 39, 0x1c, 127
layer_end

.sound_toad_whoa:
chan_setbank 15
chan_setinstr 8
chan_setlayer 0, .layer_toad_CC0
chan_end

.layer_toad_CC0:
layer_note1 39, 0x30, 127
layer_end

.sound_toad_eeuh:
chan_setbank 15
chan_setinstr 9
chan_setlayer 0, .layer_toad_CCE
chan_end

.layer_toad_CCE:
layer_note1 39, 0x44, 127
layer_end

.sound_toad_attacked:
chan_setbank 15
chan_setinstr 10
chan_setlayer 0, .layer_toad_CDC
chan_end

.layer_toad_CDC:
layer_note1 39, 0x30, 127
layer_end

.sound_toad_ooof:
chan_setbank 15
chan_setinstr 11
chan_setlayer 0, .layer_toad_CEA
chan_end

.layer_toad_CEA:
layer_note1 39, 0x30, 127
layer_end

.sound_toad_here_we_go:
chan_setbank 15
chan_setinstr 12
chan_setlayer 0, .layer_toad_CF8
chan_end

.layer_toad_CF8:
layer_note1 39, 0x85, 127
layer_end

.sound_toad_yawning:
chan_setbank 15
chan_setinstr 13
chan_setlayer 0, .layer_toad_D09
chan_end

.layer_toad_D09:
layer_note1 39, 0x7f, 127
layer_end

.sound_toad_snoring1:
chan_setbank 15
chan_setinstr 14
chan_setlayer 0, .layer_toad_D17
chan_end

.layer_toad_D17:
layer_note1 39, 0x60, 127
layer_end

.sound_toad_snoring2:
chan_setbank 15
chan_setinstr 15
chan_setlayer 0, .layer_toad_D25
chan_end

.layer_toad_D25:
layer_note1 39, 0x5c, 127
layer_end

.sound_toad_waaaooow:
chan_setbank 16
chan_setinstr 0
chan_setlayer 0, .layer_toad_D33
chan_end

.layer_toad_D33:
layer_note1 39, 0xaa, 127
layer_end

.sound_toad_haha:
chan_setbank 15
chan_setinstr 3
chan_setlayer 0, .layer_toad_D42
chan_end

.layer_toad_D42:
layer_note1 39, 0x4d, 127
layer_end

.sound_toad_uh2:
chan_setbank 16
chan_setinstr 6
chan_setlayer 0, .layer_toad_D50
chan_end

.layer_toad_D50:
layer_note1 39, 0x1e, 127
layer_end

.sound_toad_on_fire:
chan_setbank 16
chan_setinstr 5
chan_setlayer 0, .layer_toad_D5E
chan_end

.layer_toad_D5E:
layer_note1 39, 0xc8, 127
layer_end

.sound_toad_dying:
chan_setbank 16
chan_setinstr 4
chan_setlayer 0, .layer_toad_D6D
chan_end

.layer_toad_D6D:
layer_note1 39, 0x8c, 127
layer_end

.sound_toad_panting_cold:
chan_setbank 16
chan_setinstr 2
chan_setlayer 0, .layer_toad_D7C
chan_end

.layer_toad_D7C:
layer_transpose -2
layer_portamento 0x82, 35, 255
layer_note1 38, 0x30, 127
layer_end

.sound_toad_panting1:
chan_setbank 16
chan_setinstr 2
chan_setlayer 0, .layer_toad_D8E
chan_end

.layer_toad_D8E:
layer_transpose -2
layer_note1 39, 0x3c, 100
layer_end

.sound_toad_panting2:
chan_setbank 16
chan_setinstr 2
chan_setlayer 0, .layer_toad_D9C
chan_end

.layer_toad_D9C:
layer_transpose -2
layer_delay 0x4
layer_note1 38, 0x3c, 100
layer_end

.sound_toad_panting3:
chan_setbank 16
chan_setinstr 2
chan_setlayer 0, .layer_toad_DAC
chan_end

.layer_toad_DAC:
layer_transpose -2
layer_delay 0x8
layer_note1 40, 0x3c, 100
layer_end

.sound_toad_coughing1:
chan_setbank 16
chan_setinstr 7
chan_setlayer 0, .layer_toad_DBC
chan_end

.layer_toad_DBC:
layer_transpose -2
layer_note1 39, 0x10, 115
layer_end

.sound_toad_coughing2:
chan_setbank 16
chan_setinstr 7
chan_setlayer 0, .layer_toad_DCA
chan_end

.layer_toad_DCA:
layer_transpose -2
layer_portamento 0x81, 38, 255
layer_note1 41, 0x18, 115
layer_end

.sound_toad_coughing3:
chan_setbank 16
chan_setinstr 7
chan_setlayer 0, .layer_toad_DDC
chan_end

.layer_toad_DDC:
layer_transpose -2
layer_somethingon
layer_portamento 0x85, 38, 255
layer_note1 41, 0xc, 115
layer_note1 35, 0x12, 115
layer_end

.sound_toad_punch_yah:
chan_setbank 16
chan_setinstr 9
chan_setlayer 0, .layer_toad_DFE
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_toad_538
chan_end

.layer_toad_538:
layer_portamento 0x81, 46, 255
layer_note1 39, 0xf, 127
layer_end

.layer_toad_DFE:
layer_jump .layer_toad_C5C

.sound_toad_punch_hoo:
chan_setbank 16
chan_setinstr 10
chan_setlayer 0, .layer_toad_E17
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_toad_548
chan_end

.layer_toad_548:
layer_note1 39, 0x12, 127
layer_end

.layer_toad_E17:
layer_note1 39, 0x30, 127
layer_end

.sound_toad_mama_mia:
chan_setbank 16
chan_setinstr 11
chan_setlayer 0, .layer_toad_E29
chan_end

.layer_toad_E29:
layer_note1 39, 0x8c, 127
layer_end

.sound_toad_okey_dokey:
chan_setbank 16
chan_setinstr 12
chan_setlayer 0, .layer_toad_E3A
chan_end

.layer_toad_E3A:
layer_note1 39, 0x60, 127
layer_end

.sound_toad_ground_pound_wah:
chan_jump .sound_toad_wah2

.sound_toad_drowning:
chan_setbank 16
chan_setinstr 13
chan_setlayer 0, .layer_toad_E49
chan_end

.layer_toad_E49:
layer_note1 39, 0x91, 127
layer_end

.sound_toad_punch_wah:
chan_setbank 15
chan_setinstr 1
chan_setlayer 0, .layer_toad_E62
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_toad_536
chan_end

.layer_toad_536:
layer_transpose 1

.layer_toad_E62:
layer_jump .layer_toad_C4E

.ifndef VERSION_JP
  .sound_peach_dear_toad:
  chan_setbank 16
  chan_setinstr 15
  chan_setlayer 0, .layer_toad_E6F
  chan_end

  .layer_toad_E6F:
  layer_note1 39, 0x2bc, 127
  layer_end

  .sound_toad_waha:
  chan_setbank 15
  chan_setinstr 24
  chan_setlayer 0, .layer_toad_E7C
  chan_end

  .layer_toad_E7C:
  layer_note1 39, 0x5a, 127
  layer_end

  .sound_toad_yippee:
  chan_setbank 15
  chan_setinstr 25
  chan_setlayer 0, .layer_toad_E88
  chan_end

  .layer_toad_E88:
  layer_note1 39, 0x5a, 127
  layer_end

  .sound_toad_doh:
  chan_setbank 15
  chan_setinstr 16
  chan_setlayer 0, .layer_toad_E94
  chan_end

  .layer_toad_E94:
  layer_note1 39, 0x46, 127
  layer_end

  .sound_toad_game_over:
  chan_setbank 15
  chan_setinstr 17
  chan_setlayer 0, .layer_toad_EA0
  chan_end

  .layer_toad_EA0:
  layer_note1 39, 0x55, 127
  layer_end

  .sound_toad_hello:
  chan_setbank 15
  chan_setinstr 18
  chan_setlayer 0, .layer_toad_EAC
  chan_end

  .layer_toad_EAC:
  layer_note1 39, 0x46, 127
  layer_end

  .sound_toad_press_start_to_play:
  chan_setbank 15
  chan_setinstr 19
  chan_setlayer 0, .layer_toad_EB8
  chan_end

  .layer_toad_EB8:
  layer_note1 39, 0x12c, 127
  layer_end

  .sound_toad_twirl_bounce:
  chan_setbank 15
  chan_setinstr 20
  chan_setlayer 0, .layer_toad_EC5
  chan_end

  .layer_toad_EC5:
  layer_note1 39, 0x30, 127
  layer_end

  .sound_toad_snoring3:
  chan_setbank 15
  chan_setlayer 0, .layer_toad_ECF
  chan_end

  .layer_toad_ECF:
  layer_delay 0x4e
  .layer_toad_ED1:
  layer_loop 50
  layer_call .layer_toad_fn_EE1
  layer_loopend
  layer_setinstr 21
  layer_note1 39, 0x44c, 127
  layer_jump .layer_toad_ED1
  layer_end

  .layer_toad_fn_EE1:
  layer_setinstr 21
  layer_note1 39, 0x53, 127
  layer_setinstr 15
  layer_note1 39, 0x4e, 127
  layer_end

  .sound_toad_so_longa_bowser:
  chan_setbank 15
  chan_setinstr 22
  chan_setlayer 0, .layer_toad_EF7
  chan_setlayer 1, .layer_toad_EF7
  chan_end

  .layer_toad_EF7:
  layer_note1 39, 0xc8, 127
  layer_end

  .sound_toad_ima_tired:
  chan_setbank 15
  chan_setinstr 23
  chan_setlayer 0, .layer_toad_F08
  chan_end

  .layer_toad_F08:
  layer_note1 39, 0x96, 127
  layer_end

  .sound_toad_lets_a_go:
  chan_setbank 15
  chan_setinstr 26
  chan_setlayer 0, .layer_toad_311D
  chan_end

  .layer_toad_311D:
  layer_note1 39, 0x5A, 127
  layer_end
.endif
