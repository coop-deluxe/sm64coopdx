.channel11:
chan_largenoteson
chan_setinstr 0
chan_setpanmix 127
chan_setnotepriority 14
chan_setval 0
chan_iowriteval 5
chan_stereoheadseteffects 1
chan_setdyntable .channel11_table
chan_jump .main_loop_wario

.main_loop_wario:
chan_delay1
chan_ioreadval 0
chan_bltz .main_loop_wario
.start_playing_wario:
chan_freelayer 0
chan_freelayer 1
chan_freelayer 2
chan_setval 0
chan_iowriteval 5
chan_ioreadval 4
chan_dyncall


.poll_wario:
chan_delay1
chan_ioreadval 0
chan_bltz .skip_wario
  chan_beqz .force_stop_wario
  chan_jump .start_playing_wario
.skip_wario:
chan_testlayerfinished 0
chan_beqz .poll_wario
chan_jump .main_loop_wario
.force_stop_wario:
chan_freelayer 0
chan_freelayer 1
chan_freelayer 2
chan_jump .main_loop_wario

.channel11_table:
sound_ref .sound_wario_jump_yah
sound_ref .sound_wario_jump_wah
sound_ref .sound_wario_jump_hoo
sound_ref .sound_wario_hoohoo
sound_ref .sound_wario_yahoo
sound_ref .sound_wario_uh
sound_ref .sound_wario_hrmm
sound_ref .sound_wario_wah2
sound_ref .sound_wario_whoa
sound_ref .sound_wario_eeuh
sound_ref .sound_wario_attacked
sound_ref .sound_wario_ooof
sound_ref .sound_wario_here_we_go
sound_ref .sound_wario_yawning
sound_ref .sound_wario_snoring1
sound_ref .sound_wario_snoring2
sound_ref .sound_wario_waaaooow
sound_ref .sound_wario_haha
sound_ref .sound_wario_panting1
sound_ref .sound_wario_uh2
sound_ref .sound_wario_on_fire
sound_ref .sound_wario_dying
sound_ref .sound_wario_panting_cold
sound_ref .sound_wario_coughing3
sound_ref .sound_wario_panting1
sound_ref .sound_wario_panting2
sound_ref .sound_wario_panting3
sound_ref .sound_wario_coughing1
sound_ref .sound_wario_coughing2
sound_ref .sound_wario_coughing3
sound_ref .sound_wario_punch_yah
sound_ref .sound_wario_punch_hoo
sound_ref .sound_wario_mama_mia
sound_ref .sound_wario_okey_dokey
sound_ref .sound_wario_ground_pound_wah
sound_ref .sound_wario_drowning
sound_ref .sound_wario_punch_wah
sound_ref .sound_wario_uh
sound_ref .sound_wario_hrmm
sound_ref .sound_wario_wah2
.ifdef VERSION_JP
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
.else
  sound_ref .sound_peach_dear_wario
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_jump_hoo
  sound_ref .sound_wario_yahoo
  sound_ref .sound_wario_yahoo
  sound_ref .sound_wario_yahoo
  sound_ref .sound_wario_waha
  sound_ref .sound_wario_yippee
  sound_ref .sound_wario_doh
  sound_ref .sound_wario_game_over
  sound_ref .sound_wario_hello
  sound_ref .sound_wario_press_start_to_play
  sound_ref .sound_wario_twirl_bounce
  sound_ref .sound_wario_snoring3
  sound_ref .sound_wario_so_longa_bowser
  sound_ref .sound_wario_ima_tired
  sound_ref .sound_wario_lets_a_go
.endif

.sound_wario_jump_hoo:
chan_setbank 13
chan_setinstr 0
chan_setlayer 0, .layer_wario_C3C
chan_end

.layer_wario_C3C:
layer_note1 39, 0x61, 127
layer_end

.sound_wario_jump_wah:
chan_setbank 13
chan_setinstr 1
chan_setlayer 0, .layer_wario_C4C
chan_end

.layer_wario_C4C:
.layer_wario_C4E:
layer_note1 39, 0x34, 127
layer_end

.sound_wario_jump_yah:
chan_setbank 14
chan_setinstr 9
chan_setlayer 0, .layer_wario_C5A
chan_end

.layer_wario_C5A:
layer_note1 39, 0x4d, 127
layer_end

.layer_wario_C5C:
layer_note1 39, 0x24, 127
layer_end

.sound_wario_hoohoo:
chan_setbank 14
chan_setinstr 1
chan_setlayer 0, .layer_wario_C6C
chan_end

.layer_wario_C6C:
layer_note1 39, 0x6e, 127
layer_end

.sound_wario_yahoo:
chan_setbank 13
chan_setinstr 4
chan_setlayer 0, .layer_wario_C7C
chan_end

.layer_wario_C7C:
layer_note1 39, 0xb8, 127
layer_end

.sound_wario_uh:
chan_setbank 13
chan_setinstr 5
chan_setlayer 0, .layer_wario_C92
chan_end

.layer_wario_C92:
layer_note1 39, 0x27, 127
layer_end

.sound_wario_hrmm:
chan_setbank 13
chan_setinstr 6
chan_setlayer 0, .layer_wario_CA4
chan_end

.layer_wario_CA4:
layer_note1 39, 0x3f, 127
layer_end

.sound_wario_wah2:
chan_setbank 13
chan_setinstr 7
chan_setlayer 0, .layer_wario_CB2
chan_end

.layer_wario_CB2:
layer_note1 39, 0x74, 127
layer_end

.sound_wario_whoa:
chan_setbank 13
chan_setinstr 8
chan_setlayer 0, .layer_wario_CC0
chan_end

.layer_wario_CC0:
layer_note1 39, 0x4c, 127
layer_end

.sound_wario_eeuh:
chan_setbank 13
chan_setinstr 9
chan_setlayer 0, .layer_wario_CCE
chan_end

.layer_wario_CCE:
layer_note1 39, 0x43, 127
layer_end

.sound_wario_attacked:
chan_setbank 13
chan_setinstr 10
chan_setlayer 0, .layer_wario_CDC
chan_end

.layer_wario_CDC:
layer_note1 39, 0x33, 127
layer_end

.sound_wario_ooof:
chan_setbank 13
chan_setinstr 11
chan_setlayer 0, .layer_wario_CEA
chan_end

.layer_wario_CEA:
layer_note1 39, 0x3c, 127
layer_end

.sound_wario_here_we_go:
chan_setbank 13
chan_setinstr 12
chan_setlayer 0, .layer_wario_CF8
chan_end

.layer_wario_CF8:
layer_note1 39, 0xbf, 127
layer_end

.sound_wario_yawning:
chan_setbank 13
chan_setinstr 13
chan_setlayer 0, .layer_wario_D09
chan_end

.layer_wario_D09:
layer_note1 39, 0x14c, 127
layer_end

.sound_wario_snoring1:
chan_setbank 13
chan_setinstr 14
chan_setlayer 0, .layer_wario_D17
chan_end

.layer_wario_D17:
layer_note1 39, 0xce, 127
layer_end

.sound_wario_snoring2:
chan_setbank 13
chan_setinstr 15
chan_setlayer 0, .layer_wario_D25
chan_end

.layer_wario_D25:
layer_note1 39, 0xa1, 127
layer_end

.sound_wario_waaaooow:
chan_setbank 14
chan_setinstr 0
chan_setlayer 0, .layer_wario_D33
chan_end

.layer_wario_D33:
layer_note1 39, 0x121, 127
layer_end

.sound_wario_haha:
chan_setbank 13
chan_setinstr 3
chan_setlayer 0, .layer_wario_D42
chan_end

.layer_wario_D42:
layer_note1 39, 0x159, 127
layer_end

.sound_wario_uh2:
chan_setbank 14
chan_setinstr 6
chan_setlayer 0, .layer_wario_D50
chan_end

.layer_wario_D50:
layer_note1 39, 0x9b, 127
layer_end

.sound_wario_on_fire:
chan_setbank 14
chan_setinstr 5
chan_setlayer 0, .layer_wario_D5E
chan_end

.layer_wario_D5E:
layer_note1 39, 0x34, 127
layer_end

.sound_wario_dying:
chan_setbank 14
chan_setinstr 4
chan_setlayer 0, .layer_wario_D6D
chan_end

.layer_wario_D6D:
layer_note1 39, 0xe5, 127
layer_end

.sound_wario_panting_cold:
chan_setbank 14
chan_setinstr 2
chan_setlayer 0, .layer_wario_D7C
chan_end

.layer_wario_D7C:
layer_transpose -2
layer_portamento 0x82, 35, 255
layer_note1 38, 0x30, 127
layer_end

.sound_wario_panting1:
chan_setbank 14
chan_setinstr 2
chan_setlayer 0, .layer_wario_D8E
chan_end

.layer_wario_D8E:
layer_transpose -2
layer_note1 39, 0x3c, 100
layer_end

.sound_wario_panting2:
chan_setbank 14
chan_setinstr 2
chan_setlayer 0, .layer_wario_D9C
chan_end

.layer_wario_D9C:
layer_transpose -2
layer_delay 0x4
layer_note1 38, 0x3c, 100
layer_end

.sound_wario_panting3:
chan_setbank 14
chan_setinstr 2
chan_setlayer 0, .layer_wario_DAC
chan_end

.layer_wario_DAC:
layer_transpose -2
layer_delay 0x8
layer_note1 40, 0x3c, 100
layer_end

.sound_wario_coughing1:
chan_setbank 14
chan_setinstr 7
chan_setlayer 0, .layer_wario_DBC
chan_end

.layer_wario_DBC:
layer_transpose -2
layer_note1 39, 0x10, 115
layer_end

.sound_wario_coughing2:
chan_setbank 14
chan_setinstr 7
chan_setlayer 0, .layer_wario_DCA
chan_end

.layer_wario_DCA:
layer_transpose -2
layer_portamento 0x81, 38, 255
layer_note1 41, 0x18, 115
layer_end

.sound_wario_coughing3:
chan_setbank 14
chan_setinstr 7
chan_setlayer 0, .layer_wario_DDC
chan_end

.layer_wario_DDC:
layer_transpose -2
layer_somethingon
layer_portamento 0x85, 38, 255
layer_note1 41, 0xc, 115
layer_note1 35, 0x12, 115
layer_end

.sound_wario_punch_yah:
chan_setbank 14
chan_setinstr 9
chan_setlayer 0, .layer_wario_DFE
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_wario_539
chan_end

.layer_wario_539:
layer_note1 39, 0xf, 127
layer_end

.layer_wario_DFE:
layer_jump .layer_wario_C5C

.sound_wario_punch_hoo:
chan_setbank 14
chan_setinstr 10
chan_setlayer 0, .layer_wario_E17
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_wario_548
chan_end

.layer_wario_548:
layer_note1 39, 0x12, 127
layer_end

.layer_wario_E17:
layer_note1 39, 0xa3, 127
layer_end

.sound_wario_mama_mia:
chan_setbank 14
chan_setinstr 11
chan_setlayer 0, .layer_wario_E29
chan_end

.layer_wario_E29:
layer_note1 39, 0xd9, 127
layer_end

.sound_wario_okey_dokey:
chan_setbank 14
chan_setinstr 12
chan_setlayer 0, .layer_wario_E3A
chan_end

.layer_wario_E3A:
layer_note1 39, 0x133, 127
layer_end

.sound_wario_ground_pound_wah:
chan_jump .sound_wario_wah2

.sound_wario_drowning:
chan_setbank 14
chan_setinstr 13
chan_setlayer 0, .layer_wario_E49
chan_end

.layer_wario_E49:
layer_note1 39, 0xf4, 127
layer_end

.sound_wario_punch_wah:
chan_setbank 13
chan_setinstr 1
chan_setlayer 0, .layer_wario_E62
chan_setval 1
chan_call .delay
chan_setbank 0
chan_setinstr 0
chan_setlayer 1, .layer_wario_536
chan_end

.layer_wario_536:

.layer_wario_E62:
layer_jump .layer_wario_C4E

.ifndef VERSION_JP
  .sound_peach_dear_wario:
  chan_setbank 14
  chan_setinstr 15
  chan_setlayer 0, .layer_wario_E6F
  chan_end

  .layer_wario_E6F:
  layer_note1 39, 0x3b, 127
  layer_end

  .sound_wario_waha:
  chan_setbank 13
  chan_setinstr 24
  chan_setlayer 0, .layer_wario_E7C
  chan_end

  .layer_wario_E7C:
  layer_note1 39, 0x95, 127
  layer_end

  .sound_wario_yippee:
  chan_setbank 13
  chan_setinstr 25
  chan_setlayer 0, .layer_wario_E88
  chan_end

  .layer_wario_E88:
  layer_note1 39, 0xa2, 127
  layer_end

  .sound_wario_doh:
  chan_setbank 13
  chan_setinstr 16
  chan_setlayer 0, .layer_wario_E94
  chan_end

  .layer_wario_E94:
  layer_note1 39, 0x2e, 127
  layer_end

  .sound_wario_game_over:
  chan_setbank 13
  chan_setinstr 17
  chan_setlayer 0, .layer_wario_EA0
  chan_end

  .layer_wario_EA0:
  layer_note1 39, 0xab, 127
  layer_end

  .sound_wario_hello:
  chan_setbank 13
  chan_setinstr 18
  chan_setlayer 0, .layer_wario_EAC
  chan_end

  .layer_wario_EAC:
  layer_note1 39, 0x50, 127
  layer_end

  .sound_wario_press_start_to_play:
  chan_setbank 13
  chan_setinstr 19
  chan_setlayer 0, .layer_wario_EB8
  chan_end

  .layer_wario_EB8:
  layer_note1 39, 0x9c, 127
  layer_end

  .sound_wario_twirl_bounce:
  chan_setbank 13
  chan_setinstr 20
  chan_setlayer 0, .layer_wario_EC5
  chan_end

  .layer_wario_EC5:
  layer_note1 39, 0x6d, 127
  layer_end

  .sound_wario_snoring3:
  chan_setbank 13
  chan_setlayer 0, .layer_wario_ECF
  chan_end

  .layer_wario_ECF:
  layer_delay 0x4e
  .layer_wario_ED1:
  layer_loop 50
  layer_call .layer_wario_fn_EE1
  layer_loopend
  layer_setinstr 21
  layer_note1 39, 0x44c, 127
  layer_jump .layer_wario_ED1
  layer_end

  .layer_wario_fn_EE1:
  layer_setinstr 21
  layer_note1 39, 0x53, 127
  layer_setinstr 15
  layer_note1 39, 0x4e, 127
  layer_end

  .sound_wario_so_longa_bowser:
  chan_setbank 13
  chan_setinstr 22
  chan_setlayer 0, .layer_wario_EF7
  chan_end

  .layer_wario_EF7:
  layer_note1 39, 0xc0, 127
  layer_end

  .sound_wario_ima_tired:
  chan_setbank 13
  chan_setinstr 23
  chan_setlayer 0, .layer_wario_F08
  chan_end

  .layer_wario_F08:
  layer_note1 39, 0xe1, 127
  layer_end

  .sound_wario_lets_a_go:
  chan_setbank 13
  chan_setinstr 26
  chan_setlayer 0, .layer_wario_311D
  chan_end

  .layer_wario_311D:
  layer_note1 39, 0x5A, 127
  layer_end
.endif
