## [:rewind: C Reference](../c.md)

# Languages

## Tools
The language checker (run `tools/check_languages.py`) can be used to report:
- Missing (untranslated) entries
- Extra (abandoned) entries

If the tool reports any incorrect entries, get them addressed as soon as possible. The base language is English, and all other languages will be checked against it.

Example output:
```
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

## Conventions
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