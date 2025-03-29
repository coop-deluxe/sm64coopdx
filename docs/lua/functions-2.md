## [:rewind: Lua Functions](functions.md)

---

[< prev](functions.md) | [1](functions.md) | 2 | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-3.md)]


---
# functions from behavior_actions.h

<br />


## [arc_to_goal_pos](#arc_to_goal_pos)

### Description
Calculates the time it takes for the current object to follow an arc from `pos` to `goal`

### Lua Example
`local integerValue = arc_to_goal_pos(goal, pos, yVel, gravity)`

### Parameters
| Field | Type |
| ----- | ---- |
| goal | [Vec3f](structs.md#Vec3f) |
| pos | [Vec3f](structs.md#Vec3f) |
| yVel | `number` |
| gravity | `number` |

### Returns
- `integer`

### C Prototype
`s32 arc_to_goal_pos(Vec3f goal, Vec3f pos, f32 yVel, f32 gravity);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_common_init](#bhv_1up_common_init)

### Description
Behavior init function for common 1-Up

### Lua Example
`bhv_1up_common_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_common_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_hidden_in_pole_loop](#bhv_1up_hidden_in_pole_loop)

### Description
Behavior loop function for hidden 1-Up in pole (Green Demon)

### Lua Example
`bhv_1up_hidden_in_pole_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_hidden_in_pole_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_hidden_in_pole_spawner_loop](#bhv_1up_hidden_in_pole_spawner_loop)

### Description
Behavior loop function for 1-Up hidden in pole spawner

### Lua Example
`bhv_1up_hidden_in_pole_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_hidden_in_pole_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_hidden_in_pole_trigger_loop](#bhv_1up_hidden_in_pole_trigger_loop)

### Description
Behavior loop function for 1-Up hidden in pole trigger

### Lua Example
`bhv_1up_hidden_in_pole_trigger_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_hidden_in_pole_trigger_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_hidden_loop](#bhv_1up_hidden_loop)

### Description
Behavior loop function for hidden 1-Up

### Lua Example
`bhv_1up_hidden_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_hidden_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_hidden_trigger_loop](#bhv_1up_hidden_trigger_loop)

### Description
Behavior loop function for hidden 1-Up trigger

### Lua Example
`bhv_1up_hidden_trigger_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_hidden_trigger_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_init](#bhv_1up_init)

### Description
Behavior init function for 1-Up

### Lua Example
`bhv_1up_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_jump_on_approach_loop](#bhv_1up_jump_on_approach_loop)

### Description
Behavior loop function for jump on approach 1-Up

### Lua Example
`bhv_1up_jump_on_approach_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_jump_on_approach_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_loop](#bhv_1up_loop)

### Description
Behavior loop function for 1-Up

### Lua Example
`bhv_1up_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_running_away_loop](#bhv_1up_running_away_loop)

### Description
Behavior loop function for running away 1-Up

### Lua Example
`bhv_1up_running_away_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_running_away_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_sliding_loop](#bhv_1up_sliding_loop)

### Description
Behavior loop function for sliding 1-Up

### Lua Example
`bhv_1up_sliding_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_sliding_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_trigger_init](#bhv_1up_trigger_init)

### Description
Behavior init function for 1-Up trigger

### Lua Example
`bhv_1up_trigger_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_trigger_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_1up_walking_loop](#bhv_1up_walking_loop)

### Description
Behavior loop function for walking 1-Up

### Lua Example
`bhv_1up_walking_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_1up_walking_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_act_selector_init](#bhv_act_selector_init)

### Description
Behavior init function for Act Selector

### Lua Example
`bhv_act_selector_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_act_selector_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_act_selector_loop](#bhv_act_selector_loop)

### Description
Behavior loop function for Act Selector

### Lua Example
`bhv_act_selector_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_act_selector_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_act_selector_star_type_loop](#bhv_act_selector_star_type_loop)

### Description
Behavior loop function for Act Selector star type

### Lua Example
`bhv_act_selector_star_type_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_act_selector_star_type_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_activated_back_and_forth_platform_init](#bhv_activated_back_and_forth_platform_init)

### Description
Behavior init function for activated back and forth platform in Bowser courses

### Lua Example
`bhv_activated_back_and_forth_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_activated_back_and_forth_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_activated_back_and_forth_platform_update](#bhv_activated_back_and_forth_platform_update)

### Description
Behavior loop function for activated back and forth platform in Bowser courses

### Lua Example
`bhv_activated_back_and_forth_platform_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_activated_back_and_forth_platform_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_alpha_boo_key_loop](#bhv_alpha_boo_key_loop)

### Description
Behavior loop function for alpha boo key

### Lua Example
`bhv_alpha_boo_key_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_alpha_boo_key_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ambient_light_update](#bhv_ambient_light_update)

### Description
Behavior loop function for the lighting engine ambient light. Takes the first 3 behavior parameter bytes for RGB color

### Lua Example
`bhv_ambient_light_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ambient_light_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ambient_sounds_init](#bhv_ambient_sounds_init)

### Description
Behavior init function for ambient sounds

### Lua Example
`bhv_ambient_sounds_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ambient_sounds_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_animated_texture_loop](#bhv_animated_texture_loop)

### Description
Behavior loop function for animated texture

### Lua Example
`bhv_animated_texture_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_animated_texture_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_animates_on_floor_switch_press_init](#bhv_animates_on_floor_switch_press_init)

### Description
Behavior init function for animates on floor switch press in Rainbow Ride and Bowser courses

### Lua Example
`bhv_animates_on_floor_switch_press_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_animates_on_floor_switch_press_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_animates_on_floor_switch_press_loop](#bhv_animates_on_floor_switch_press_loop)

### Description
Behavior loop function for animates on floor switch press in Rainbow Ride and Bowser courses

### Lua Example
`bhv_animates_on_floor_switch_press_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_animates_on_floor_switch_press_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_arrow_lift_loop](#bhv_arrow_lift_loop)

### Description
Behavior loop function for Wet Dry World arrow lift

### Lua Example
`bhv_arrow_lift_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_arrow_lift_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bbh_tilting_trap_platform_loop](#bhv_bbh_tilting_trap_platform_loop)

### Description
Behavior loop function for Big Boo's Haunt tilting trap platform

### Lua Example
`bhv_bbh_tilting_trap_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bbh_tilting_trap_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_boo_key_loop](#bhv_beta_boo_key_loop)

### Description
Behavior loop function for beta boo key

### Lua Example
`bhv_beta_boo_key_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_boo_key_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_bowser_anchor_loop](#bhv_beta_bowser_anchor_loop)

### Description
Behavior loop function for beta Bowser anchor

### Lua Example
`bhv_beta_bowser_anchor_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_bowser_anchor_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_chest_bottom_init](#bhv_beta_chest_bottom_init)

### Description
Behavior init function for beta chest bottom

### Lua Example
`bhv_beta_chest_bottom_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_chest_bottom_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_chest_bottom_loop](#bhv_beta_chest_bottom_loop)

### Description
Behavior loop function for beta chest bottom

### Lua Example
`bhv_beta_chest_bottom_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_chest_bottom_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_chest_lid_loop](#bhv_beta_chest_lid_loop)

### Description
Behavior loop function for beta chest lid

### Lua Example
`bhv_beta_chest_lid_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_chest_lid_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_fish_splash_spawner_loop](#bhv_beta_fish_splash_spawner_loop)

### Description
Behavior loop function for beta fish splash spawner

### Lua Example
`bhv_beta_fish_splash_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_fish_splash_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_holdable_object_init](#bhv_beta_holdable_object_init)

### Description
Behavior init function for beta holdable object

### Lua Example
`bhv_beta_holdable_object_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_holdable_object_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_holdable_object_loop](#bhv_beta_holdable_object_loop)

### Description
Behavior loop function for beta holdable object

### Lua Example
`bhv_beta_holdable_object_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_holdable_object_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_moving_flames_loop](#bhv_beta_moving_flames_loop)

### Description
Behavior loop function for beta moving flames

### Lua Example
`bhv_beta_moving_flames_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_moving_flames_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_moving_flames_spawn_loop](#bhv_beta_moving_flames_spawn_loop)

### Description
Behavior loop function for beta moving flames spawn

### Lua Example
`bhv_beta_moving_flames_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_moving_flames_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_trampoline_spring_loop](#bhv_beta_trampoline_spring_loop)

### Description
Behavior loop function for beta trampoline spring

### Lua Example
`bhv_beta_trampoline_spring_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_trampoline_spring_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_beta_trampoline_top_loop](#bhv_beta_trampoline_top_loop)

### Description
Behavior loop function for beta trampoline top

### Lua Example
`bhv_beta_trampoline_top_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_beta_trampoline_top_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_big_boo_loop](#bhv_big_boo_loop)

### Description
Behavior loop function for Big Boo

### Lua Example
`bhv_big_boo_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_big_boo_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_big_boulder_generator_loop](#bhv_big_boulder_generator_loop)

### Description
Behavior loop function for big boulder generator

### Lua Example
`bhv_big_boulder_generator_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_big_boulder_generator_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_big_boulder_init](#bhv_big_boulder_init)

### Description
Behavior init function for big boulder

### Lua Example
`bhv_big_boulder_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_big_boulder_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_big_boulder_loop](#bhv_big_boulder_loop)

### Description
Behavior loop function for big boulder

### Lua Example
`bhv_big_boulder_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_big_boulder_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_big_bully_init](#bhv_big_bully_init)

### Description
Behavior init function for Big Bully

### Lua Example
`bhv_big_bully_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_big_bully_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_big_bully_with_minions_init](#bhv_big_bully_with_minions_init)

### Description
Behavior init function for Big Bully with minions

### Lua Example
`bhv_big_bully_with_minions_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_big_bully_with_minions_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_big_bully_with_minions_loop](#bhv_big_bully_with_minions_loop)

### Description
Behavior loop function for Big Bully with minions

### Lua Example
`bhv_big_bully_with_minions_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_big_bully_with_minions_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bird_update](#bhv_bird_update)

### Description
Behavior loop function for bird

### Lua Example
`bhv_bird_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bird_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_birds_sound_loop](#bhv_birds_sound_loop)

### Description
Behavior loop function for birds sound

### Lua Example
`bhv_birds_sound_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_birds_sound_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bitfs_sinking_cage_platform_loop](#bhv_bitfs_sinking_cage_platform_loop)

### Description
Behavior loop function for Bowser in the Fire Sea sinking cage platform

### Lua Example
`bhv_bitfs_sinking_cage_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bitfs_sinking_cage_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bitfs_sinking_platform_loop](#bhv_bitfs_sinking_platform_loop)

### Description
Behavior loop function for Bowser in the Fire Sea sinking platform

### Lua Example
`bhv_bitfs_sinking_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bitfs_sinking_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_black_smoke_bowser_loop](#bhv_black_smoke_bowser_loop)

### Description
Behavior loop function for black smoke Bowser

### Lua Example
`bhv_black_smoke_bowser_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_black_smoke_bowser_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_black_smoke_mario_loop](#bhv_black_smoke_mario_loop)

### Description
Behavior loop function for black smoke Mario

### Lua Example
`bhv_black_smoke_mario_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_black_smoke_mario_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_black_smoke_upward_loop](#bhv_black_smoke_upward_loop)

### Description
Behavior loop function for black smoke upward

### Lua Example
`bhv_black_smoke_upward_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_black_smoke_upward_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_bowser_flame_init](#bhv_blue_bowser_flame_init)

### Description
Behavior init function for Blue Bowser flame

### Lua Example
`bhv_blue_bowser_flame_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_bowser_flame_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_bowser_flame_loop](#bhv_blue_bowser_flame_loop)

### Description
Behavior loop function for Blue Bowser flame

### Lua Example
`bhv_blue_bowser_flame_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_bowser_flame_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_coin_jumping_loop](#bhv_blue_coin_jumping_loop)

### Description
Behavior loop function for Blue Coin jumping

### Lua Example
`bhv_blue_coin_jumping_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_coin_jumping_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_coin_number_loop](#bhv_blue_coin_number_loop)

### Description
Behavior loop function for Blue Coin number

### Lua Example
`bhv_blue_coin_number_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_coin_number_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_coin_sliding_jumping_init](#bhv_blue_coin_sliding_jumping_init)

### Description
Behavior init function for Blue Coin sliding jumping

### Lua Example
`bhv_blue_coin_sliding_jumping_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_coin_sliding_jumping_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_coin_sliding_loop](#bhv_blue_coin_sliding_loop)

### Description
Behavior loop function for Blue Coin sliding

### Lua Example
`bhv_blue_coin_sliding_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_coin_sliding_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_coin_switch_init](#bhv_blue_coin_switch_init)

### Description
Behavior init function for Blue Coin switch

### Lua Example
`bhv_blue_coin_switch_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_coin_switch_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_coin_switch_loop](#bhv_blue_coin_switch_loop)

### Description
Behavior loop function for Blue Coin switch

### Lua Example
`bhv_blue_coin_switch_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_coin_switch_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_fish_movement_loop](#bhv_blue_fish_movement_loop)

### Description
Behavior loop function for blue fish movement

### Lua Example
`bhv_blue_fish_movement_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_fish_movement_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_blue_flames_group_loop](#bhv_blue_flames_group_loop)

### Description
Behavior loop function for blue flames group

### Lua Example
`bhv_blue_flames_group_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_blue_flames_group_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bob_pit_bowling_ball_init](#bhv_bob_pit_bowling_ball_init)

### Description
Behavior init function for Bob-omb Battlefield pit bowling ball

### Lua Example
`bhv_bob_pit_bowling_ball_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bob_pit_bowling_ball_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bob_pit_bowling_ball_loop](#bhv_bob_pit_bowling_ball_loop)

### Description
Behavior loop function for Bob-omb Battlefield pit bowling ball

### Lua Example
`bhv_bob_pit_bowling_ball_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bob_pit_bowling_ball_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_anchor_mario_loop](#bhv_bobomb_anchor_mario_loop)

### Description
Behavior loop function for Bob-omb anchor mario

### Lua Example
`bhv_bobomb_anchor_mario_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_anchor_mario_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_buddy_init](#bhv_bobomb_buddy_init)

### Description
Behavior init function for Bob-omb buddy

### Lua Example
`bhv_bobomb_buddy_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_buddy_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_buddy_loop](#bhv_bobomb_buddy_loop)

### Description
Behavior loop function for Bob-omb buddy

### Lua Example
`bhv_bobomb_buddy_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_buddy_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_bully_death_smoke_init](#bhv_bobomb_bully_death_smoke_init)

### Description
Behavior init function for Bob-omb and Bully death smoke

### Lua Example
`bhv_bobomb_bully_death_smoke_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_bully_death_smoke_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_explosion_bubble_init](#bhv_bobomb_explosion_bubble_init)

### Description
Behavior init function for Bob-omb explosion bubble

### Lua Example
`bhv_bobomb_explosion_bubble_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_explosion_bubble_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_explosion_bubble_loop](#bhv_bobomb_explosion_bubble_loop)

### Description
Behavior loop function for Bob-omb explosion bubble

### Lua Example
`bhv_bobomb_explosion_bubble_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_explosion_bubble_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_fuse_smoke_init](#bhv_bobomb_fuse_smoke_init)

### Description
Behavior init function for Bob-omb fuse smoke

### Lua Example
`bhv_bobomb_fuse_smoke_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_fuse_smoke_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_init](#bhv_bobomb_init)

### Description
Behavior init function for Bob-omb

### Lua Example
`bhv_bobomb_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bobomb_loop](#bhv_bobomb_loop)

### Description
Behavior loop function for Bob-omb

### Lua Example
`bhv_bobomb_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bobomb_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_boss_spawned_bridge_loop](#bhv_boo_boss_spawned_bridge_loop)

### Description
Behavior loop function for Boo boss spawned bridge

### Lua Example
`bhv_boo_boss_spawned_bridge_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_boss_spawned_bridge_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_cage_init](#bhv_boo_cage_init)

### Description
Behavior init function for Boo cage

### Lua Example
`bhv_boo_cage_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_cage_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_cage_loop](#bhv_boo_cage_loop)

### Description
Behavior loop function for Boo cage

### Lua Example
`bhv_boo_cage_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_cage_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_in_castle_loop](#bhv_boo_in_castle_loop)

### Description
Behavior loop function for the Boo inside the Castle

### Lua Example
`bhv_boo_in_castle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_in_castle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_init](#bhv_boo_init)

### Description
Behavior init function for Boo

### Lua Example
`bhv_boo_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_loop](#bhv_boo_loop)

### Description
Behavior loop function for Boo

### Lua Example
`bhv_boo_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_with_cage_init](#bhv_boo_with_cage_init)

### Description
Behavior init function for Boo with cage

### Lua Example
`bhv_boo_with_cage_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_with_cage_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_boo_with_cage_loop](#bhv_boo_with_cage_loop)

### Description
Behavior loop function for Boo with cage

### Lua Example
`bhv_boo_with_cage_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_boo_with_cage_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_book_switch_loop](#bhv_book_switch_loop)

### Description
Behavior loop function for Book switch

### Lua Example
`bhv_book_switch_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_book_switch_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bookend_spawn_loop](#bhv_bookend_spawn_loop)

### Description
Behavior loop function for Bookend spawn

### Lua Example
`bhv_bookend_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bookend_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bouncing_fireball_flame_loop](#bhv_bouncing_fireball_flame_loop)

### Description
Behavior loop function for bouncing fireball flame

### Lua Example
`bhv_bouncing_fireball_flame_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bouncing_fireball_flame_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bouncing_fireball_loop](#bhv_bouncing_fireball_loop)

### Description
Behavior loop function for bouncing fireball

### Lua Example
`bhv_bouncing_fireball_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bouncing_fireball_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowling_ball_init](#bhv_bowling_ball_init)

### Description
Behavior init function for bowling ball

### Lua Example
`bhv_bowling_ball_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowling_ball_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowling_ball_loop](#bhv_bowling_ball_loop)

### Description
Behavior loop function for bowling ball

### Lua Example
`bhv_bowling_ball_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowling_ball_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_body_anchor_init](#bhv_bowser_body_anchor_init)

### Description
Behavior init function for Bowser body anchor

### Lua Example
`bhv_bowser_body_anchor_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_body_anchor_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_body_anchor_loop](#bhv_bowser_body_anchor_loop)

### Description
Behavior loop function for Bowser body anchor

### Lua Example
`bhv_bowser_body_anchor_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_body_anchor_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_bomb_explosion_loop](#bhv_bowser_bomb_explosion_loop)

### Description
Behavior loop function for Bowser bomb explosion

### Lua Example
`bhv_bowser_bomb_explosion_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_bomb_explosion_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_bomb_loop](#bhv_bowser_bomb_loop)

### Description
Behavior loop function for Bowser bomb

### Lua Example
`bhv_bowser_bomb_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_bomb_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_bomb_smoke_loop](#bhv_bowser_bomb_smoke_loop)

### Description
Behavior loop function for Bowser bomb smoke

### Lua Example
`bhv_bowser_bomb_smoke_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_bomb_smoke_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_course_red_coin_star_loop](#bhv_bowser_course_red_coin_star_loop)

### Description
Behavior loop function for Bowser course Red Coin Star

### Lua Example
`bhv_bowser_course_red_coin_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_course_red_coin_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_flame_spawn_loop](#bhv_bowser_flame_spawn_loop)

### Description
Behavior loop function for Bowser flame spawn

### Lua Example
`bhv_bowser_flame_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_flame_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_init](#bhv_bowser_init)

### Description
Behavior init function for Bowser

### Lua Example
`bhv_bowser_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_key_course_exit_loop](#bhv_bowser_key_course_exit_loop)

### Description
Behavior loop function for Bowser key course exit

### Lua Example
`bhv_bowser_key_course_exit_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_key_course_exit_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_key_init](#bhv_bowser_key_init)

### Description
Behavior init function for Bowser key

### Lua Example
`bhv_bowser_key_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_key_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_key_loop](#bhv_bowser_key_loop)

### Description
Behavior loop function for Bowser key

### Lua Example
`bhv_bowser_key_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_key_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_key_unlock_door_loop](#bhv_bowser_key_unlock_door_loop)

### Description
Behavior loop function for Bowser key unlock door

### Lua Example
`bhv_bowser_key_unlock_door_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_key_unlock_door_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_loop](#bhv_bowser_loop)

### Description
Behavior loop function for Bowser

### Lua Example
`bhv_bowser_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_shock_wave_loop](#bhv_bowser_shock_wave_loop)

### Description
Behavior loop function for Bowser shock wave

### Lua Example
`bhv_bowser_shock_wave_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_shock_wave_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_tail_anchor_init](#bhv_bowser_tail_anchor_init)

### Description
Behavior init function for Bowser tail anchor

### Lua Example
`bhv_bowser_tail_anchor_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_tail_anchor_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowser_tail_anchor_loop](#bhv_bowser_tail_anchor_loop)

### Description
Behavior loop function for Bowser tail anchor

### Lua Example
`bhv_bowser_tail_anchor_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowser_tail_anchor_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bowsers_sub_loop](#bhv_bowsers_sub_loop)

### Description
Behavior loop function for Bowser's submarine

### Lua Example
`bhv_bowsers_sub_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bowsers_sub_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_breakable_box_loop](#bhv_breakable_box_loop)

### Description
Behavior loop function for breakable box

### Lua Example
`bhv_breakable_box_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_breakable_box_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_breakable_box_small_init](#bhv_breakable_box_small_init)

### Description
Behavior init function for small breakable box

### Lua Example
`bhv_breakable_box_small_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_breakable_box_small_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_breakable_box_small_loop](#bhv_breakable_box_small_loop)

### Description
Behavior loop function for small breakable box

### Lua Example
`bhv_breakable_box_small_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_breakable_box_small_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bub_loop](#bhv_bub_loop)

### Description
Behavior loop function for Bub

### Lua Example
`bhv_bub_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bub_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bub_spawner_loop](#bhv_bub_spawner_loop)

### Description
Behavior loop function for Bub spawner

### Lua Example
`bhv_bub_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bub_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bubba_loop](#bhv_bubba_loop)

### Description
Behavior loop function for Bubba

### Lua Example
`bhv_bubba_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bubba_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bubble_cannon_barrel_loop](#bhv_bubble_cannon_barrel_loop)

### Description
Behavior loop function for bubble cannon barrel

### Lua Example
`bhv_bubble_cannon_barrel_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bubble_cannon_barrel_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bubble_maybe_loop](#bhv_bubble_maybe_loop)

### Description
Behavior loop function for bubble maybe

### Lua Example
`bhv_bubble_maybe_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bubble_maybe_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bubble_player_loop](#bhv_bubble_player_loop)

### Description
Behavior loop function for bubble player

### Lua Example
`bhv_bubble_player_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bubble_player_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bubble_splash_init](#bhv_bubble_splash_init)

### Description
Behavior init function for bubble splash

### Lua Example
`bhv_bubble_splash_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bubble_splash_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bubble_wave_init](#bhv_bubble_wave_init)

### Description
Behavior init function for bubble wave

### Lua Example
`bhv_bubble_wave_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bubble_wave_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bullet_bill_init](#bhv_bullet_bill_init)

### Description
Behavior init function for Bullet Bill

### Lua Example
`bhv_bullet_bill_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bullet_bill_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bullet_bill_loop](#bhv_bullet_bill_loop)

### Description
Behavior loop function for Bullet Bill

### Lua Example
`bhv_bullet_bill_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bullet_bill_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_bully_loop](#bhv_bully_loop)

### Description
Behavior loop function for Bully

### Lua Example
`bhv_bully_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_bully_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_butterfly_init](#bhv_butterfly_init)

### Description
Behavior init function for Butterfly

### Lua Example
`bhv_butterfly_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_butterfly_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_butterfly_loop](#bhv_butterfly_loop)

### Description
Behavior loop function for Butterfly

### Lua Example
`bhv_butterfly_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_butterfly_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_camera_lakitu_init](#bhv_camera_lakitu_init)

### Description
Behavior init function for Camera Lakitu

### Lua Example
`bhv_camera_lakitu_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_camera_lakitu_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_camera_lakitu_update](#bhv_camera_lakitu_update)

### Description
Behavior loop function for Camera Lakitu

### Lua Example
`bhv_camera_lakitu_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_camera_lakitu_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cannon_barrel_loop](#bhv_cannon_barrel_loop)

### Description
Behavior loop function for cannon barrel

### Lua Example
`bhv_cannon_barrel_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cannon_barrel_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cannon_base_loop](#bhv_cannon_base_loop)

### Description
Behavior loop function for cannon base

### Lua Example
`bhv_cannon_base_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cannon_base_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cannon_base_unused_loop](#bhv_cannon_base_unused_loop)

### Description
Behavior loop function for cannon base unused

### Lua Example
`bhv_cannon_base_unused_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cannon_base_unused_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cannon_closed_init](#bhv_cannon_closed_init)

### Description
Behavior init function for cannon closed

### Lua Example
`bhv_cannon_closed_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cannon_closed_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cannon_closed_loop](#bhv_cannon_closed_loop)

### Description
Behavior loop function for cannon closed

### Lua Example
`bhv_cannon_closed_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cannon_closed_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cap_switch_loop](#bhv_cap_switch_loop)

### Description
Behavior loop function for Cap Switch

### Lua Example
`bhv_cap_switch_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cap_switch_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_castle_cannon_grate_init](#bhv_castle_cannon_grate_init)

### Description
Behavior init function for Castle cannon grate

### Lua Example
`bhv_castle_cannon_grate_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_castle_cannon_grate_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_castle_flag_init](#bhv_castle_flag_init)

### Description
Behavior init function for castle flag

### Lua Example
`bhv_castle_flag_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_castle_flag_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_castle_floor_trap_init](#bhv_castle_floor_trap_init)

### Description
Behavior init function for Bowser in the Dark World floor trap manager

### Lua Example
`bhv_castle_floor_trap_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_castle_floor_trap_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_castle_floor_trap_loop](#bhv_castle_floor_trap_loop)

### Description
Behavior loop function for Bowser in the Dark World floor trap manager

### Lua Example
`bhv_castle_floor_trap_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_castle_floor_trap_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ccm_touched_star_spawn_loop](#bhv_ccm_touched_star_spawn_loop)

### Description
Behavior loop function for Cool, Cool Mountain touched Star spawn

### Lua Example
`bhv_ccm_touched_star_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ccm_touched_star_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_celebration_star_init](#bhv_celebration_star_init)

### Description
Behavior init function for Celebration Star

### Lua Example
`bhv_celebration_star_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_celebration_star_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_celebration_star_loop](#bhv_celebration_star_loop)

### Description
Behavior loop function for Celebration Star

### Lua Example
`bhv_celebration_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_celebration_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_celebration_star_sparkle_loop](#bhv_celebration_star_sparkle_loop)

### Description
Behavior loop function for Celebration Star sparkle

### Lua Example
`bhv_celebration_star_sparkle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_celebration_star_sparkle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_chain_chomp_chain_part_update](#bhv_chain_chomp_chain_part_update)

### Description
Behavior loop function for Chain Chomp chain part

### Lua Example
`bhv_chain_chomp_chain_part_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_chain_chomp_chain_part_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_chain_chomp_gate_init](#bhv_chain_chomp_gate_init)

### Description
Behavior init function for Chain Chomp gate

### Lua Example
`bhv_chain_chomp_gate_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_chain_chomp_gate_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_chain_chomp_gate_update](#bhv_chain_chomp_gate_update)

### Description
Behavior loop function for Chain Chomp gate

### Lua Example
`bhv_chain_chomp_gate_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_chain_chomp_gate_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_chain_chomp_update](#bhv_chain_chomp_update)

### Description
Behavior loop function for Chain Chomp

### Lua Example
`bhv_chain_chomp_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_chain_chomp_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_checkerboard_elevator_group_init](#bhv_checkerboard_elevator_group_init)

### Description
Behavior init function for checkerboard elevator group

### Lua Example
`bhv_checkerboard_elevator_group_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_checkerboard_elevator_group_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_checkerboard_elevator_group_loop](#bhv_checkerboard_elevator_group_loop)

### Description
Behavior loop function for checkerboard elevator group

### Lua Example
`bhv_checkerboard_elevator_group_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_checkerboard_elevator_group_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_checkerboard_platform_init](#bhv_checkerboard_platform_init)

### Description
Behavior init function for checkerboard platform

### Lua Example
`bhv_checkerboard_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_checkerboard_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_checkerboard_platform_loop](#bhv_checkerboard_platform_loop)

### Description
Behavior loop function for checkerboard platform

### Lua Example
`bhv_checkerboard_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_checkerboard_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_chuckya_anchor_mario_loop](#bhv_chuckya_anchor_mario_loop)

### Description
Behavior loop function for Chuckya mario anchor

### Lua Example
`bhv_chuckya_anchor_mario_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_chuckya_anchor_mario_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_chuckya_loop](#bhv_chuckya_loop)

### Description
Behavior loop function for Chuckya

### Lua Example
`bhv_chuckya_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_chuckya_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_circling_amp_init](#bhv_circling_amp_init)

### Description
Behavior init function for Circling Amp

### Lua Example
`bhv_circling_amp_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_circling_amp_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_circling_amp_loop](#bhv_circling_amp_loop)

### Description
Behavior loop function for Circling Amp

### Lua Example
`bhv_circling_amp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_circling_amp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_clam_loop](#bhv_clam_loop)

### Description
Behavior loop function for Clam

### Lua Example
`bhv_clam_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_clam_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cloud_part_update](#bhv_cloud_part_update)

### Description
Behavior loop function for cloud part

### Lua Example
`bhv_cloud_part_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cloud_part_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_cloud_update](#bhv_cloud_update)

### Description
Behavior loop function for cloud

### Lua Example
`bhv_cloud_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_cloud_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coffin_loop](#bhv_coffin_loop)

### Description
Behavior loop function for coffin

### Lua Example
`bhv_coffin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coffin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coffin_spawner_loop](#bhv_coffin_spawner_loop)

### Description
Behavior loop function for coffin spawner

### Lua Example
`bhv_coffin_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coffin_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coin_formation_init](#bhv_coin_formation_init)

### Description
Behavior init function for Coin formation

### Lua Example
`bhv_coin_formation_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coin_formation_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coin_formation_loop](#bhv_coin_formation_loop)

### Description
Behavior loop function for Coin formation

### Lua Example
`bhv_coin_formation_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coin_formation_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coin_formation_spawn_loop](#bhv_coin_formation_spawn_loop)

### Description
Behavior loop function for Coin formation spawn

### Lua Example
`bhv_coin_formation_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coin_formation_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coin_init](#bhv_coin_init)

### Description
Behavior init function for Coin

### Lua Example
`bhv_coin_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coin_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coin_inside_boo_loop](#bhv_coin_inside_boo_loop)

### Description
Behavior loop function for Coin inside Boo

### Lua Example
`bhv_coin_inside_boo_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coin_inside_boo_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coin_loop](#bhv_coin_loop)

### Description
Behavior loop function for Coin

### Lua Example
`bhv_coin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_coin_sparkles_loop](#bhv_coin_sparkles_loop)

### Description
Behavior loop function for Coin sparkles

### Lua Example
`bhv_coin_sparkles_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_coin_sparkles_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_collect_star_init](#bhv_collect_star_init)

### Description
Behavior init function for collectable Star

### Lua Example
`bhv_collect_star_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_collect_star_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_collect_star_loop](#bhv_collect_star_loop)

### Description
Behavior loop function for collectable Star

### Lua Example
`bhv_collect_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_collect_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_controllable_platform_init](#bhv_controllable_platform_init)

### Description
Behavior init function for controllable platform

### Lua Example
`bhv_controllable_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_controllable_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_controllable_platform_loop](#bhv_controllable_platform_loop)

### Description
Behavior loop function for controllable platform

### Lua Example
`bhv_controllable_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_controllable_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_controllable_platform_sub_loop](#bhv_controllable_platform_sub_loop)

### Description
Behavior loop function for controllable sub platform

### Lua Example
`bhv_controllable_platform_sub_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_controllable_platform_sub_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_courtyard_boo_triplet_init](#bhv_courtyard_boo_triplet_init)

### Description
Behavior init function for Courtyard Boo triplet

### Lua Example
`bhv_courtyard_boo_triplet_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_courtyard_boo_triplet_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ddd_moving_pole_loop](#bhv_ddd_moving_pole_loop)

### Description
Behavior loop function for Dire Dire Docks moving pole

### Lua Example
`bhv_ddd_moving_pole_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ddd_moving_pole_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ddd_pole_init](#bhv_ddd_pole_init)

### Description
Behavior init function for Dire Dire Docks pole

### Lua Example
`bhv_ddd_pole_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ddd_pole_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ddd_pole_update](#bhv_ddd_pole_update)

### Description
Behavior loop function for Dire Dire Docks pole

### Lua Example
`bhv_ddd_pole_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ddd_pole_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ddd_warp_loop](#bhv_ddd_warp_loop)

### Description
Behavior loop function for Castle Basement Dire Dire Docks warp collision

### Lua Example
`bhv_ddd_warp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ddd_warp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_decorative_pendulum_init](#bhv_decorative_pendulum_init)

### Description
Behavior init function for decorative pendulum

### Lua Example
`bhv_decorative_pendulum_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_decorative_pendulum_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_decorative_pendulum_loop](#bhv_decorative_pendulum_loop)

### Description
Behavior loop function for decorative pendulum

### Lua Example
`bhv_decorative_pendulum_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_decorative_pendulum_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_donut_platform_spawner_update](#bhv_donut_platform_spawner_update)

### Description
Behavior loop function for donut platform spawner

### Lua Example
`bhv_donut_platform_spawner_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_donut_platform_spawner_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_donut_platform_update](#bhv_donut_platform_update)

### Description
Behavior loop function for donut platform

### Lua Example
`bhv_donut_platform_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_donut_platform_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_door_init](#bhv_door_init)

### Description
Behavior init function for door

### Lua Example
`bhv_door_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_door_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_door_loop](#bhv_door_loop)

### Description
Behavior loop function for door

### Lua Example
`bhv_door_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_door_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_dorrie_update](#bhv_dorrie_update)

### Description
Behavior loop function for Dorrie

### Lua Example
`bhv_dorrie_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_dorrie_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_elevator_init](#bhv_elevator_init)

### Description
Behavior init function for elevator

### Lua Example
`bhv_elevator_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_elevator_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_elevator_loop](#bhv_elevator_loop)

### Description
Behavior loop function for elevator

### Lua Example
`bhv_elevator_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_elevator_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_end_birds_1_loop](#bhv_end_birds_1_loop)

### Description
Behavior loop function for first end birds

### Lua Example
`bhv_end_birds_1_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_end_birds_1_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_end_birds_2_loop](#bhv_end_birds_2_loop)

### Description
Behavior loop function for second end birds

### Lua Example
`bhv_end_birds_2_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_end_birds_2_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_enemy_lakitu_update](#bhv_enemy_lakitu_update)

### Description
Behavior loop function for Enemy Lakitu

### Lua Example
`bhv_enemy_lakitu_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_enemy_lakitu_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_exclamation_box_init](#bhv_exclamation_box_init)

### Description
Behavior init function for Exclamation Box

### Lua Example
`bhv_exclamation_box_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_exclamation_box_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_exclamation_box_loop](#bhv_exclamation_box_loop)

### Description
Behavior loop function for Exclamation Box

### Lua Example
`bhv_exclamation_box_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_exclamation_box_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_explosion_init](#bhv_explosion_init)

### Description
Behavior init function for explosion

### Lua Example
`bhv_explosion_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_explosion_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_explosion_loop](#bhv_explosion_loop)

### Description
Behavior loop function for explosion

### Lua Example
`bhv_explosion_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_explosion_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_eyerok_boss_init](#bhv_eyerok_boss_init)

### Description
Behavior init function for Eyerok boss

### Lua Example
`bhv_eyerok_boss_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_eyerok_boss_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_eyerok_boss_loop](#bhv_eyerok_boss_loop)

### Description
Behavior loop function for Eyerok boss

### Lua Example
`bhv_eyerok_boss_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_eyerok_boss_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_eyerok_hand_loop](#bhv_eyerok_hand_loop)

### Description
Behavior loop function for Eyerok hand

### Lua Example
`bhv_eyerok_hand_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_eyerok_hand_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fading_warp_loop](#bhv_fading_warp_loop)

### Description
Behavior loop function for fading warp

### Lua Example
`bhv_fading_warp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fading_warp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_falling_bowser_platform_loop](#bhv_falling_bowser_platform_loop)

### Description
Behavior loop function for falling Bowser in the Sky arena platform

### Lua Example
`bhv_falling_bowser_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_falling_bowser_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_falling_pillar_hitbox_loop](#bhv_falling_pillar_hitbox_loop)

### Description
Behavior loop function for Jolly Roger Bay falling pillar hitbox

### Lua Example
`bhv_falling_pillar_hitbox_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_falling_pillar_hitbox_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_falling_pillar_init](#bhv_falling_pillar_init)

### Description
Behavior init function for Jolly Roger Bay falling pillar

### Lua Example
`bhv_falling_pillar_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_falling_pillar_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_falling_pillar_loop](#bhv_falling_pillar_loop)

### Description
Behavior loop function for Jolly Roger Bay falling pillar

### Lua Example
`bhv_falling_pillar_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_falling_pillar_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ferris_wheel_axle_init](#bhv_ferris_wheel_axle_init)

### Description
Behavior init function for ferris wheel axle

### Lua Example
`bhv_ferris_wheel_axle_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ferris_wheel_axle_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ferris_wheel_platform_init](#bhv_ferris_wheel_platform_init)

### Description
Behavior init function for ferris wheel platform

### Lua Example
`bhv_ferris_wheel_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ferris_wheel_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ferris_wheel_platform_update](#bhv_ferris_wheel_platform_update)

### Description
Behavior loop function for ferris wheel platform

### Lua Example
`bhv_ferris_wheel_platform_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ferris_wheel_platform_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fire_piranha_plant_init](#bhv_fire_piranha_plant_init)

### Description
Behavior init function for Fire Piranha Plant

### Lua Example
`bhv_fire_piranha_plant_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fire_piranha_plant_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fire_piranha_plant_update](#bhv_fire_piranha_plant_update)

### Description
Behavior loop function for Fire Piranha Plant

### Lua Example
`bhv_fire_piranha_plant_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fire_piranha_plant_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fire_spitter_update](#bhv_fire_spitter_update)

### Description
Behavior loop function for Fire spitter

### Lua Example
`bhv_fire_spitter_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fire_spitter_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fish_group_loop](#bhv_fish_group_loop)

### Description
Behavior loop function for fish group

### Lua Example
`bhv_fish_group_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fish_group_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fish_loop](#bhv_fish_loop)

### Description
Behavior loop function for fish

### Lua Example
`bhv_fish_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fish_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fish_spawner_loop](#bhv_fish_spawner_loop)

### Description
Behavior loop function for fish spawner

### Lua Example
`bhv_fish_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fish_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_bouncing_init](#bhv_flame_bouncing_init)

### Description
Behavior init function for flame bouncing

### Lua Example
`bhv_flame_bouncing_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_bouncing_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_bouncing_loop](#bhv_flame_bouncing_loop)

### Description
Behavior loop function for flame bouncing

### Lua Example
`bhv_flame_bouncing_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_bouncing_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_bowser_init](#bhv_flame_bowser_init)

### Description
Behavior init function for Bowser flame

### Lua Example
`bhv_flame_bowser_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_bowser_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_bowser_loop](#bhv_flame_bowser_loop)

### Description
Behavior loop function for Bowser flame

### Lua Example
`bhv_flame_bowser_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_bowser_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_floating_landing_init](#bhv_flame_floating_landing_init)

### Description
Behavior init function for flame floating landing

### Lua Example
`bhv_flame_floating_landing_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_floating_landing_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_floating_landing_loop](#bhv_flame_floating_landing_loop)

### Description
Behavior loop function for flame floating landing

### Lua Example
`bhv_flame_floating_landing_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_floating_landing_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_large_burning_out_init](#bhv_flame_large_burning_out_init)

### Description
Behavior init function for large flame burning out

### Lua Example
`bhv_flame_large_burning_out_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_large_burning_out_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_mario_loop](#bhv_flame_mario_loop)

### Description
Behavior loop function for flame Mario

### Lua Example
`bhv_flame_mario_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_mario_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_moving_forward_growing_init](#bhv_flame_moving_forward_growing_init)

### Description
Behavior init function for flame moving forward growing

### Lua Example
`bhv_flame_moving_forward_growing_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_moving_forward_growing_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flame_moving_forward_growing_loop](#bhv_flame_moving_forward_growing_loop)

### Description
Behavior loop function for flame moving forward growing

### Lua Example
`bhv_flame_moving_forward_growing_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flame_moving_forward_growing_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flamethrower_flame_loop](#bhv_flamethrower_flame_loop)

### Description
Behavior loop function for flamethrower flame

### Lua Example
`bhv_flamethrower_flame_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flamethrower_flame_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flamethrower_loop](#bhv_flamethrower_loop)

### Description
Behavior loop function for flamethrower

### Lua Example
`bhv_flamethrower_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flamethrower_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_floating_platform_loop](#bhv_floating_platform_loop)

### Description
Behavior loop function for floating platform

### Lua Example
`bhv_floating_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_floating_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_floor_trap_in_castle_loop](#bhv_floor_trap_in_castle_loop)

### Description
Behavior loop function for Bowser in the Dark World floor trap

### Lua Example
`bhv_floor_trap_in_castle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_floor_trap_in_castle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fly_guy_flame_loop](#bhv_fly_guy_flame_loop)

### Description
Behavior loop function for Fly Guy flame

### Lua Example
`bhv_fly_guy_flame_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fly_guy_flame_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_fly_guy_update](#bhv_fly_guy_update)

### Description
Behavior loop function for Fly Guy

### Lua Example
`bhv_fly_guy_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_fly_guy_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_flying_bookend_loop](#bhv_flying_bookend_loop)

### Description
Behavior loop function for flying bookend

### Lua Example
`bhv_flying_bookend_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_flying_bookend_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_free_bowling_ball_init](#bhv_free_bowling_ball_init)

### Description
Behavior init function for free bowling ball

### Lua Example
`bhv_free_bowling_ball_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_free_bowling_ball_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_free_bowling_ball_loop](#bhv_free_bowling_ball_loop)

### Description
Behavior loop function for free bowling ball

### Lua Example
`bhv_free_bowling_ball_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_free_bowling_ball_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_generic_bowling_ball_spawner_init](#bhv_generic_bowling_ball_spawner_init)

### Description
Behavior init function for generic bowling ball spawner

### Lua Example
`bhv_generic_bowling_ball_spawner_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_generic_bowling_ball_spawner_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_generic_bowling_ball_spawner_loop](#bhv_generic_bowling_ball_spawner_loop)

### Description
Behavior loop function for generic bowling ball spawner

### Lua Example
`bhv_generic_bowling_ball_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_generic_bowling_ball_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_giant_pole_loop](#bhv_giant_pole_loop)

### Description
Behavior loop function for giant pole

### Lua Example
`bhv_giant_pole_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_giant_pole_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_golden_coin_sparkles_loop](#bhv_golden_coin_sparkles_loop)

### Description
Behavior loop function for golden Coin sparkles

### Lua Example
`bhv_golden_coin_sparkles_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_golden_coin_sparkles_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_goomba_init](#bhv_goomba_init)

### Description
Behavior init function for Goomba

### Lua Example
`bhv_goomba_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_goomba_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_goomba_triplet_spawner_update](#bhv_goomba_triplet_spawner_update)

### Description
Behavior loop function for Goomba triplet spawner

### Lua Example
`bhv_goomba_triplet_spawner_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_goomba_triplet_spawner_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_goomba_update](#bhv_goomba_update)

### Description
Behavior loop function for Goomba

### Lua Example
`bhv_goomba_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_goomba_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_grand_star_init](#bhv_grand_star_init)

### Description
Behavior init function for Grand Star

### Lua Example
`bhv_grand_star_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_grand_star_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_grand_star_loop](#bhv_grand_star_loop)

### Description
Behavior loop function for Grand Star

### Lua Example
`bhv_grand_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_grand_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_grindel_thwomp_loop](#bhv_grindel_thwomp_loop)

### Description
Behavior loop function for Grindel and Thwomp

### Lua Example
`bhv_grindel_thwomp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_grindel_thwomp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ground_sand_init](#bhv_ground_sand_init)

### Description
Behavior init function for ground sand

### Lua Example
`bhv_ground_sand_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ground_sand_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ground_snow_init](#bhv_ground_snow_init)

### Description
Behavior init function for ground snow

### Lua Example
`bhv_ground_snow_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ground_snow_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_haunted_bookshelf_loop](#bhv_haunted_bookshelf_loop)

### Description
Behavior loop function for Big Boo's Haunt haunted bookshelf

### Lua Example
`bhv_haunted_bookshelf_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_haunted_bookshelf_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_haunted_bookshelf_manager_loop](#bhv_haunted_bookshelf_manager_loop)

### Description
Behavior loop function for haunted bookshelf manager

### Lua Example
`bhv_haunted_bookshelf_manager_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_haunted_bookshelf_manager_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_haunted_chair_init](#bhv_haunted_chair_init)

### Description
Behavior init function for Haunted Chair

### Lua Example
`bhv_haunted_chair_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_haunted_chair_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_haunted_chair_loop](#bhv_haunted_chair_loop)

### Description
Behavior loop function for Haunted Chair

### Lua Example
`bhv_haunted_chair_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_haunted_chair_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_heave_ho_loop](#bhv_heave_ho_loop)

### Description
Behavior loop function for Heave ho

### Lua Example
`bhv_heave_ho_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_heave_ho_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_heave_ho_throw_mario_loop](#bhv_heave_ho_throw_mario_loop)

### Description
Behavior loop function for Heave ho throwing Mario

### Lua Example
`bhv_heave_ho_throw_mario_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_heave_ho_throw_mario_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hidden_blue_coin_loop](#bhv_hidden_blue_coin_loop)

### Description
Behavior loop function for hidden Blue Coin

### Lua Example
`bhv_hidden_blue_coin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hidden_blue_coin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hidden_object_loop](#bhv_hidden_object_loop)

### Description
Behavior loop function for Wet Dry World hidden breakable box

### Lua Example
`bhv_hidden_object_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hidden_object_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hidden_red_coin_star_init](#bhv_hidden_red_coin_star_init)

### Description
Behavior init function for Hidden Red Coin Star

### Lua Example
`bhv_hidden_red_coin_star_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hidden_red_coin_star_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hidden_red_coin_star_loop](#bhv_hidden_red_coin_star_loop)

### Description
Behavior loop function for Hidden Red Coin Star

### Lua Example
`bhv_hidden_red_coin_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hidden_red_coin_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hidden_star_init](#bhv_hidden_star_init)

### Description
Behavior init function for Secret Star

### Lua Example
`bhv_hidden_star_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hidden_star_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hidden_star_loop](#bhv_hidden_star_loop)

### Description
Behavior loop function for Secret Star

### Lua Example
`bhv_hidden_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hidden_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hidden_star_trigger_loop](#bhv_hidden_star_trigger_loop)

### Description
Behavior loop function for Secrets

### Lua Example
`bhv_hidden_star_trigger_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hidden_star_trigger_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_homing_amp_init](#bhv_homing_amp_init)

### Description
Behavior init function for Homing Amp

### Lua Example
`bhv_homing_amp_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_homing_amp_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_homing_amp_loop](#bhv_homing_amp_loop)

### Description
Behavior loop function for Homing Amp

### Lua Example
`bhv_homing_amp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_homing_amp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hoot_init](#bhv_hoot_init)

### Description
Behavior init function for Hoot

### Lua Example
`bhv_hoot_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hoot_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_hoot_loop](#bhv_hoot_loop)

### Description
Behavior loop function for Hoot

### Lua Example
`bhv_hoot_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_hoot_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_horizontal_grindel_init](#bhv_horizontal_grindel_init)

### Description
Behavior init function for horizontal Grindel

### Lua Example
`bhv_horizontal_grindel_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_horizontal_grindel_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_horizontal_grindel_update](#bhv_horizontal_grindel_update)

### Description
Behavior loop function for horizontal Grindel

### Lua Example
`bhv_horizontal_grindel_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_horizontal_grindel_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_idle_water_wave_loop](#bhv_idle_water_wave_loop)

### Description
Behavior loop function for idle water wave

### Lua Example
`bhv_idle_water_wave_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_idle_water_wave_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_init_changing_water_level_loop](#bhv_init_changing_water_level_loop)

### Description
Behavior init function for changing water level, called when Wet Dry World is loaded

### Lua Example
`bhv_init_changing_water_level_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_init_changing_water_level_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_intro_lakitu_loop](#bhv_intro_lakitu_loop)

### Description
Behavior loop function for intro Lakitu

### Lua Example
`bhv_intro_lakitu_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_intro_lakitu_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_intro_peach_loop](#bhv_intro_peach_loop)

### Description
Behavior loop function for intro Peach

### Lua Example
`bhv_intro_peach_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_intro_peach_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_intro_scene_loop](#bhv_intro_scene_loop)

### Description
Behavior loop function for intro scene

### Lua Example
`bhv_intro_scene_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_intro_scene_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_invisible_objects_under_bridge_init](#bhv_invisible_objects_under_bridge_init)

### Description
Behavior init function for invisible objects under the Castle bridge

### Lua Example
`bhv_invisible_objects_under_bridge_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_invisible_objects_under_bridge_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_invisible_objects_under_bridge_loop](#bhv_invisible_objects_under_bridge_loop)

### Description
Behavior loop function for Invisible objects under the Castle bridge

### Lua Example
`bhv_invisible_objects_under_bridge_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_invisible_objects_under_bridge_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_jet_stream_loop](#bhv_jet_stream_loop)

### Description
Behavior loop function for jet stream

### Lua Example
`bhv_jet_stream_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_jet_stream_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_jet_stream_ring_spawner_loop](#bhv_jet_stream_ring_spawner_loop)

### Description
Behavior loop function for jet stream ring spawner

### Lua Example
`bhv_jet_stream_ring_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_jet_stream_ring_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_jet_stream_water_ring_init](#bhv_jet_stream_water_ring_init)

### Description
Behavior init function for jet stream water ring

### Lua Example
`bhv_jet_stream_water_ring_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_jet_stream_water_ring_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_jet_stream_water_ring_loop](#bhv_jet_stream_water_ring_loop)

### Description
Behavior loop function for jet stream water ring

### Lua Example
`bhv_jet_stream_water_ring_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_jet_stream_water_ring_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_jrb_floating_box_loop](#bhv_jrb_floating_box_loop)

### Description
Behavior loop function for Jolly Roger Bay floating box

### Lua Example
`bhv_jrb_floating_box_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_jrb_floating_box_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_jrb_sliding_box_loop](#bhv_jrb_sliding_box_loop)

### Description
Behavior loop function for Jolly Roger Bay sliding box

### Lua Example
`bhv_jrb_sliding_box_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_jrb_sliding_box_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_jumping_box_loop](#bhv_jumping_box_loop)

### Description
Behavior loop function for jumping box

### Lua Example
`bhv_jumping_box_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_jumping_box_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_kickable_board_loop](#bhv_kickable_board_loop)

### Description
Behavior loop function for Whomp's Fortress kickable board

### Lua Example
`bhv_kickable_board_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_kickable_board_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_king_bobomb_loop](#bhv_king_bobomb_loop)

### Description
Behavior loop function for King Bob-omb

### Lua Example
`bhv_king_bobomb_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_king_bobomb_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_klepto_init](#bhv_klepto_init)

### Description
Behavior init function for Klepto

### Lua Example
`bhv_klepto_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_klepto_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_klepto_update](#bhv_klepto_update)

### Description
Behavior loop function for Klepto

### Lua Example
`bhv_klepto_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_klepto_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_koopa_init](#bhv_koopa_init)

### Description
Behavior init function for Koopa

### Lua Example
`bhv_koopa_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_koopa_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_koopa_race_endpoint_update](#bhv_koopa_race_endpoint_update)

### Description
Behavior loop function for Koopa race endpoint

### Lua Example
`bhv_koopa_race_endpoint_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_koopa_race_endpoint_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_koopa_shell_flame_loop](#bhv_koopa_shell_flame_loop)

### Description
Behavior loop function for Koopa Shell flame

### Lua Example
`bhv_koopa_shell_flame_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_koopa_shell_flame_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_koopa_shell_loop](#bhv_koopa_shell_loop)

### Description
Behavior loop function for Koopa Shell

### Lua Example
`bhv_koopa_shell_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_koopa_shell_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_koopa_shell_underwater_loop](#bhv_koopa_shell_underwater_loop)

### Description
Behavior loop function for Koopa Shell underwater

### Lua Example
`bhv_koopa_shell_underwater_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_koopa_shell_underwater_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_koopa_update](#bhv_koopa_update)

### Description
Behavior loop function for Koopa

### Lua Example
`bhv_koopa_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_koopa_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_large_bomp_init](#bhv_large_bomp_init)

### Description
Behavior init function for Large Bomp (Whomp's Fortress moving wall with eyes)

### Lua Example
`bhv_large_bomp_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_large_bomp_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_large_bomp_loop](#bhv_large_bomp_loop)

### Description
Behavior loop function for Large Bomp (Whomp's Fortress moving wall with eyes)

### Lua Example
`bhv_large_bomp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_large_bomp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_bowser_puzzle_loop](#bhv_lll_bowser_puzzle_loop)

### Description
Behavior loop function for Lethal Lava Land bowser puzzle

### Lua Example
`bhv_lll_bowser_puzzle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_bowser_puzzle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_bowser_puzzle_piece_loop](#bhv_lll_bowser_puzzle_piece_loop)

### Description
Behavior loop function for Lethal Lava Land bowser puzzle piece

### Lua Example
`bhv_lll_bowser_puzzle_piece_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_bowser_puzzle_piece_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_drawbridge_loop](#bhv_lll_drawbridge_loop)

### Description
Behavior loop function for Lethal Lava Land drawbridge

### Lua Example
`bhv_lll_drawbridge_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_drawbridge_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_drawbridge_spawner_init](#bhv_lll_drawbridge_spawner_init)

### Description
Behavior init function for Lethal Lava Land drawbridge spawner

### Lua Example
`bhv_lll_drawbridge_spawner_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_drawbridge_spawner_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_drawbridge_spawner_loop](#bhv_lll_drawbridge_spawner_loop)

### Description
Behavior loop function for Lethal Lava Land drawbridge spawner

### Lua Example
`bhv_lll_drawbridge_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_drawbridge_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_floating_wood_bridge_loop](#bhv_lll_floating_wood_bridge_loop)

### Description
Behavior loop function for Lethal Lava Land floating wood bridge

### Lua Example
`bhv_lll_floating_wood_bridge_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_floating_wood_bridge_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_moving_octagonal_mesh_platform_loop](#bhv_lll_moving_octagonal_mesh_platform_loop)

### Description
Behavior loop function for Lethal Lava Land moving octagonal mesh platform

### Lua Example
`bhv_lll_moving_octagonal_mesh_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_moving_octagonal_mesh_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_rolling_log_init](#bhv_lll_rolling_log_init)

### Description
Behavior init function for Lethal Lava Land rolling log

### Lua Example
`bhv_lll_rolling_log_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_rolling_log_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_rotating_block_fire_bars_loop](#bhv_lll_rotating_block_fire_bars_loop)

### Description
Behavior loop function for Lethal Lava Land rotating block fire bars

### Lua Example
`bhv_lll_rotating_block_fire_bars_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_rotating_block_fire_bars_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_rotating_hex_flame_loop](#bhv_lll_rotating_hex_flame_loop)

### Description
Behavior loop function for Lethal Lava Land rotating hex flame

### Lua Example
`bhv_lll_rotating_hex_flame_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_rotating_hex_flame_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_rotating_hexagonal_ring_loop](#bhv_lll_rotating_hexagonal_ring_loop)

### Description
Behavior loop function for Lethal Lava Land rotating hexagonal ring

### Lua Example
`bhv_lll_rotating_hexagonal_ring_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_rotating_hexagonal_ring_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_sinking_rectangular_platform_loop](#bhv_lll_sinking_rectangular_platform_loop)

### Description
Behavior loop function for Lethal Lava Land sinking rectangular platform

### Lua Example
`bhv_lll_sinking_rectangular_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_sinking_rectangular_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_sinking_rock_block_loop](#bhv_lll_sinking_rock_block_loop)

### Description
Behavior loop function for Lethal Lava Land sinking rock block

### Lua Example
`bhv_lll_sinking_rock_block_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_sinking_rock_block_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_sinking_square_platforms_loop](#bhv_lll_sinking_square_platforms_loop)

### Description
Behavior loop function for Lethal Lava Land sinking square platforms

### Lua Example
`bhv_lll_sinking_square_platforms_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_sinking_square_platforms_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_lll_wood_piece_loop](#bhv_lll_wood_piece_loop)

### Description
Behavior loop function for Lethal Lava Land wood piece

### Lua Example
`bhv_lll_wood_piece_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_lll_wood_piece_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mad_piano_update](#bhv_mad_piano_update)

### Description
Behavior loop function for Mad Piano

### Lua Example
`bhv_mad_piano_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mad_piano_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_manta_ray_init](#bhv_manta_ray_init)

### Description
Behavior init function for Manta Ray

### Lua Example
`bhv_manta_ray_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_manta_ray_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_manta_ray_loop](#bhv_manta_ray_loop)

### Description
Behavior loop function for Manta Ray

### Lua Example
`bhv_manta_ray_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_manta_ray_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_manta_ray_water_ring_init](#bhv_manta_ray_water_ring_init)

### Description
Behavior init function for Manta Ray water ring

### Lua Example
`bhv_manta_ray_water_ring_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_manta_ray_water_ring_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_manta_ray_water_ring_loop](#bhv_manta_ray_water_ring_loop)

### Description
Behavior loop function for Manta Ray water ring

### Lua Example
`bhv_manta_ray_water_ring_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_manta_ray_water_ring_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_menu_button_init](#bhv_menu_button_init)

### Description
Behavior init function for File Select button

### Lua Example
`bhv_menu_button_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_menu_button_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_menu_button_loop](#bhv_menu_button_loop)

### Description
Behavior loop function for File Select button

### Lua Example
`bhv_menu_button_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_menu_button_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_menu_button_manager_init](#bhv_menu_button_manager_init)

### Description
Behavior init function for File Select button manager

### Lua Example
`bhv_menu_button_manager_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_menu_button_manager_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_menu_button_manager_loop](#bhv_menu_button_manager_loop)

### Description
Behavior loop function for File Select button manager

### Lua Example
`bhv_menu_button_manager_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_menu_button_manager_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_merry_go_round_boo_manager_loop](#bhv_merry_go_round_boo_manager_loop)

### Description
Behavior loop function for Merry Go Round Boo manager

### Lua Example
`bhv_merry_go_round_boo_manager_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_merry_go_round_boo_manager_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_merry_go_round_loop](#bhv_merry_go_round_loop)

### Description
Behavior loop function for Big Boo's Haunt Merry Go Round

### Lua Example
`bhv_merry_go_round_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_merry_go_round_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_metal_cap_init](#bhv_metal_cap_init)

### Description
Behavior init function for Metal Cap

### Lua Example
`bhv_metal_cap_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_metal_cap_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_metal_cap_loop](#bhv_metal_cap_loop)

### Description
Behavior loop function for Metal Cap

### Lua Example
`bhv_metal_cap_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_metal_cap_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mips_init](#bhv_mips_init)

### Description
Behavior init function for Mips

### Lua Example
`bhv_mips_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mips_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mips_loop](#bhv_mips_loop)

### Description
Behavior loop function for Mips

### Lua Example
`bhv_mips_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mips_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moat_grills_loop](#bhv_moat_grills_loop)

### Description
Behavior loop function for moat grills

### Lua Example
`bhv_moat_grills_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moat_grills_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moneybag_hidden_loop](#bhv_moneybag_hidden_loop)

### Description
Behavior loop function for Moneybag hidden

### Lua Example
`bhv_moneybag_hidden_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moneybag_hidden_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moneybag_init](#bhv_moneybag_init)

### Description
Behavior init function for Moneybag

### Lua Example
`bhv_moneybag_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moneybag_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moneybag_loop](#bhv_moneybag_loop)

### Description
Behavior loop function for Moneybag

### Lua Example
`bhv_moneybag_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moneybag_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_monty_mole_hole_update](#bhv_monty_mole_hole_update)

### Description
Behavior loop function for Monty Mole hole

### Lua Example
`bhv_monty_mole_hole_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_monty_mole_hole_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_monty_mole_init](#bhv_monty_mole_init)

### Description
Behavior init function for Monty Mole

### Lua Example
`bhv_monty_mole_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_monty_mole_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_monty_mole_rock_update](#bhv_monty_mole_rock_update)

### Description
Behavior loop function for Monty Mole rock

### Lua Example
`bhv_monty_mole_rock_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_monty_mole_rock_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_monty_mole_update](#bhv_monty_mole_update)

### Description
Behavior loop function for Monty Mole

### Lua Example
`bhv_monty_mole_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_monty_mole_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moving_blue_coin_init](#bhv_moving_blue_coin_init)

### Description
Behavior init function for moving Blue Coin

### Lua Example
`bhv_moving_blue_coin_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moving_blue_coin_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moving_blue_coin_loop](#bhv_moving_blue_coin_loop)

### Description
Behavior loop function for moving Blue Coin

### Lua Example
`bhv_moving_blue_coin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moving_blue_coin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moving_yellow_coin_init](#bhv_moving_yellow_coin_init)

### Description
Behavior init function for moving Yellow Coin

### Lua Example
`bhv_moving_yellow_coin_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moving_yellow_coin_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_moving_yellow_coin_loop](#bhv_moving_yellow_coin_loop)

### Description
Behavior loop function for moving Yellow Coin

### Lua Example
`bhv_moving_yellow_coin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_moving_yellow_coin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mr_blizzard_init](#bhv_mr_blizzard_init)

### Description
Behavior init function for Mr. Blizzard

### Lua Example
`bhv_mr_blizzard_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mr_blizzard_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mr_blizzard_snowball](#bhv_mr_blizzard_snowball)

### Description
Behavior loop function for Mr. Blizzard's snowball

### Lua Example
`bhv_mr_blizzard_snowball()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mr_blizzard_snowball(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mr_blizzard_update](#bhv_mr_blizzard_update)

### Description
Behavior loop function for Mr. Blizzard

### Lua Example
`bhv_mr_blizzard_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mr_blizzard_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mr_i_body_loop](#bhv_mr_i_body_loop)

### Description
Behavior loop function for Mr. I body

### Lua Example
`bhv_mr_i_body_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mr_i_body_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mr_i_loop](#bhv_mr_i_loop)

### Description
Behavior loop function for Mr. I

### Lua Example
`bhv_mr_i_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mr_i_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_mr_i_particle_loop](#bhv_mr_i_particle_loop)

### Description
Behavior loop function for Mr. I particle

### Lua Example
`bhv_mr_i_particle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_mr_i_particle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_normal_cap_init](#bhv_normal_cap_init)

### Description
Behavior init function for Normal Cap

### Lua Example
`bhv_normal_cap_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_normal_cap_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_normal_cap_loop](#bhv_normal_cap_loop)

### Description
Behavior loop function for Normal Cap

### Lua Example
`bhv_normal_cap_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_normal_cap_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_object_bubble_init](#bhv_object_bubble_init)

### Description
Behavior init function for bubble object

### Lua Example
`bhv_object_bubble_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_object_bubble_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_object_bubble_loop](#bhv_object_bubble_loop)

### Description
Behavior loop function for bubble object

### Lua Example
`bhv_object_bubble_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_object_bubble_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_object_water_wave_init](#bhv_object_water_wave_init)

### Description
Behavior init function for water wave object

### Lua Example
`bhv_object_water_wave_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_object_water_wave_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_object_water_wave_loop](#bhv_object_water_wave_loop)

### Description
Behavior loop function for water wave object

### Lua Example
`bhv_object_water_wave_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_object_water_wave_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_openable_cage_door_loop](#bhv_openable_cage_door_loop)

### Description
Behavior loop function for openable cage door

### Lua Example
`bhv_openable_cage_door_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_openable_cage_door_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_openable_grill_loop](#bhv_openable_grill_loop)

### Description
Behavior loop function for openable grill

### Lua Example
`bhv_openable_grill_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_openable_grill_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_orange_number_init](#bhv_orange_number_init)

### Description
Behavior init function for orange number

### Lua Example
`bhv_orange_number_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_orange_number_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_orange_number_loop](#bhv_orange_number_loop)

### Description
Behavior loop function for orange number

### Lua Example
`bhv_orange_number_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_orange_number_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_particle_init](#bhv_particle_init)

### Description
Behavior init function for particle

### Lua Example
`bhv_particle_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_particle_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_particle_loop](#bhv_particle_loop)

### Description
Behavior loop function for particle

### Lua Example
`bhv_particle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_particle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_penguin_race_finish_line_update](#bhv_penguin_race_finish_line_update)

### Description
Behavior loop function for Penguin race finish line

### Lua Example
`bhv_penguin_race_finish_line_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_penguin_race_finish_line_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_penguin_race_shortcut_check_update](#bhv_penguin_race_shortcut_check_update)

### Description
Behavior loop function for Penguin race shortcut check

### Lua Example
`bhv_penguin_race_shortcut_check_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_penguin_race_shortcut_check_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_piranha_particle_loop](#bhv_piranha_particle_loop)

### Description
Behavior loop function for Piranha particle

### Lua Example
`bhv_piranha_particle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_piranha_particle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_piranha_plant_bubble_loop](#bhv_piranha_plant_bubble_loop)

### Description
Behavior loop function for Piranha Plant bubble

### Lua Example
`bhv_piranha_plant_bubble_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_piranha_plant_bubble_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_piranha_plant_loop](#bhv_piranha_plant_loop)

### Description
Behavior loop function for Piranha Plant

### Lua Example
`bhv_piranha_plant_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_piranha_plant_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_piranha_plant_waking_bubbles_loop](#bhv_piranha_plant_waking_bubbles_loop)

### Description
Behavior loop function for Piranha Plant waking bubbles

### Lua Example
`bhv_piranha_plant_waking_bubbles_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_piranha_plant_waking_bubbles_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_platform_normals_init](#bhv_platform_normals_init)

### Description
Behavior init function for Bowser in the Dark World, Lethal Lava Land, and Bowser in the Fire Sea platform normals

### Lua Example
`bhv_platform_normals_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_platform_normals_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_platform_on_track_init](#bhv_platform_on_track_init)

### Description
Behavior init function for platform on track

### Lua Example
`bhv_platform_on_track_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_platform_on_track_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_platform_on_track_update](#bhv_platform_on_track_update)

### Description
Behavior loop function for platform on track

### Lua Example
`bhv_platform_on_track_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_platform_on_track_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_play_music_track_when_touched_loop](#bhv_play_music_track_when_touched_loop)

### Description
Behavior loop function for playing a jingle when in a 200 unit radius

### Lua Example
`bhv_play_music_track_when_touched_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_play_music_track_when_touched_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_point_light_init](#bhv_point_light_init)

### Description
Behavior init function for the lighting engine point light. Takes the first 3 behavior parameter bytes for RGB color and the last for radius

### Lua Example
`bhv_point_light_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_point_light_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_point_light_loop](#bhv_point_light_loop)

### Description
Behavior loop function for the lighting engine point light

### Lua Example
`bhv_point_light_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_point_light_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pokey_body_part_update](#bhv_pokey_body_part_update)

### Description
Behavior loop function for Pokey body part

### Lua Example
`bhv_pokey_body_part_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pokey_body_part_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pokey_update](#bhv_pokey_update)

### Description
Behavior loop function for Pokey

### Lua Example
`bhv_pokey_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pokey_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pole_base_loop](#bhv_pole_base_loop)

### Description
Behavior loop function for pole base

### Lua Example
`bhv_pole_base_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pole_base_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pole_init](#bhv_pole_init)

### Description
Behavior init function for pole

### Lua Example
`bhv_pole_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pole_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pound_tiny_star_particle_init](#bhv_pound_tiny_star_particle_init)

### Description
Behavior init function for tiny pound star particle

### Lua Example
`bhv_pound_tiny_star_particle_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pound_tiny_star_particle_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pound_tiny_star_particle_loop](#bhv_pound_tiny_star_particle_loop)

### Description
Behavior loop function for tiny pound star particle

### Lua Example
`bhv_pound_tiny_star_particle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pound_tiny_star_particle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pound_white_puffs_init](#bhv_pound_white_puffs_init)

### Description
Behavior init function for pound white puffs

### Lua Example
`bhv_pound_white_puffs_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pound_white_puffs_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_punch_tiny_triangle_init](#bhv_punch_tiny_triangle_init)

### Description
Behavior init function for tiny punch triangle

### Lua Example
`bhv_punch_tiny_triangle_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_punch_tiny_triangle_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_punch_tiny_triangle_loop](#bhv_punch_tiny_triangle_loop)

### Description
Behavior loop function for tiny punch triangle

### Lua Example
`bhv_punch_tiny_triangle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_punch_tiny_triangle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_purple_switch_loop](#bhv_purple_switch_loop)

### Description
Behavior loop function for Purple Switch

### Lua Example
`bhv_purple_switch_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_purple_switch_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pushable_loop](#bhv_pushable_loop)

### Description
Behavior loop function for pushable metal box

### Lua Example
`bhv_pushable_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pushable_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_elevator_init](#bhv_pyramid_elevator_init)

### Description
Behavior init function for Pyramid elevator

### Lua Example
`bhv_pyramid_elevator_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_elevator_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_elevator_loop](#bhv_pyramid_elevator_loop)

### Description
Behavior loop function for Pyramid elevator

### Lua Example
`bhv_pyramid_elevator_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_elevator_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_elevator_trajectory_marker_ball_loop](#bhv_pyramid_elevator_trajectory_marker_ball_loop)

### Description
Behavior loop function for Pyramid elevator trajectory marker ball

### Lua Example
`bhv_pyramid_elevator_trajectory_marker_ball_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_elevator_trajectory_marker_ball_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_pillar_touch_detector_loop](#bhv_pyramid_pillar_touch_detector_loop)

### Description
Behavior loop function for Pyramid pillar touch detector

### Lua Example
`bhv_pyramid_pillar_touch_detector_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_pillar_touch_detector_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_top_fragment_init](#bhv_pyramid_top_fragment_init)

### Description
Behavior init function for Pyramid top fragment

### Lua Example
`bhv_pyramid_top_fragment_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_top_fragment_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_top_fragment_loop](#bhv_pyramid_top_fragment_loop)

### Description
Behavior loop function for Pyramid top fragment

### Lua Example
`bhv_pyramid_top_fragment_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_top_fragment_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_top_init](#bhv_pyramid_top_init)

### Description
Behavior init function for Pyramid top

### Lua Example
`bhv_pyramid_top_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_top_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_pyramid_top_loop](#bhv_pyramid_top_loop)

### Description
Behavior loop function for Pyramid top

### Lua Example
`bhv_pyramid_top_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_pyramid_top_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_racing_penguin_init](#bhv_racing_penguin_init)

### Description
Behavior init function for Racing Penguin

### Lua Example
`bhv_racing_penguin_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_racing_penguin_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_racing_penguin_update](#bhv_racing_penguin_update)

### Description
Behavior loop function for Racing Penguin

### Lua Example
`bhv_racing_penguin_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_racing_penguin_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_recovery_heart_loop](#bhv_recovery_heart_loop)

### Description
Behavior loop function for Recovery Heart

### Lua Example
`bhv_recovery_heart_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_recovery_heart_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_red_coin_init](#bhv_red_coin_init)

### Description
Behavior init function for Red Coin

### Lua Example
`bhv_red_coin_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_red_coin_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_red_coin_loop](#bhv_red_coin_loop)

### Description
Behavior loop function for Red Coin

### Lua Example
`bhv_red_coin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_red_coin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_red_coin_star_marker_init](#bhv_red_coin_star_marker_init)

### Description
Behavior init function for Red Coin Star marker

### Lua Example
`bhv_red_coin_star_marker_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_red_coin_star_marker_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_respawner_loop](#bhv_respawner_loop)

### Description
Behavior loop function for respawner

### Lua Example
`bhv_respawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_respawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rolling_log_loop](#bhv_rolling_log_loop)

### Description
Behavior loop function for rolling log

### Lua Example
`bhv_rolling_log_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rolling_log_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rotating_clock_arm_loop](#bhv_rotating_clock_arm_loop)

### Description
Behavior loop function for rotating clock arm

### Lua Example
`bhv_rotating_clock_arm_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rotating_clock_arm_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rotating_exclamation_box_loop](#bhv_rotating_exclamation_box_loop)

### Description
Behavior loop function for rotating exclamation mark

### Lua Example
`bhv_rotating_exclamation_box_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rotating_exclamation_box_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rotating_octagonal_plat_init](#bhv_rotating_octagonal_plat_init)

### Description
Behavior init function for Rotating octagonal platform in Rainbow Ride and Bowser in the Sky

### Lua Example
`bhv_rotating_octagonal_plat_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rotating_octagonal_plat_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rotating_octagonal_plat_loop](#bhv_rotating_octagonal_plat_loop)

### Description
Behavior loop function for Rotating octagonal platform in Rainbow Ride and Bowser in the Sky

### Lua Example
`bhv_rotating_octagonal_plat_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rotating_octagonal_plat_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rotating_platform_loop](#bhv_rotating_platform_loop)

### Description
Behavior loop function for rotating platform

### Lua Example
`bhv_rotating_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rotating_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rr_cruiser_wing_init](#bhv_rr_cruiser_wing_init)

### Description
Behavior init function for Rainbow Ride cruiser wing

### Lua Example
`bhv_rr_cruiser_wing_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rr_cruiser_wing_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rr_cruiser_wing_loop](#bhv_rr_cruiser_wing_loop)

### Description
Behavior loop function for Rainbow Ride cruiser wing

### Lua Example
`bhv_rr_cruiser_wing_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rr_cruiser_wing_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_rr_rotating_bridge_platform_loop](#bhv_rr_rotating_bridge_platform_loop)

### Description
Behavior loop function for Rainbow Ride rotating bridge platform

### Lua Example
`bhv_rr_rotating_bridge_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_rr_rotating_bridge_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sand_sound_loop](#bhv_sand_sound_loop)

### Description
Behavior loop function for sand sound

### Lua Example
`bhv_sand_sound_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sand_sound_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_scuttlebug_loop](#bhv_scuttlebug_loop)

### Description
Behavior loop function for Scuttlebug

### Lua Example
`bhv_scuttlebug_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_scuttlebug_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_scuttlebug_spawn_loop](#bhv_scuttlebug_spawn_loop)

### Description
Behavior loop function for Scuttlebug spawner

### Lua Example
`bhv_scuttlebug_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_scuttlebug_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_seaweed_bundle_init](#bhv_seaweed_bundle_init)

### Description
Behavior init function for seaweed bundle

### Lua Example
`bhv_seaweed_bundle_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_seaweed_bundle_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_seaweed_init](#bhv_seaweed_init)

### Description
Behavior init function for seaweed

### Lua Example
`bhv_seaweed_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_seaweed_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_seesaw_platform_init](#bhv_seesaw_platform_init)

### Description
Behavior init function for seesaw platform

### Lua Example
`bhv_seesaw_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_seesaw_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_seesaw_platform_update](#bhv_seesaw_platform_update)

### Description
Behavior loop function for seesaw platform

### Lua Example
`bhv_seesaw_platform_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_seesaw_platform_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_shallow_water_splash_init](#bhv_shallow_water_splash_init)

### Description
Behavior init function for shallow water splash

### Lua Example
`bhv_shallow_water_splash_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_shallow_water_splash_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ship_part_3_loop](#bhv_ship_part_3_loop)

### Description
Behavior loop function for Jolly Roger Bay ship part 3

### Lua Example
`bhv_ship_part_3_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ship_part_3_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_skeeter_update](#bhv_skeeter_update)

### Description
Behavior loop function for Skeeter

### Lua Example
`bhv_skeeter_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_skeeter_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_skeeter_wave_update](#bhv_skeeter_wave_update)

### Description
Behavior loop function for Skeeter wave

### Lua Example
`bhv_skeeter_wave_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_skeeter_wave_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sl_snowman_wind_loop](#bhv_sl_snowman_wind_loop)

### Description
Behavior loop function for Snowman's Land snowman wind

### Lua Example
`bhv_sl_snowman_wind_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sl_snowman_wind_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sl_walking_penguin_loop](#bhv_sl_walking_penguin_loop)

### Description
Behavior loop function for Snowman's Land walking penguin

### Lua Example
`bhv_sl_walking_penguin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sl_walking_penguin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sliding_plat_2_init](#bhv_sliding_plat_2_init)

### Description
Behavior init function for sliding platform 2 in Rainbow Ride and Bowser courses

### Lua Example
`bhv_sliding_plat_2_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sliding_plat_2_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sliding_plat_2_loop](#bhv_sliding_plat_2_loop)

### Description
Behavior loop function for sliding platform 2 in Rainbow Ride and Bowser courses

### Lua Example
`bhv_sliding_plat_2_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sliding_plat_2_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sliding_snow_mound_loop](#bhv_sliding_snow_mound_loop)

### Description
Behavior loop function for sliding snow mound

### Lua Example
`bhv_sliding_snow_mound_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sliding_snow_mound_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_small_bomp_init](#bhv_small_bomp_init)

### Description
Behavior init function for Small Bomp (Whomp's Fortress moving wall with eyes)

### Lua Example
`bhv_small_bomp_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_small_bomp_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_small_bomp_loop](#bhv_small_bomp_loop)

### Description
Behavior loop function for Small Bomp (Whomp's Fortress moving wall with eyes)

### Lua Example
`bhv_small_bomp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_small_bomp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_small_bubbles_loop](#bhv_small_bubbles_loop)

### Description
Behavior loop function for small bubbles

### Lua Example
`bhv_small_bubbles_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_small_bubbles_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_small_bully_init](#bhv_small_bully_init)

### Description
Behavior init function for Small Bully

### Lua Example
`bhv_small_bully_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_small_bully_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_small_penguin_loop](#bhv_small_penguin_loop)

### Description
Behavior loop function for small penguin

### Lua Example
`bhv_small_penguin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_small_penguin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_small_piranha_flame_loop](#bhv_small_piranha_flame_loop)

### Description
Behavior loop function for Small Piranha flame

### Lua Example
`bhv_small_piranha_flame_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_small_piranha_flame_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_small_water_wave_loop](#bhv_small_water_wave_loop)

### Description
Behavior loop function for small water wave

### Lua Example
`bhv_small_water_wave_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_small_water_wave_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snow_leaf_particle_spawn_init](#bhv_snow_leaf_particle_spawn_init)

### Description
Behavior init function for snow leaf particle spawn

### Lua Example
`bhv_snow_leaf_particle_spawn_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snow_leaf_particle_spawn_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snow_mound_spawn_loop](#bhv_snow_mound_spawn_loop)

### Description
Behavior loop function for snow mound spawn

### Lua Example
`bhv_snow_mound_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snow_mound_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snowmans_body_checkpoint_loop](#bhv_snowmans_body_checkpoint_loop)

### Description
Behavior loop function for Snowman's body checkpoint

### Lua Example
`bhv_snowmans_body_checkpoint_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snowmans_body_checkpoint_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snowmans_bottom_init](#bhv_snowmans_bottom_init)

### Description
Behavior init function for Snowman's bottom

### Lua Example
`bhv_snowmans_bottom_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snowmans_bottom_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snowmans_bottom_loop](#bhv_snowmans_bottom_loop)

### Description
Behavior loop function for Snowman's bottom

### Lua Example
`bhv_snowmans_bottom_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snowmans_bottom_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snowmans_head_init](#bhv_snowmans_head_init)

### Description
Behavior init function for Snowman's head

### Lua Example
`bhv_snowmans_head_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snowmans_head_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snowmans_head_loop](#bhv_snowmans_head_loop)

### Description
Behavior loop function for Snowman's head

### Lua Example
`bhv_snowmans_head_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snowmans_head_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snufit_balls_loop](#bhv_snufit_balls_loop)

### Description
Behavior loop function for Snufit balls

### Lua Example
`bhv_snufit_balls_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snufit_balls_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_snufit_loop](#bhv_snufit_loop)

### Description
Behavior loop function for Snufit

### Lua Example
`bhv_snufit_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_snufit_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sound_spawner_init](#bhv_sound_spawner_init)

### Description
Behavior init function for sound spawner

### Lua Example
`bhv_sound_spawner_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sound_spawner_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sparkle_spawn_loop](#bhv_sparkle_spawn_loop)

### Description
Behavior loop function for sparkle spawner

### Lua Example
`bhv_sparkle_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sparkle_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_spawn_star_no_level_exit](#bhv_spawn_star_no_level_exit)

### Description
Spawns a Star parented to `object` that won't make Mario exit the level with an ID corresponding to `params`' first byte

### Lua Example
`bhv_spawn_star_no_level_exit(object, params, networkSendEvent)`

### Parameters
| Field | Type |
| ----- | ---- |
| object | [Object](structs.md#Object) |
| params | `integer` |
| networkSendEvent | `integer` |

### Returns
- None

### C Prototype
`void bhv_spawn_star_no_level_exit(struct Object* object, u32 params, u8 networkSendEvent);`

[:arrow_up_small:](#)

<br />

## [bhv_spawned_star_init](#bhv_spawned_star_init)

### Description
Behavior init function for spawned star

### Lua Example
`bhv_spawned_star_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_spawned_star_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_spawned_star_loop](#bhv_spawned_star_loop)

### Description
Behavior loop function for Spawned star

### Lua Example
`bhv_spawned_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_spawned_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_spindel_init](#bhv_spindel_init)

### Description
Behavior init function for Spindel

### Lua Example
`bhv_spindel_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_spindel_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_spindel_loop](#bhv_spindel_loop)

### Description
Behavior loop function for Spindel

### Lua Example
`bhv_spindel_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_spindel_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_spindrift_loop](#bhv_spindrift_loop)

### Description
Behavior loop function for Spindrift

### Lua Example
`bhv_spindrift_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_spindrift_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_spiny_update](#bhv_spiny_update)

### Description
Behavior loop function for Spiny

### Lua Example
`bhv_spiny_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_spiny_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_squarish_path_moving_loop](#bhv_squarish_path_moving_loop)

### Description
Behavior loop function for Bowser in the Dark World squarish path moving

### Lua Example
`bhv_squarish_path_moving_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_squarish_path_moving_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_squarish_path_parent_init](#bhv_squarish_path_parent_init)

### Description
Behavior init function for Bowser in the Dark World squarish path parent

### Lua Example
`bhv_squarish_path_parent_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_squarish_path_parent_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_squarish_path_parent_loop](#bhv_squarish_path_parent_loop)

### Description
Behavior loop function for Bowser in the Dark World Ssuarish path parent

### Lua Example
`bhv_squarish_path_parent_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_squarish_path_parent_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_squishable_platform_loop](#bhv_squishable_platform_loop)

### Description
Behavior loop function for squishable platform

### Lua Example
`bhv_squishable_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_squishable_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ssl_moving_pyramid_wall_init](#bhv_ssl_moving_pyramid_wall_init)

### Description
Behavior init function for Ssl moving pyramid wall

### Lua Example
`bhv_ssl_moving_pyramid_wall_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ssl_moving_pyramid_wall_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ssl_moving_pyramid_wall_loop](#bhv_ssl_moving_pyramid_wall_loop)

### Description
Behavior loop function for Ssl moving pyramid wall

### Lua Example
`bhv_ssl_moving_pyramid_wall_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ssl_moving_pyramid_wall_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_star_door_loop](#bhv_star_door_loop)

### Description
Behavior loop function for Star Door

### Lua Example
`bhv_star_door_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_star_door_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_star_door_loop_2](#bhv_star_door_loop_2)

### Description
Behavior loop function for Star Door

### Lua Example
`bhv_star_door_loop_2()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_star_door_loop_2(void);`

[:arrow_up_small:](#)

<br />

## [bhv_star_key_collection_puff_spawner_loop](#bhv_star_key_collection_puff_spawner_loop)

### Description
Behavior loop function for Star and key collection puff spawner

### Lua Example
`bhv_star_key_collection_puff_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_star_key_collection_puff_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_star_number_loop](#bhv_star_number_loop)

### Description
Behavior loop function for Star number

### Lua Example
`bhv_star_number_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_star_number_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_star_spawn_init](#bhv_star_spawn_init)

### Description
Behavior init function for Star spawn

### Lua Example
`bhv_star_spawn_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_star_spawn_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_star_spawn_loop](#bhv_star_spawn_loop)

### Description
Behavior loop function for Star spawn

### Lua Example
`bhv_star_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_star_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_static_checkered_platform_loop](#bhv_static_checkered_platform_loop)

### Description
Behavior loop function for static checkered platform

### Lua Example
`bhv_static_checkered_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_static_checkered_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_strong_wind_particle_loop](#bhv_strong_wind_particle_loop)

### Description
Behavior loop function for strong wind particle

### Lua Example
`bhv_strong_wind_particle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_strong_wind_particle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sunken_ship_part_loop](#bhv_sunken_ship_part_loop)

### Description
Behavior loop function for Jolly Roger Bay sunken ship part

### Lua Example
`bhv_sunken_ship_part_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sunken_ship_part_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sushi_shark_collision_loop](#bhv_sushi_shark_collision_loop)

### Description
Behavior loop function for Sushi Shark collision

### Lua Example
`bhv_sushi_shark_collision_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sushi_shark_collision_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_sushi_shark_loop](#bhv_sushi_shark_loop)

### Description
Behavior loop function for Sushi Shark

### Lua Example
`bhv_sushi_shark_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_sushi_shark_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_swing_platform_init](#bhv_swing_platform_init)

### Description
Behavior init function for swing platform

### Lua Example
`bhv_swing_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_swing_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_swing_platform_update](#bhv_swing_platform_update)

### Description
Behavior loop function for swing platform

### Lua Example
`bhv_swing_platform_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_swing_platform_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_swoop_update](#bhv_swoop_update)

### Description
Behavior loop function for Swoop

### Lua Example
`bhv_swoop_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_swoop_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tank_fish_group_loop](#bhv_tank_fish_group_loop)

### Description
Behavior loop function for tank fish group

### Lua Example
`bhv_tank_fish_group_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tank_fish_group_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_temp_coin_loop](#bhv_temp_coin_loop)

### Description
Behavior loop function for despawning Coin

### Lua Example
`bhv_temp_coin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_temp_coin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_thi_bowling_ball_spawner_loop](#bhv_thi_bowling_ball_spawner_loop)

### Description
Behavior loop function for Tiny Huge Island bowling ball spawner

### Lua Example
`bhv_thi_bowling_ball_spawner_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_thi_bowling_ball_spawner_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_thi_huge_island_top_loop](#bhv_thi_huge_island_top_loop)

### Description
Behavior loop function for Tiny Huge Island huge island top

### Lua Example
`bhv_thi_huge_island_top_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_thi_huge_island_top_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_thi_tiny_island_top_loop](#bhv_thi_tiny_island_top_loop)

### Description
Behavior loop function for Tiny Huge Island tiny island top

### Lua Example
`bhv_thi_tiny_island_top_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_thi_tiny_island_top_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tilting_bowser_lava_platform_init](#bhv_tilting_bowser_lava_platform_init)

### Description
Behavior init function for tilting Bowser in the Fire Sea arena platform

### Lua Example
`bhv_tilting_bowser_lava_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tilting_bowser_lava_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tilting_inverted_pyramid_loop](#bhv_tilting_inverted_pyramid_loop)

### Description
Behavior loop function for Lethal Lava Land and Bowser in the Fire Sea tilting inverted pyramid

### Lua Example
`bhv_tilting_inverted_pyramid_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tilting_inverted_pyramid_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tiny_star_particles_init](#bhv_tiny_star_particles_init)

### Description
Behavior init function for tiny Star particles

### Lua Example
`bhv_tiny_star_particles_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tiny_star_particles_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tower_door_loop](#bhv_tower_door_loop)

### Description
Behavior loop function for Whomp's Fortress tower door

### Lua Example
`bhv_tower_door_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tower_door_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tower_platform_group_init](#bhv_tower_platform_group_init)

### Description
Behavior init function for Whomp's Fortress tower platform group

### Lua Example
`bhv_tower_platform_group_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tower_platform_group_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tower_platform_group_loop](#bhv_tower_platform_group_loop)

### Description
Behavior loop function for Whomp's Fortress tower platform group

### Lua Example
`bhv_tower_platform_group_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tower_platform_group_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tox_box_loop](#bhv_tox_box_loop)

### Description
Behavior loop function for Tox Box

### Lua Example
`bhv_tox_box_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tox_box_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_track_ball_update](#bhv_track_ball_update)

### Description
Behavior loop function for track ball

### Lua Example
`bhv_track_ball_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_track_ball_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_bottom_init](#bhv_treasure_chest_bottom_init)

### Description
Behavior init function for treasure chest bottom

### Lua Example
`bhv_treasure_chest_bottom_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_bottom_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_bottom_loop](#bhv_treasure_chest_bottom_loop)

### Description
Behavior loop function for treasure chest bottom

### Lua Example
`bhv_treasure_chest_bottom_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_bottom_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_init](#bhv_treasure_chest_init)

### Description
Behavior init function for treasure chest

### Lua Example
`bhv_treasure_chest_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_jrb_init](#bhv_treasure_chest_jrb_init)

### Description
Behavior init function for treasure chest jrb

### Lua Example
`bhv_treasure_chest_jrb_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_jrb_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_jrb_loop](#bhv_treasure_chest_jrb_loop)

### Description
Behavior loop function for treasure chest jrb

### Lua Example
`bhv_treasure_chest_jrb_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_jrb_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_loop](#bhv_treasure_chest_loop)

### Description
Behavior loop function for treasure chest

### Lua Example
`bhv_treasure_chest_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_ship_init](#bhv_treasure_chest_ship_init)

### Description
Behavior init function for treasure chest ship

### Lua Example
`bhv_treasure_chest_ship_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_ship_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_ship_loop](#bhv_treasure_chest_ship_loop)

### Description
Behavior loop function for treasure chest ship

### Lua Example
`bhv_treasure_chest_ship_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_ship_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_treasure_chest_top_loop](#bhv_treasure_chest_top_loop)

### Description
Behavior loop function for treasure chest top

### Lua Example
`bhv_treasure_chest_top_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_treasure_chest_top_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tree_snow_or_leaf_loop](#bhv_tree_snow_or_leaf_loop)

### Description
Behavior loop function for tree snow or leaf particle

### Lua Example
`bhv_tree_snow_or_leaf_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tree_snow_or_leaf_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_triplet_butterfly_update](#bhv_triplet_butterfly_update)

### Description
Behavior loop function for a triplet of butterflies

### Lua Example
`bhv_triplet_butterfly_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_triplet_butterfly_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_2d_rotator_init](#bhv_ttc_2d_rotator_init)

### Description
Behavior init function for Tick Tock Clock 2D rotator

### Lua Example
`bhv_ttc_2d_rotator_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_2d_rotator_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_2d_rotator_update](#bhv_ttc_2d_rotator_update)

### Description
Behavior loop function for Tick Tock Clock 2D rotator

### Lua Example
`bhv_ttc_2d_rotator_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_2d_rotator_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_cog_init](#bhv_ttc_cog_init)

### Description
Behavior init function for Tick Tock Clock cog

### Lua Example
`bhv_ttc_cog_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_cog_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_cog_update](#bhv_ttc_cog_update)

### Description
Behavior loop function for Tick Tock Clock cog

### Lua Example
`bhv_ttc_cog_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_cog_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_elevator_init](#bhv_ttc_elevator_init)

### Description
Behavior init function for Tick Tock Clock elevator

### Lua Example
`bhv_ttc_elevator_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_elevator_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_elevator_update](#bhv_ttc_elevator_update)

### Description
Behavior loop function for Tick Tock Clock elevator

### Lua Example
`bhv_ttc_elevator_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_elevator_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_moving_bar_init](#bhv_ttc_moving_bar_init)

### Description
Behavior init function for Tick Tock Clock moving bar

### Lua Example
`bhv_ttc_moving_bar_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_moving_bar_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_moving_bar_update](#bhv_ttc_moving_bar_update)

### Description
Behavior loop function for Tick Tock Clock moving bar

### Lua Example
`bhv_ttc_moving_bar_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_moving_bar_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_pendulum_init](#bhv_ttc_pendulum_init)

### Description
Behavior init function for Tick Tock Clock pendulum

### Lua Example
`bhv_ttc_pendulum_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_pendulum_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_pendulum_update](#bhv_ttc_pendulum_update)

### Description
Behavior loop function for Tick Tock Clock pendulum

### Lua Example
`bhv_ttc_pendulum_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_pendulum_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_pit_block_init](#bhv_ttc_pit_block_init)

### Description
Behavior init function for Tick Tock Clock pit block

### Lua Example
`bhv_ttc_pit_block_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_pit_block_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_pit_block_update](#bhv_ttc_pit_block_update)

### Description
Behavior loop function for Tick Tock Clock pit block

### Lua Example
`bhv_ttc_pit_block_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_pit_block_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_rotating_solid_init](#bhv_ttc_rotating_solid_init)

### Description
Behavior init function for Tick Tock Clock rotating solid

### Lua Example
`bhv_ttc_rotating_solid_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_rotating_solid_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_rotating_solid_update](#bhv_ttc_rotating_solid_update)

### Description
Behavior loop function for Tick Tock Clock rotating solid

### Lua Example
`bhv_ttc_rotating_solid_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_rotating_solid_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_spinner_update](#bhv_ttc_spinner_update)

### Description
Behavior loop function for Tick Tock Clock spinner

### Lua Example
`bhv_ttc_spinner_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_spinner_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_treadmill_init](#bhv_ttc_treadmill_init)

### Description
Behavior init function for Tick Tock Clock treadmill

### Lua Example
`bhv_ttc_treadmill_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_treadmill_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttc_treadmill_update](#bhv_ttc_treadmill_update)

### Description
Behavior loop function for Tick Tock Clock treadmill

### Lua Example
`bhv_ttc_treadmill_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttc_treadmill_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ttm_rolling_log_init](#bhv_ttm_rolling_log_init)

### Description
Behavior init function for Tall, Tall Mountain rolling log

### Lua Example
`bhv_ttm_rolling_log_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ttm_rolling_log_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tumbling_bridge_loop](#bhv_tumbling_bridge_loop)

### Description
Behavior loop function for tumbling bridge

### Lua Example
`bhv_tumbling_bridge_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tumbling_bridge_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tumbling_bridge_platform_loop](#bhv_tumbling_bridge_platform_loop)

### Description
Behavior loop function for tumbling bridge platform

### Lua Example
`bhv_tumbling_bridge_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tumbling_bridge_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tuxies_mother_loop](#bhv_tuxies_mother_loop)

### Description
Behavior loop function for Tuxie's mother

### Lua Example
`bhv_tuxies_mother_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tuxies_mother_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tweester_loop](#bhv_tweester_loop)

### Description
Behavior loop function for Tweester

### Lua Example
`bhv_tweester_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tweester_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_tweester_sand_particle_loop](#bhv_tweester_sand_particle_loop)

### Description
Behavior loop function for Tweester sand particle

### Lua Example
`bhv_tweester_sand_particle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_tweester_sand_particle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ukiki_cage_loop](#bhv_ukiki_cage_loop)

### Description
Behavior loop function for Ukiki cage

### Lua Example
`bhv_ukiki_cage_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ukiki_cage_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ukiki_cage_star_loop](#bhv_ukiki_cage_star_loop)

### Description
Behavior loop function for Ukiki cage Star

### Lua Example
`bhv_ukiki_cage_star_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ukiki_cage_star_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ukiki_init](#bhv_ukiki_init)

### Description
Behavior init function for Ukiki

### Lua Example
`bhv_ukiki_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ukiki_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_ukiki_loop](#bhv_ukiki_loop)

### Description
Behavior loop function for Ukiki

### Lua Example
`bhv_ukiki_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_ukiki_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_unagi_init](#bhv_unagi_init)

### Description
Behavior init function for Unagi

### Lua Example
`bhv_unagi_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_unagi_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_unagi_loop](#bhv_unagi_loop)

### Description
Behavior loop function for Unagi

### Lua Example
`bhv_unagi_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_unagi_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_unagi_subobject_loop](#bhv_unagi_subobject_loop)

### Description
Behavior loop function for Unagi subobject

### Lua Example
`bhv_unagi_subobject_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_unagi_subobject_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_unused_particle_spawn_loop](#bhv_unused_particle_spawn_loop)

### Description
Behavior loop function for unused particle spawn

### Lua Example
`bhv_unused_particle_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_unused_particle_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_unused_poundable_platform](#bhv_unused_poundable_platform)

### Description
Behavior loop function for unused poundable platform

### Lua Example
`bhv_unused_poundable_platform()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_unused_poundable_platform(void);`

[:arrow_up_small:](#)

<br />

## [bhv_vanish_cap_init](#bhv_vanish_cap_init)

### Description
Behavior init function for Vanish Cap

### Lua Example
`bhv_vanish_cap_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_vanish_cap_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_volcano_flames_loop](#bhv_volcano_flames_loop)

### Description
Behavior loop function for Volcano flames

### Lua Example
`bhv_volcano_flames_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_volcano_flames_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_volcano_sound_loop](#bhv_volcano_sound_loop)

### Description
Behavior loop function for volcano sound

### Lua Example
`bhv_volcano_sound_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_volcano_sound_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_volcano_trap_loop](#bhv_volcano_trap_loop)

### Description
Behavior loop function for volcano trap

### Lua Example
`bhv_volcano_trap_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_volcano_trap_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wall_tiny_star_particle_loop](#bhv_wall_tiny_star_particle_loop)

### Description
Behavior loop function for tiny wall star particle

### Lua Example
`bhv_wall_tiny_star_particle_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wall_tiny_star_particle_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_warp_loop](#bhv_warp_loop)

### Description
Behavior loop function for warp

### Lua Example
`bhv_warp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_warp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_air_bubble_init](#bhv_water_air_bubble_init)

### Description
Behavior init function for water air bubble

### Lua Example
`bhv_water_air_bubble_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_air_bubble_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_air_bubble_loop](#bhv_water_air_bubble_loop)

### Description
Behavior loop function for water air bubble

### Lua Example
`bhv_water_air_bubble_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_air_bubble_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_bomb_cannon_loop](#bhv_water_bomb_cannon_loop)

### Description
Behavior loop function for water bomb cannon

### Lua Example
`bhv_water_bomb_cannon_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_bomb_cannon_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_bomb_shadow_update](#bhv_water_bomb_shadow_update)

### Description
Behavior loop function for water bomb shadow

### Lua Example
`bhv_water_bomb_shadow_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_bomb_shadow_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_bomb_spawner_update](#bhv_water_bomb_spawner_update)

### Description
Behavior loop function for water bomb spawner

### Lua Example
`bhv_water_bomb_spawner_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_bomb_spawner_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_bomb_update](#bhv_water_bomb_update)

### Description
Behavior loop function for water bomb

### Lua Example
`bhv_water_bomb_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_bomb_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_droplet_loop](#bhv_water_droplet_loop)

### Description
Behavior loop function for water droplet

### Lua Example
`bhv_water_droplet_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_droplet_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_droplet_splash_init](#bhv_water_droplet_splash_init)

### Description
Behavior init function for water droplet splash

### Lua Example
`bhv_water_droplet_splash_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_droplet_splash_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_level_diamond_loop](#bhv_water_level_diamond_loop)

### Description
Behavior loop function for Wet Dry World water level diamond

### Lua Example
`bhv_water_level_diamond_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_level_diamond_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_level_pillar_init](#bhv_water_level_pillar_init)

### Description
Behavior init function for Castle Basement water level pillar

### Lua Example
`bhv_water_level_pillar_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_level_pillar_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_level_pillar_loop](#bhv_water_level_pillar_loop)

### Description
Behavior loop function for Castle Basement water level pillar

### Lua Example
`bhv_water_level_pillar_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_level_pillar_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_mist_2_loop](#bhv_water_mist_2_loop)

### Description
Behavior loop function for water mist 2

### Lua Example
`bhv_water_mist_2_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_mist_2_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_mist_loop](#bhv_water_mist_loop)

### Description
Behavior loop function for water mist

### Lua Example
`bhv_water_mist_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_mist_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_mist_spawn_loop](#bhv_water_mist_spawn_loop)

### Description
Behavior loop function for water mist spawn

### Lua Example
`bhv_water_mist_spawn_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_mist_spawn_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_splash_spawn_droplets](#bhv_water_splash_spawn_droplets)

### Description
Behavior init function for spawning water splash droplets

### Lua Example
`bhv_water_splash_spawn_droplets()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_splash_spawn_droplets(void);`

[:arrow_up_small:](#)

<br />

## [bhv_water_waves_init](#bhv_water_waves_init)

### Description
Behavior init function for water waves

### Lua Example
`bhv_water_waves_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_water_waves_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_waterfall_sound_loop](#bhv_waterfall_sound_loop)

### Description
Behavior loop function for waterfall sound

### Lua Example
`bhv_waterfall_sound_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_waterfall_sound_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wave_trail_shrink](#bhv_wave_trail_shrink)

### Description
Behavior loop function for shrinking water trail

### Lua Example
`bhv_wave_trail_shrink()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wave_trail_shrink(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wdw_express_elevator_loop](#bhv_wdw_express_elevator_loop)

### Description
Behavior loop function for Wet Dry World express elevator

### Lua Example
`bhv_wdw_express_elevator_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wdw_express_elevator_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_breakable_wall_loop](#bhv_wf_breakable_wall_loop)

### Description
Behavior loop function for Whomp's Fortress breakable wall

### Lua Example
`bhv_wf_breakable_wall_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_breakable_wall_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_elevator_tower_platform_loop](#bhv_wf_elevator_tower_platform_loop)

### Description
Behavior loop function for Whomp's Fortress elevator tower platform

### Lua Example
`bhv_wf_elevator_tower_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_elevator_tower_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_rotating_wooden_platform_init](#bhv_wf_rotating_wooden_platform_init)

### Description
Behavior init function for Whomp's Fortress rotating wooden platform

### Lua Example
`bhv_wf_rotating_wooden_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_rotating_wooden_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_rotating_wooden_platform_loop](#bhv_wf_rotating_wooden_platform_loop)

### Description
Behavior loop function for Whomp's Fortress rotating wooden platform

### Lua Example
`bhv_wf_rotating_wooden_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_rotating_wooden_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_sliding_platform_init](#bhv_wf_sliding_platform_init)

### Description
Behavior init function for Whomp's Fortress sliding platform

### Lua Example
`bhv_wf_sliding_platform_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_sliding_platform_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_sliding_platform_loop](#bhv_wf_sliding_platform_loop)

### Description
Behavior loop function for Whomp's Fortress sliding platform

### Lua Example
`bhv_wf_sliding_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_sliding_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_sliding_tower_platform_loop](#bhv_wf_sliding_tower_platform_loop)

### Description
Behavior loop function for Whomp's Fortress sliding tower platform

### Lua Example
`bhv_wf_sliding_tower_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_sliding_tower_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wf_solid_tower_platform_loop](#bhv_wf_solid_tower_platform_loop)

### Description
Behavior loop function for Whomp's Fortress solid tower platform

### Lua Example
`bhv_wf_solid_tower_platform_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wf_solid_tower_platform_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_whirlpool_init](#bhv_whirlpool_init)

### Description
Behavior init function for whirlpool

### Lua Example
`bhv_whirlpool_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_whirlpool_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_whirlpool_loop](#bhv_whirlpool_loop)

### Description
Behavior loop function for whirlpool

### Lua Example
`bhv_whirlpool_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_whirlpool_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_white_puff_1_loop](#bhv_white_puff_1_loop)

### Description
Behavior loop function for white puff 1

### Lua Example
`bhv_white_puff_1_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_white_puff_1_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_white_puff_2_loop](#bhv_white_puff_2_loop)

### Description
Behavior loop function for white puff 2

### Lua Example
`bhv_white_puff_2_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_white_puff_2_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_white_puff_exploding_loop](#bhv_white_puff_exploding_loop)

### Description
Behavior loop function for white puff exploding

### Lua Example
`bhv_white_puff_exploding_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_white_puff_exploding_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_white_puff_smoke_init](#bhv_white_puff_smoke_init)

### Description
Behavior init function for White puff smoke

### Lua Example
`bhv_white_puff_smoke_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_white_puff_smoke_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_whomp_loop](#bhv_whomp_loop)

### Description
Behavior loop function for Whomp

### Lua Example
`bhv_whomp_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_whomp_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wiggler_body_part_update](#bhv_wiggler_body_part_update)

### Description
Behavior loop function for Wiggler body part

### Lua Example
`bhv_wiggler_body_part_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wiggler_body_part_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wiggler_update](#bhv_wiggler_update)

### Description
Behavior loop function for Wiggler

### Lua Example
`bhv_wiggler_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wiggler_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wind_loop](#bhv_wind_loop)

### Description
Behavior loop function for wind

### Lua Example
`bhv_wind_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wind_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wing_cap_init](#bhv_wing_cap_init)

### Description
Behavior init function for Wing Cap

### Lua Example
`bhv_wing_cap_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wing_cap_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wing_vanish_cap_loop](#bhv_wing_vanish_cap_loop)

### Description
Behavior loop function for Wing and Vanish caps

### Lua Example
`bhv_wing_vanish_cap_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wing_vanish_cap_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_wooden_post_update](#bhv_wooden_post_update)

### Description
Behavior loop function for ground poundable wooden post

### Lua Example
`bhv_wooden_post_update()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_wooden_post_update(void);`

[:arrow_up_small:](#)

<br />

## [bhv_yellow_coin_init](#bhv_yellow_coin_init)

### Description
Behavior init function for Yellow Coin

### Lua Example
`bhv_yellow_coin_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_yellow_coin_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_yellow_coin_loop](#bhv_yellow_coin_loop)

### Description
Behavior loop function for Yellow Coin

### Lua Example
`bhv_yellow_coin_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_yellow_coin_loop(void);`

[:arrow_up_small:](#)

<br />

## [bhv_yoshi_init](#bhv_yoshi_init)

### Description
Behavior init function for Yoshi

### Lua Example
`bhv_yoshi_init()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_yoshi_init(void);`

[:arrow_up_small:](#)

<br />

## [bhv_yoshi_loop](#bhv_yoshi_loop)

### Description
Behavior loop function for Yoshi

### Lua Example
`bhv_yoshi_loop()`

### Parameters
- None

### Returns
- None

### C Prototype
`void bhv_yoshi_loop(void);`

[:arrow_up_small:](#)

<br />

## [check_if_moving_over_floor](#check_if_moving_over_floor)

### Description
Checks if the current object is moving `a1` units over a floor and within a threshold of `a0`

### Lua Example
`local integerValue = check_if_moving_over_floor(a0, a1)`

### Parameters
| Field | Type |
| ----- | ---- |
| a0 | `number` |
| a1 | `number` |

### Returns
- `integer`

### C Prototype
`s32 check_if_moving_over_floor(f32 a0, f32 a1);`

[:arrow_up_small:](#)

<br />

## [clear_particle_flags](#clear_particle_flags)

### Description
Clears the particle flags of the current object

### Lua Example
`clear_particle_flags(flags)`

### Parameters
| Field | Type |
| ----- | ---- |
| flags | `integer` |

### Returns
- None

### C Prototype
`void clear_particle_flags(u32 flags);`

[:arrow_up_small:](#)

<br />

## [common_anchor_mario_behavior](#common_anchor_mario_behavior)

### Description
Common behavior for when Mario's anchoring when grabbed

### Lua Example
`common_anchor_mario_behavior(sp28, sp2C, sp30)`

### Parameters
| Field | Type |
| ----- | ---- |
| sp28 | `number` |
| sp2C | `number` |
| sp30 | `integer` |

### Returns
- None

### C Prototype
`void common_anchor_mario_behavior(f32 sp28, f32 sp2C, s32 sp30);`

[:arrow_up_small:](#)

<br />

## [cur_obj_spawn_strong_wind_particles](#cur_obj_spawn_strong_wind_particles)

### Description
Spawns strong wind particles relative to the current object

### Lua Example
`cur_obj_spawn_strong_wind_particles(windSpread, scale, relPosX, relPosY, relPosZ)`

### Parameters
| Field | Type |
| ----- | ---- |
| windSpread | `integer` |
| scale | `number` |
| relPosX | `number` |
| relPosY | `number` |
| relPosZ | `number` |

### Returns
- None

### C Prototype
`void cur_obj_spawn_strong_wind_particles(s32 windSpread, f32 scale, f32 relPosX, f32 relPosY, f32 relPosZ);`

[:arrow_up_small:](#)

<br />

## [mario_moving_fast_enough_to_make_piranha_plant_bite](#mario_moving_fast_enough_to_make_piranha_plant_bite)

### Description
Checks if Mario is moving fast enough to make Piranha Plant bite. This one is a mouthful

### Lua Example
`local integerValue = mario_moving_fast_enough_to_make_piranha_plant_bite()`

### Parameters
- None

### Returns
- `integer`

### C Prototype
`s32 mario_moving_fast_enough_to_make_piranha_plant_bite(void);`

[:arrow_up_small:](#)

<br />

## [obj_set_secondary_camera_focus](#obj_set_secondary_camera_focus)

### Description
Sets the secondary camera focus

### Lua Example
`obj_set_secondary_camera_focus()`

### Parameters
- None

### Returns
- None

### C Prototype
`void obj_set_secondary_camera_focus(void);`

[:arrow_up_small:](#)

<br />

## [play_penguin_walking_sound](#play_penguin_walking_sound)

### Description
Plays the penguin walking sound

### Lua Example
`play_penguin_walking_sound(walk)`

### Parameters
| Field | Type |
| ----- | ---- |
| walk | `integer` |

### Returns
- None

### C Prototype
`void play_penguin_walking_sound(s32 walk);`

[:arrow_up_small:](#)

<br />

## [spawn_ambient_light](#spawn_ambient_light)

### Description
Spawns a lighting engine point light

### Lua Example
`local ObjectValue = spawn_ambient_light(x, y, z, r, g, b)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| r | `integer` |
| g | `integer` |
| b | `integer` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_ambient_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b);`

[:arrow_up_small:](#)

<br />

## [spawn_default_star](#spawn_default_star)

### Description
Spawns a Star with an ID corresponding to the current object's first behavior parameter byte

### Lua Example
`local ObjectValue = spawn_default_star(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_default_star(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [spawn_mist_from_global](#spawn_mist_from_global)

### Description
Spawns mist particles around the current object

### Lua Example
`spawn_mist_from_global()`

### Parameters
- None

### Returns
- None

### C Prototype
`void spawn_mist_from_global(void);`

[:arrow_up_small:](#)

<br />

## [spawn_mist_particles_variable](#spawn_mist_particles_variable)

### Description
Spawns mist particles around the current object

### Lua Example
`spawn_mist_particles_variable(count, offsetY, size)`

### Parameters
| Field | Type |
| ----- | ---- |
| count | `integer` |
| offsetY | `integer` |
| size | `number` |

### Returns
- None

### C Prototype
`void spawn_mist_particles_variable(s32 count, s32 offsetY, f32 size);`

[:arrow_up_small:](#)

<br />

## [spawn_no_exit_star](#spawn_no_exit_star)

### Description
Spawns a Star that won't make Mario exit the level with an ID corresponding to the current object's first behavior parameter byte

### Lua Example
`local ObjectValue = spawn_no_exit_star(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_no_exit_star(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [spawn_point_light](#spawn_point_light)

### Description
Spawns a lighting engine ambient light

### Lua Example
`local ObjectValue = spawn_point_light(x, y, z, r, g, b, radius)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |
| r | `integer` |
| g | `integer` |
| b | `integer` |
| radius | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_point_light(f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, f32 radius);`

[:arrow_up_small:](#)

<br />

## [spawn_red_coin_cutscene_star](#spawn_red_coin_cutscene_star)

### Description
Spawns a Red Coin cutscene star with an ID corresponding to the current object's first behavior parameter byte

### Lua Example
`local ObjectValue = spawn_red_coin_cutscene_star(x, y, z)`

### Parameters
| Field | Type |
| ----- | ---- |
| x | `number` |
| y | `number` |
| z | `number` |

### Returns
[Object](structs.md#Object)

### C Prototype
`struct Object* spawn_red_coin_cutscene_star(f32 x, f32 y, f32 z);`

[:arrow_up_small:](#)

<br />

## [spawn_star_number](#spawn_star_number)

### Description
Spawns a star number

### Lua Example
`spawn_star_number()`

### Parameters
- None

### Returns
- None

### C Prototype
`void spawn_star_number(void);`

[:arrow_up_small:](#)

<br />

## [spawn_triangle_break_particles](#spawn_triangle_break_particles)

### Description
Spawns triangle break particles around the current object

### Lua Example
`spawn_triangle_break_particles(numTris, triModel, triSize, triAnimState)`

### Parameters
| Field | Type |
| ----- | ---- |
| numTris | `integer` |
| triModel | `integer` |
| triSize | `number` |
| triAnimState | `integer` |

### Returns
- None

### C Prototype
`void spawn_triangle_break_particles(s16 numTris, s16 triModel, f32 triSize, s16 triAnimState);`

[:arrow_up_small:](#)

<br />

## [spawn_wind_particles](#spawn_wind_particles)

### Description
Spawns wind particles around the current object

### Lua Example
`spawn_wind_particles(pitch, yaw)`

### Parameters
| Field | Type |
| ----- | ---- |
| pitch | `integer` |
| yaw | `integer` |

### Returns
- None

### C Prototype
`void spawn_wind_particles(s16 pitch, s16 yaw);`

[:arrow_up_small:](#)

<br />

## [tox_box_move](#tox_box_move)

### Description
Moves Tox Box

### Lua Example
`tox_box_move(forwardVel, a1, deltaPitch, deltaRoll)`

### Parameters
| Field | Type |
| ----- | ---- |
| forwardVel | `number` |
| a1 | `number` |
| deltaPitch | `integer` |
| deltaRoll | `integer` |

### Returns
- None

### C Prototype
`void tox_box_move(f32 forwardVel, f32 a1, s16 deltaPitch, s16 deltaRoll);`

[:arrow_up_small:](#)

<br />

## [update_angle_from_move_flags](#update_angle_from_move_flags)

### Description
Updates the current object's angle from its move flags

### Lua Example
`local integerValue = update_angle_from_move_flags(angle)`

### Parameters
| Field | Type |
| ----- | ---- |
| angle | `Pointer` <`integer`> |

### Returns
- `integer`

### C Prototype
`s32 update_angle_from_move_flags(s32 *angle);`

[:arrow_up_small:](#)

<br />

## [uv_update_scroll](#uv_update_scroll)

### Description
Behavior loop function for UV texture scrolling

### Lua Example
`uv_update_scroll()`

### Parameters
- None

### Returns
- None

### C Prototype
`void uv_update_scroll(void);`

[:arrow_up_small:](#)

<br />

## [vec3f_copy_2](#vec3f_copy_2)

### Description
Duplicate of vec3f_copy except without bad return

### Lua Example
`vec3f_copy_2(dest, src)`

### Parameters
| Field | Type |
| ----- | ---- |
| dest | [Vec3f](structs.md#Vec3f) |
| src | [Vec3f](structs.md#Vec3f) |

### Returns
- None

### C Prototype
`void vec3f_copy_2(Vec3f dest, Vec3f src);`

[:arrow_up_small:](#)

<br />
---

[< prev](functions.md) | [1](functions.md) | 2 | [3](functions-3.md) | [4](functions-4.md) | [5](functions-5.md) | [6](functions-6.md) | [next >](functions-3.md)]

