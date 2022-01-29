void set_swimming_at_surface_particles(struct MarioState *m, u32 particleFlag);
u32 perform_water_step(struct MarioState *m);
u32 perform_water_full_step(struct MarioState *m, Vec3f nextPos);
s32 mario_execute_submerged_action(struct MarioState *m);
void float_surface_gfx(struct MarioState *m);
void apply_water_current(struct MarioState *m, Vec3f step);
