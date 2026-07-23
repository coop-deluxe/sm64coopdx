## [:rewind: Lua Reference](../lua.md)

# ModFS

`ModFS` enables a small, sandboxed file system for mods. It allows to store and retrieve binary and text files, no matter their content.<br>
Each mod has its own file system, and can allow other mods to read its files.

<br>

## Specs

### File system

Each ModFS file system:
- Has a maximum size of **128 MB** (`MOD_FS_MAX_SIZE`). Files can be any size, as long as the cumulative sum of file sizes doesn't exceed this limit.
- Can store at most **1024 files** (`MOD_FS_MAX_FILES`).
- Is stored on disk as a `.modfs` file, which is a ZIP file, containing all files written in it.

The ModFS files are located in the `sav` directory at the usual save file location:
- Windows: `%appdata%/sm64coopdx`
- Linux: `~/.local/share/sm64coopdx`
- MacOS: `~/Library/Application Support/sm64coopdx`

### Files

- The maximum filepath length is **256 characters** (`MOD_FS_MAX_PATH`), including the NUL terminator.
- Filepaths have the following restrictions:
  - Cannot start or end with whitespaces or slashes `/`, and cannot have two or more consecutive slashes `/`
  - Can contain only valid ASCII characters, no `*` or `\`
  - Cannot be called `properties.json` (this name is reserved for ModFS internal properties)
  - Only the following extensions (and extension-less files) are allowed:
    - text: `.txt`, `.json`, `.ini`, `.sav`
    - actors: `.bin`, `.col`
    - behaviors: `.bhv`
    - textures: `.tex`, `.png`
    - levels: `.lvl`
    - audio: `.m64`, `.aiff`, `.mp3`, `.ogg`

<br>

## [`ModFs`](../structs.md#ModFs)

The object holding the file system of the mod.

### Fields

All fields are immutable.

| Name | Type |
| ----- | ---- |
| mod | [Mod](../structs.md#Mod) |
| modPath | `string` |
| numFiles | `integer` |
| totalSize | `integer` |
| isPublic | `boolean` |

Fields can be accessed in Lua with the dot `.` character:
```lua
print("The ModFS " .. modFs.modPath .. " contains " .. modFs.numFiles .. " files.")
```

### Methods

| Name | Reference |
| ---- | --------- |
| get_filename | [`mod_fs_get_filename`](../functions-5.md#mod_fs_get_filename) |
| get_file | [`mod_fs_get_file`](../functions-5.md#mod_fs_get_file) |
| create_file | [`mod_fs_create_file`](../functions-5.md#mod_fs_create_file) |
| move_file | [`mod_fs_move_file`](../functions-5.md#mod_fs_move_file) |
| copy_file | [`mod_fs_copy_file`](../functions-5.md#mod_fs_copy_file) |
| delete_file | [`mod_fs_delete_file`](../functions-5.md#mod_fs_delete_file) |
| clear | [`mod_fs_clear`](../functions-5.md#mod_fs_clear) |
| save | [`mod_fs_save`](../functions-5.md#mod_fs_save) |
| delete | [`mod_fs_delete`](../functions-5.md#mod_fs_delete) |
| set_public | [`mod_fs_set_public`](../functions-5.md#mod_fs_set_public) |

Methods can be called in Lua with the colon `:` character:
```lua
print("The first file of ModFS " .. modFs.modPath .. " is named " .. modFs:get_filename(0) .. ".")
```

<br>

## [`ModFsFile`](../structs.md#ModFsFile)

A handle to a ModFS file.

### Fields

All fields are immutable.

| Field | Type |
| ----- | ---- |
| modFs | [ModFs](../structs.md#ModFs) |
| filepath | `string` |
| size | `integer` |
| offset | `integer` |
| isText | `boolean` |
| isPublic | `boolean` |

Fields can be accessed in Lua with the dot `.` character:
```lua
print("The ModFS file " .. file.filepath .. " is " .. file.size .. " bytes long.")
```

### Methods

| Name | Reference |
| ---- | --------- |
| read_bool | [`mod_fs_file_read_bool`](../functions-5.md#mod_fs_file_read_bool) |
| read_integer | [`mod_fs_file_read_integer`](../functions-5.md#mod_fs_file_read_integer) |
| read_number | [`mod_fs_file_read_number`](../functions-5.md#mod_fs_file_read_number) |
| read_bytes | [`mod_fs_file_read_bytes`](../functions-5.md#mod_fs_file_read_bytes) |
| read_string | [`mod_fs_file_read_string`](../functions-5.md#mod_fs_file_read_string) |
| read_line | [`mod_fs_file_read_line`](../functions-5.md#mod_fs_file_read_line) |
| write_bool | [`mod_fs_file_write_bool`](../functions-5.md#mod_fs_file_write_bool) |
| write_integer | [`mod_fs_file_write_integer`](../functions-5.md#mod_fs_file_write_integer) |
| write_number | [`mod_fs_file_write_number`](../functions-5.md#mod_fs_file_write_number) |
| write_bytes | [`mod_fs_file_write_bytes`](../functions-5.md#mod_fs_file_write_bytes) |
| write_string | [`mod_fs_file_write_string`](../functions-5.md#mod_fs_file_write_string) |
| write_line | [`mod_fs_file_write_line`](../functions-5.md#mod_fs_file_write_line) |
| seek | [`mod_fs_file_seek`](../functions-5.md#mod_fs_file_seek) |
| rewind | [`mod_fs_file_rewind`](../functions-5.md#mod_fs_file_rewind) |
| is_eof | [`mod_fs_file_is_eof`](../functions-5.md#mod_fs_file_is_eof) |
| fill | [`mod_fs_file_fill`](../functions-5.md#mod_fs_file_fill) |
| erase | [`mod_fs_file_erase`](../functions-5.md#mod_fs_file_erase) |
| set_text_mode | [`mod_fs_file_set_text_mode`](../functions-5.md#mod_fs_file_set_text_mode) |
| set_public | [`mod_fs_file_set_public`](../functions-5.md#mod_fs_file_set_public) |
| set_compression | [`mod_fs_file_set_compression`](../functions-5.md#mod_fs_file_set_compression) |

Methods can be called in Lua with the colon `:` character:
```lua
file:erase(file.size)
print("The ModFS file " .. file.filepath .. " is now empty.")
```

<br>

## Error handling

All errors coming from ModFS functions are not blocking. However, they appear in the console and raise the "Mod has script errors" message.

- The function [`mod_fs_hide_errors`](../functions-5.md#mod_fs_hide_errors) can suppress the ModFS errors from the console.
- Use the function [`mod_fs_get_last_error_code`](../functions-5.md#mod_fs_get_last_error_code) to retrieve the last error code raised by ModFS. This function always return an error code if an error occurred, even if errors are hidden.
- Use the function [`mod_fs_get_last_error`](../functions-5.md#mod_fs_get_last_error) to retrieve the last error raised by ModFS. This function always return an error message if an error occurred, even if errors are hidden.

<br>

## Usage with other sm64coopdx features

One of the strengths of this feature is its interactions with other existing features of sm64coopdx:
- Load models with `smlua_model_util_get_id`
- Load textures with `get_texture_info`
- Load collisions with `smlua_collision_util_get`
- Load sequences with `smlua_audio_utils_replace_sequence`
- Load audio streams with `audio_stream_load`
- Load audio samples with `audio_sample_load`

These functions can take a **ModFS URI** as argument instead of a resource name.<br>
Generate a ModFS URI from a `ModFs` object with the following code:
```lua
local uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "<filepath>")
```

Here are some examples:

```lua
-- Models
local custom_geo_uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "custom_geo.bin")
local E_MODEL_CUSTOM = smlua_model_util_get_id(custom_geo_uri)

-- Textures (both PNG and TEX)
local texture_png_uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "texture.png")
local TEXTURE_PNG = get_texture_info(texture_png_uri)
local texture_tex_uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "texture.tex")
local TEXTURE_TEX = get_texture_info(texture_tex_uri)

-- Collisions
local custom_col_uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "custom_col.col")
local COL_CUSTOM = smlua_collision_util_get(custom_col_uri)

-- Sequences
local custom_m64_uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "custom.m64")
smlua_audio_utils_replace_sequence(SEQ_LEVEL_GRASS, 0x11, 0x80, custom_m64_uri)

-- Streams
local custom_stream_uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "custom_stream.mp3")
local custom_stream = audio_stream_load(custom_stream_uri)

-- Samples
local custom_sample_uri = string.format(MOD_FS_URI_FORMAT, modFs.modPath, "custom_sample.mp3")
local custom_sample = audio_sample_load(custom_sample_uri)
```

<br>

## Good practices

### Always valid `ModFs` object

Use the following piece of code to always retrieve a valid `ModFs` object:
```lua
local modFs = mod_fs_get() or mod_fs_create()
```
If the ModFS for the current mod doesn't exist, it will create one.

<br>

### Always valid `ModFsFile` object

Use the following piece of code to always retrieve a valid `ModFsFile` object:
```lua
local file = modFs:get_file("myfile.txt") or modFs:create_file("myfile.txt", true)
```
Like previously, if the file doesn't exist, it will create one.<br>

To make sure the file is empty when requested, add the following line to clear the existing file content.
```lua
file:erase(file.size)
```

<br>

### Correctly initialize a file

The `get_file` method of a `ModFs` object opens a file only if the file is not loaded yet. Subsequent calls with the same filename will return the file handle without resetting its offset or mode.<br>
For example, one function could write to a file while another could read from the same file, so it's better to set the appropriate file offset and mode when it's needed before starting reading/writing:
```lua
local file = modFs:get_file("myfile.txt")
file:set_text_mode(true) -- Set mode to text
file:rewind() -- Reset offset to the beginning of the file
```

<br>

### Methods over functions

Always use `ModFs` and `ModFsFile` objects methods over regular functions.<br>
It's more clear that way and helps to reduce errors:
```lua
-- Don't
local file = mod_fs_create_file(modFs, "myfile.txt", true)

-- Do
local file = modFs:create_file("myfile.txt", true)
```
```lua
-- Don't
mod_fs_file_write_string(file, "some text")

-- Do
file:write_string("some text")
```

<br>

### Handle possible failures

In addition to error messages that can be retrieved with [`mod_fs_get_last_error`](../functions-5.md#mod_fs_get_last_error), all ModFS functions return an error code as second return value. The error code can be one of the following:

|Error code|Description|
|-|-|
|`MOD_FS_ERR_ALLOC_FAILED`|Memory allocation failed|
|`MOD_FS_ERR_ALREADY_EXISTS`|Tried to create, move or copy an existing ModFS or ModFS file|
|`MOD_FS_ERR_NOT_FOUND`|Tried to move, copy or delete a non-existent ModFS file|
|`MOD_FS_ERR_INVALID_POINTER`|Passed an invalid ModFS or ModFS file pointer|
|`MOD_FS_ERR_INVALID_PARAMETER`|Passed an invalid parameter value|
|`MOD_FS_ERR_FILE_INVALID_INDEX`|Tried to get the filename of an out-of-bounds file index|
|`MOD_FS_ERR_FILE_TYPE_NOT_ALLOWED`|Tried to use a read/write function on a non-supported file type|
|`MOD_FS_ERR_TOTAL_SIZE_EXCEEDED`|Tried to read, copy or write past the maximum size of a ModFS|
|`MOD_FS_ERR_NUM_FILES_EXCEEDED`|Tried to read or create more files than allowed for a ModFS|
|`MOD_FS_ERR_FILEPATH_EMPTY`|Empty filepath|
|`MOD_FS_ERR_FILEPATH_LEN_EXCEEDED`|Filepath too long|
|`MOD_FS_ERR_FILEPATH_RESERVED`|Filepath is reserved and cannot be used for ModFS files|
|`MOD_FS_ERR_FILEPATH_INVALID_CHAR`|Filepath contains invalid characters (non-ASCII, control characters, asterisk or backslash)|
|`MOD_FS_ERR_FILEPATH_MALFORMED`|Filepath is malformed (leading/trailing whitespaces/slashes, consecutive slashes)|
|`MOD_FS_ERR_FILEPATH_INVALID_EXTENSION`|Filepath extension is not in whitelist|
|`MOD_FS_ERR_READ_INVALID_MODPATH`|Modpath couldn't be resolved|
|`MOD_FS_ERR_READ_ZIP`|ZIP decompression failed|
|`MOD_FS_ERR_READ_PROPERTIES`|Properties file JSON is malformed|
|`MOD_FS_ERR_READ_FILE_TRUNCATED`|Read data didn't match the expected size|
|`MOD_FS_ERR_READ_EOF`|Reached end of file while reading|
|`MOD_FS_ERR_WRITE_ZIP`|ZIP compression failed|
|`MOD_FS_ERR_WRITE_NOT_ACTIVE_MOD`|Tried to perform a write operation (create, delete, move, copy, write, set) on another mod ModFS or ModFS file|

Along with the return value of the function, use this error code to handle errors properly:
```lua
local ok, err = modFs:delete_file("somefile")
if not ok then
    print(err, mod_fs_get_last_error())
    if err == MOD_FS_ERR_WRITE_NOT_ACTIVE_MOD then
        print("Do not delete other mods ModFS files!")
    end
end
```

<br>

### Don't forget to save

ModFS are not saved automatically when writing to files.<br>
The mod has to explicitly call the method `save` to save its ModFS on the disk.
```lua
modFs:save()
```

<br>

## Compression

ModFS files can each have their compression level explicitly set. By default this is set to 1 for minimal compression.<br>
Although it makes no difference to the total size limit, changing the compression level can be useful if you are trying to optimize for CPU time.<br>
The compression level can be any integer between 0-9.<br>
```lua
file:set_compression(MOD_FS_COMPRESSION_MIN) -- no compression, good for small data that changes frequently

file:set_compression(MOD_FS_COMPRESSION_MAX) -- max compression, good for large data that is read infrequently
```