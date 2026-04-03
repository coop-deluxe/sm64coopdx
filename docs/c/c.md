# C Reference

## Naming Convention

- Variable names should use `camelCase`
- Function names should use `snake_case`
- Struct names should use `PascalCase`
- Filenames should use `snake_case`
- Global variables, or variables that can be accessed in any file, should be prefixed with a `g` (i.e. `gGlobalTimer`)
- Static variables, or variables that are only accessed in a single file, should be prefixed with an `s` (i.e. `sOverrideCameraCollision`)
- For creating a pointer, `Type *value;` is the proper convention, not `Type* value;`.

## Sections
- [SMLua](sections/smlua.md)
- [Config File](sections/configfile.md)
- [DJUI](sections/djui.md)