# C Reference

If you haven't, please read up on [contributing](../../CONTRIBUTING.md)!

## Sections

- [SMLua](sections/smlua.md)
- [Config File](sections/configfile.md)
- [DJUI](sections/djui.md)
- [Languages](sections/lang.md)
- [Growing Arrays](sections/growing_arrays.md)

## Code Format and Conventions

This is the coding format, conventions, and style we use:

- Variable names should use `camelCase`
- Function names should use `snake_case`
- Struct names should use `PascalCase`
- Enum names should use `PascalCase`, with the constants inside the enum being `SCREAMING_SNAKE_CASE`
- Macros are `SCREAMING_SNAKE_CASE`
- Filenames should use `snake_case`
- Global variables, or variables that can be accessed in any file, should be prefixed with a `g` (i.e. `gGlobalTimer`)
- Static variables should be prefixed with an `s` (i.e. `sOverrideCameraCollision`)
- For creating a pointer, `type *value;` is the proper convention, not `type* value;`
- For casting to a pointer, use `(type *)value`, not `(type*)value` or `(type *) value`
- In a header file, use `#pragma once` rather than `#ifndef`/`#define` guard blocks
- Function arguments should always be specified. If empty, use `void`. As an example, use `void allocate_item(void)` instead of `void allocate_item()`
- The brace style is 1TBS (One True Brace Style)
- Indentation is 4 spaces
- Use the `const` keyword for immutable data as much as possible. For example, do not use a `char *` for a read-only string, use `const char *`.
- Use ultratypes (`u8`, `u16`, `u32`, `u64`, `s8`, `s16`, `s32`, `s64`) everywhere you can, you can include it to a file by adding `#include "types.h"` to the top of your file
- For `.c` files, use a corresponding `.h` file, and have it next to the `.c` file
- For `.cpp` files, use a corresponding `.hpp` file, not a `.h` file, and have it next to the `.cpp` file
- Headers in isolation should use `.inl`

You will see many of these rules not followed in the codebase, simply ignore them and follow these rules for all your changes.
