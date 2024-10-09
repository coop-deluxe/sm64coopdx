.channel10:
chan_largenoteson
chan_setinstr 0
chan_setpanmix 127
chan_setnotepriority 14
chan_setval 0
chan_iowriteval 5
chan_stereoheadseteffects 1
chan_setdyntable .channel10_table
chan_jump .main_loop_luigi

.main_loop_luigi:
chan_delay1
chan_ioreadval 0
chan_bltz .main_loop_luigi
.start_playing_luigi:
chan_freelayer 0
chan_freelayer 1
chan_freelayer 2
chan_setval 0
chan_iowriteval 5
chan_ioreadval 4
chan_dyncall


.poll_luigi:
chan_delay1
chan_ioreadval 0
chan_bltz .skip_luigi
  chan_beqz .force_stop_luigi
  chan_jump .start_playing_luigi
.skip_luigi:
chan_testlayerfinished 0
chan_beqz .poll_luigi
chan_jump .main_loop_luigi
.force_stop_luigi:
chan_freelayer 0
chan_freelayer 1
chan_freelayer 2
chan_jump .main_loop_luigi

.channel10_table:
sound_ref .sound_luigi_jump_yah
sound_ref .sound_luigi_jump_wah
sound_ref .sound_luigi_jump_hoo
sound_ref .sound_luigi_hoohoo
sound_ref .sound_luigi_yahoo
sound_ref .sound_luigi_uh
sound_ref .sound_luigi_hrmm
sound_ref .sound_luigi_wah2
sound_ref .sound_luigi_whoa
sound_ref .sound_luigi_eeuh
sound_ref .sound_luigi_attacked
sound_ref .sound_luigi_ooof
sound_ref .sound_luigi_here_we_go
sound_ref .sound_luigi_yawning
sound_ref .sound_luigi_snoring1
sound_ref .sound_luigi_snoring2
sound_ref .sound_luigi_waaaooow
sound_ref .sound_luigi_haha
sound_ref .sound_luigi_panting1
sound_ref .sound_luigi_uh2
sound_ref .sound_luigi_on_fire
sound_ref .sound_luigi_dying
sound_ref .sound_luigi_panting_cold
sound_ref .sound_luigi_coughing3
sound_ref .sound_luigi_panting1
sound_ref .sound_luigi_panting2
sound_ref .sound_luigi_panting3
sound_ref .sound_luigi_coughing1
sound_ref .sound_luigi_coughing2
sound_ref .sound_luigi_coughing3
sound_ref .sound_luigi_punch_yah
sound_ref .sound_luigi_punch_hoo
sound_ref .sound_luigi_mama_mia
sound_ref .sound_luigi_okey_dokey
sound_ref .sound_luigi_ground_pound_wah
sound_ref .sound_luigi_drowning
sound_ref .sound_luigi_punch_wah
sound_ref .sound_luigi_uh
sound_ref .sound_luigi_hrmm
sound_ref .sound_luigi_wah2
.ifdef VERSION_JP
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
.else
  sound_ref .sound_peach_dear_luigi
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_jump_hoo
  sound_ref .sound_luigi_yahoo
  sound_ref .sound_luigi_yahoo
  sound_ref .sound_luigi_yahoo
  sound_ref .sound_luigi_waha
  sound_ref .sound_luigi_yippee
  sound_ref .sound_luigi_doh
  sound_ref .sound_luigi_game_over
  sound_ref .sound_luigi_hello
  sound_ref .sound_luigi_press_start_to_play
  sound_ref .sound_luigi_twirl_bounce
  sound_ref .sound_luigi_snoring3
  sound_ref .sound_luigi_so_longa_bowser
  sound_ref .sound_luigi_ima_tired
  sound_ref .sound_luigi_lets_a_go
.endif

.sound_luigi_jump_hoo:
chan_setbank 11
chan_setinstr 0
chan_setlayer 0, .layer_luigi_C3C
chan_end

.layer_luigi_C3C:
layer_note1 39, 0x14, 127
layer_end

.sound_luigi_jump_wah:
chan_setbank 11
chan_setinstr 1
chan_setlayer 0, .layer_luigi_C4C
chan_end

.layer_luigi_C4C:
.layer_luigi_C4E:
layer_note1 39, 0x18, 127
layer_end

.sound_luigi_jump_yah:
chan_setbank 12
chan_setinstr 9
chan_setlayer 0, .layer_luigi_C5A
chan_end

.layer_luigi_C5A:
.layer_luigi_C5C:
layer_note1 39, 0x24, 127
layer_end

.sound_luigi_hoohoo:
chan_setbank 12
chan_setinstr 1
chan_setlayer 0, .layer_luigi_C6C
chan_end

.layer_luigi_C6C:
layer_note1 39, 0x30, 127
layer_end

.sound_luigi_yahoo:
chan_setbank 11
chan_setinstr 4
chan_setlayer 0, .layer_luigi_C7C
chan_end

.layer_luigi_C7C:

layer_somethingon
layer_note1 39, 0x1e, 127
layer_note1 39, 0x41, 127
layer_end

.sound_luigi_uh:
chan_setbank 11
chan_setinstr 5
chan_setlayer 0, .layer_luigi_C92
chan_end

.layer_luigi_C92:
layer_note1 39, 0x2b, 127
layer_end

.sound_luigi_hrmm:
chan_setbank 11
chan_setinstr 6
chan_setlayer 0, .layer_luigi_CA4
chan_end

.layer_luigi_CA4:
layer_note1 39, 0x1e, 127
layer_end

.sound_luigi_wah2:
chan_setbank 11
chan_setinstr 7
chan_setlayer 0, .layer_luigi_CB2
chan_end

.layer_luigi_CB2:
layer_note1 39, 0x1c, 127
layer_end

.sound_luigi_whoa:
chan_setbank 11
chan_setinstr 8
chan_setlayer 0, .layer_luigi_CC0
chan_end

.layer_luigi_CC0:
layer_note1 39, 0x30, 127
layer_end

.sound_luigi_eeuh:
chan_setbank 11
chan_setinstr 9
chan_setlayer 0, .layer_luigi_CCE
chan_end

.layer_luigi_CCE:
layer_note1 39, 0x44, 127
layer_end

.sound_luigi_attacked:
chan_setbank 11
chan_setinstr 10
chan_setlayer 0, .layer_luigi_CDC
chan_end

.layer_luigi_CDC:
layer_note1 39, 0x30, 127
layer_end

.sound_luigi_ooof:
chan_setbank 11
chan_setinstr 11
chan_setlayer 0, .layer_luigi_CEA
chan_end

.layer_luigi_CEA:
layer_note1 39, 0x30, 127
layer_end

.sound_luigi_here_we_go:
chan_setbank 11
chan_setinstr 12
chan_setlayer 0, .layer_luigi_CF8
chan_end

.layer_luigi_CF8:
layer_note1 39, 0x85, 127
layer_end

.sound_luigi_yawning:
chan_setbank 11
chan_setinstr 13
chan_setlayer 0, .layer_luigi_D09
chan_end

.layer_luigi_D09:
layer_note1 39, 0x7f, 127
layer_end

.sound_luigi_snoring1:
chan_setbank 11
chan_setinstr 14
chan_setlayer 0, .layer_luigi_D17
chan_end

.layer_luigi_D17:
layer_transpose -2
layer_note1 39, 0x60, 64
layer_end

.sound_luigi_snoring2:
chan_setbank 11
chan_setinstr 15
chan_setlayer 0, .layer_luigi_D25
chan_end

.layer_luigi_D25:
layer_transpose -2
layer_note1 39, 0x5c, 52
layer_end

.sound_luigi_waaaooow:
chan_setbank 12
chan_setinstr 0
chan_setlayer 0, .layer_luigi_D33
chan_end

.layer_luigi_D33:
layer_note1 39, 0xaa, 127
layer_end

.sound_luigi_haha:
chan_setbank 11
chan_setinstr 3
chan_setlayer 0, .layer_luigi_D42
chan_end

.layer_luigi_D42:
layer_note1 39, 0x4d, 127
layer_end

.sound_luigi_uh2:
chan_setbank 12
chan_setinstr 6
chan_setlayer 0, .layer_luigi_D50
chan_end

.layer_luigi_D50:
layer_note1 39, 0x28, 127
layer_end

.sound_luigi_on_fire:
chan_setbank 12
chan_setinstr 5
chan_setlayer 0, .layer_luigi_D5E
chan_end

.layer_luigi_D5E:
layer_note1 39, 0xc8, 127
layer_end

.sound_luigi_dying:
chan_setbank 12
chan_setinstr 4
chan_setlayer 0, .layer_luigi_D6D
chan_end

.layer_luigi_D6D:
layer_note1 39, 0x8c, 127
layer_end

.sound_luigi_panting_cold:
chan_setbank 12
chan_setinstr 2
chan_setlayer 0, .layer_luigi_D7C
chan_end

.layer_luigi_D7C:
layer_transpose -2
layer_portamento 0x82, 35, 255
layer_note1 38, 0x30, 127
layer_end

.sound_luigi_panting1:
chan_setbank 12
chan_setinstr 2
chan_setlayer 0, .layer_luigi_D8E
chan_end

.layer_luigi_D8E:
layer_transpose -2
layer_note1 39, 0x3c, 100
layer_end

.sound_luigi_panting2:
chan_setbank 12
chan_setinstr 2
chan_setlayer 0, .layer_luigi_D9C
chan_end

.layer_luigi_D9C:
layer_transpose -2
layer_delay 0x4
layer_note1 38, 0x3c, 100
layer_end

.sound_luigi_panting3:
chan_setbank 12
chan_setinstr 2
chan_setlayer 0, .layer_luigi_DAC
chan_end

.layer_luigi_DAC:
layer_transpose -2
layer_delay 0x8
layer_note1 40, 0x3c, 100
layer_end

.sound_luigi_coughing1:
chan_setbank 12
chan_setinstr 7
chan_setlayer 0, .layer_luigi_DBC
chan_end

.layer_luigi_DBC:
layer_transpose -2
layer_note1 39, 0x10, 115
layer_end

.sound_luigi_coughing2:
chan_setbank 12
chan_setinstr 7
chan_setlayer 0, .layer_luigi_DCA
chan_end

.layer_luigi_DCA:
layer_transpose -2
layer_portamento 0x81, 38, 255
layer_note1 41, 0x18, 115
layer_end

.sound_luigi_coughing3:
chan_setbank 12
chan_setinstr 7
chan_setlayer 0, .layer_luigi_DDC
chan_end

.layer_luigi_DDC:
layer_transpose -2
layer_somethingon
layer_portamento 0x85, 38, 255
layer_note1 41, 0xc, 115
layer_note1 35, 0x12, 115
layer_end

.sound_luigi_punch_yah:
chan_setbank 12
chan_setinstr 9
chan_setlayer 0, .layer_luigi_DFE
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_luigi_538
chan_end

.layer_luigi_538:
layer_portamento 0x81, 46, 255
layer_note1 39, 0xf, 127
layer_end

.layer_luigi_DFE:
layer_jump .layer_luigi_C5C

.sound_luigi_punch_hoo:
chan_setbank 12
chan_setinstr 10
chan_setlayer 0, .layer_luigi_E17
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_luigi_548
chan_end

.layer_luigi_548:
layer_note1 39, 0x12, 127
layer_end

.layer_luigi_E17:
layer_note1 39, 0x30, 127
layer_end

.sound_luigi_mama_mia:
chan_setbank 12
chan_setinstr 11
chan_setlayer 0, .layer_luigi_E29
chan_end

.layer_luigi_E29:
layer_note1 39, 0x8c, 127
layer_end

.sound_luigi_okey_dokey:
chan_setbank 12
chan_setinstr 12
chan_setlayer 0, .layer_luigi_E3A
chan_end

.layer_luigi_E3A:
layer_note1 39, 0x60, 127
layer_end

.sound_luigi_ground_pound_wah:
chan_jump .sound_luigi_wah2

.sound_luigi_drowning:
chan_setbank 12
chan_setinstr 13
chan_setlayer 0, .layer_luigi_E49
chan_end

.layer_luigi_E49:
layer_note1 39, 0x91, 127
layer_end

.sound_luigi_punch_wah:
chan_setbank 11
chan_setinstr 1
chan_setlayer 0, .layer_luigi_E62
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_luigi_536
chan_end

.layer_luigi_536:
layer_transpose 1

.layer_luigi_E62:
layer_jump .layer_luigi_C4E

.ifndef VERSION_JP
  .sound_peach_dear_luigi:
  chan_setbank 12
  chan_setinstr 15
  chan_setlayer 0, .layer_luigi_E6F
  chan_end

  .layer_luigi_E6F:
  layer_note1 39, 0x2bc, 127
  layer_end

  .sound_luigi_waha:
  chan_setbank 11
  chan_setinstr 24
  chan_setlayer 0, .layer_luigi_E7C
  chan_end

  .layer_luigi_E7C:
  layer_note1 39, 0x5a, 127
  layer_end

  .sound_luigi_yippee:
  chan_setbank 11
  chan_setinstr 25
  chan_setlayer 0, .layer_luigi_E88
  chan_end

  .layer_luigi_E88:
  layer_note1 39, 0x5a, 127
  layer_end

  .sound_luigi_doh:
  chan_setbank 11
  chan_setinstr 16
  chan_setlayer 0, .layer_luigi_E94
  chan_end

  .layer_luigi_E94:
  layer_note1 39, 0x46, 127
  layer_end

  .sound_luigi_game_over:
  chan_setbank 11
  chan_setinstr 17
  chan_setlayer 0, .layer_luigi_EA0
  chan_end

  .layer_luigi_EA0:
  layer_note1 39, 0x55, 127
  layer_end

  .sound_luigi_hello:
  chan_setbank 11
  chan_setinstr 18
  chan_setlayer 0, .layer_luigi_EAC
  chan_end

  .layer_luigi_EAC:
  layer_note1 39, 0x46, 127
  layer_end

  .sound_luigi_press_start_to_play:
  chan_setbank 11
  chan_setinstr 19
  chan_setlayer 0, .layer_luigi_EB8
  chan_end

  .layer_luigi_EB8:
  layer_note1 39, 0x12c, 127
  layer_end

  .sound_luigi_twirl_bounce:
  chan_setbank 11
  chan_setinstr 20
  chan_setlayer 0, .layer_luigi_EC5
  chan_end

  .layer_luigi_EC5:
  layer_note1 39, 0x30, 127
  layer_end

  .sound_luigi_snoring3:
  chan_setbank 11
  chan_setlayer 0, .layer_luigi_ECF
  chan_end

  .layer_luigi_ECF:
  layer_delay 0x4e
  .layer_luigi_ED1:
  layer_loop 50
  layer_call .layer_luigi_fn_EE1
  layer_loopend
  layer_setinstr 21
  layer_note1 39, 0x44c, 127
  layer_jump .layer_luigi_ED1
  layer_end

  .layer_luigi_fn_EE1:
  layer_setinstr 21
  layer_note1 37, 0x53, 127
  layer_setinstr 15
  layer_note1 37, 0x4e, 64
  layer_end

  .sound_luigi_so_longa_bowser:
  chan_setbank 11
  chan_setinstr 22
  chan_setlayer 0, .layer_luigi_EF7
  chan_setlayer 1, .layer_luigi_EF7
  chan_end

  .layer_luigi_EF7:
  layer_note1 39, 0xc8, 127
  layer_end

  .sound_luigi_ima_tired:
  chan_setbank 11
  chan_setinstr 23
  chan_setlayer 0, .layer_luigi_F08
  chan_end

  .layer_luigi_F08:
  layer_note1 39, 0x96, 127
  layer_end

  .sound_luigi_lets_a_go:
  chan_setbank 11
  chan_setinstr 26
  chan_setlayer 0, .layer_luigi_311D
  chan_end

  .layer_luigi_311D:
  layer_note1 39, 0x46, 127
  layer_end
.endif
