## [:rewind: C Reference](../c.md)

# Languages

Languages are stored in the `lang` folder. Each language is a `.ini` file containing sections. Each of these sections has a entry for a string.

## Usage in C

You can access a language entry in C by using the `DLANG` macro, which is defined in `djui_language.h`, but automatically included if you include `djui.h`.

The usage is simple, the first param is the section, and the second param is the key. Lets take a look at this section:

```ini
[HOST_MOD_CATEGORIES]
ALL = "All"
ENABLED = "Enabled"
MISC = "Misc"
ROMHACKS = "Romhacks"
GAMEMODES = "Gamemodes"
```

To get the string for the `ENABLED` key, you'd run `DLANG(HOST_MOD_CATEGORIES, ENABLED)`. The first param being the section, the second being the key.

In certain situations the macro may not suit your needs. You may also use the direct function `djui_language_get`, which would allow you to pass in variables. You may also use other language functions such as `djui_language_replace` in the event you need to replace a sub-string with a string.

## Language Conventions

If an entry is fully translated, leave it as is:

```ini
[HOST_MOD_CATEGORIES]
ALL = "All"
ENABLED = "Enabled"
MISC = "Misc"
ROMHACKS = "Romhacks"
GAMEMODES = "Gamemodes"
```

---

If an entry has not yet been translated, comment it out:

```ini
[HOST_MOD_CATEGORIES]
ALL = "すべて"
; ENABLED = "Enabled"
MISC = "その他"
ROMHACKS = "ロムハック系"
GAMEMODES = "ゲームモード系"
```

---

If you have opted to machine translate an entry, mark it at the end:

```ini
[HOST_MOD_CATEGORIES]
ALL = "Tous"
ENABLED = "Activés" ;
MISC = "Autres"
ROMHACKS = "Romhacks"
GAMEMODES = "Modes de jeu"
```

If you find a machine-translated entry, seek advice from a speaker on the matter.

## Tools

The language checker (run `tools/check_languages.py`) can be used to report:

- Missing (untranslated) entries
- Extra (abandoned) entries

If the tool reports any incorrect entries, get them addressed as soon as possible. The base language is English, and all other languages will be checked against it.

Example output:

```sh
$ python ./tools/check_languages.py
Dutch.ini
  [DYNOS] Missing OPEN_DYNOS_FOLDER
  [HOST_MODS] Missing BROWSE_MODS, OPEN_MOD_FOLDER

German.ini
  [HOST_MESSAGE] Missing WARN_SOCKET_HIDE
  [HOST_SETTINGS] Extra: ENABLE_CHEATS
  [PAUSE] Extra: CHEATS

Italian.ini
  [HOST_SETTINGS] Extra: ENABLE_CHEATS
  [PAUSE] Extra: CHEATS
```
