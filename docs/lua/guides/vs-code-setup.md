## [:rewind: Lua Reference](../lua.md)

Setting up Visual Studio Code will allow you to have all of the modern benefits of IDEs like autocomplete.

## IMPORTANT

Install the <code>Lua</code> <a href="https://marketplace.visualstudio.com/items?itemName=sumneko.lua">extension</a> by <code>sumneko</code> in VS Code:
<br>
<img alt="extension" src="https://github.com/user-attachments/assets/15926d42-fa6c-4c30-a180-0fe4b06fedcb"/>

---
<details><summary>JSON Setup (near instant, a tad complicated)</summary>

<details><summary>1. Open the Command Palette (<code>Ctrl</code> + <code>Shift</code> + <code>P</code>)</summary>
<br>
<img alt="command-palette" src="https://github.com/user-attachments/assets/cdec296b-6465-42fe-90d9-4c72bf7f05bf"/>
</details>

---
<details><summary>2. Type <code>settings json</code> and select <code>Preferences: Open User Settings (JSON)</code></summary>
<br>
<img alt="settings-json" src="https://github.com/user-attachments/assets/c3ab5234-254c-498e-8cbc-073c323a6730"/>
</details>

---
<details>
<summary>
3. Paste the following lines into the file where appropriate (replace the <code>library</code> path with your own):
</summary>
<pre>
    "Lua.diagnostics.disable": [
        "lowercase-global"
    ],
    "Lua.workspace.library": [
        "\\path\\to\\sm64coopdx"
    ],
    "Lua.runtime.nonstandardSymbol": [
        "+=",
        "-=",
        "*=",
        "%=",
        "^=",
        "/=",
        "//=",
        "&=",
        "|=",
        "<<=",
        ">>=",
    ],
</pre>
<br>
<img alt="lines" src="https://github.com/user-attachments/assets/64cdf1a4-baec-4153-977f-4ecb0a929153"/>
</details>

---
4. Hit <code>Ctrl</code> + <code>S</code> to <code>Save</code> the file

---
</details>
<b>OR</b>
<details><summary>UI Setup (comprehensive, but slow)</summary>

<details><summary>1. Open Settings (UI) (<code>Ctrl</code> + <code>,</code>) and type <code>diagnostics disable</code> in the <code>Search settings</code> bar:</summary>
<br>
<img alt="diagnostics" src="https://github.com/user-attachments/assets/c2e3af1e-78ac-4693-ba83-0ffc898a033c"/>
</details>

---
<details><summary>2. Add a new item called <code>lowercase-global</code> and click <code>OK</code></summary>
<br>
<img alt="lowercase-global" src="https://github.com/user-attachments/assets/ba932d1e-cc2d-4422-b37c-0e85909cd7b5"/>
</details>

---
<details><summary>3. Type <code>workspace library</code> in the <code>Search settings</code> bar:</summary>
<br>
<img alt="workspace-library" src="https://github.com/user-attachments/assets/8c01242e-6292-4842-88f1-3fb305075dde"/>
</details>

---
<details><summary>4. Add a new item containing the location of <code>&lt;your repo&gt;/autogen/lua_definitions</code> (make sure you've cloned the repository!)</summary>
<br>
<img alt="lua-definitions" src="https://github.com/user-attachments/assets/712109c1-7ac8-4787-909d-b101cefa2574"/>
</details>

---
<details><summary>5. Type <code>nonstandard symbol</code> in the <code>Search settings</code> bar and add all the items listed below:</summary>
<br>
<img alt="nonstandard-symbol" src="https://github.com/user-attachments/assets/721ca579-2c79-4539-9869-b20b38181b44"/>
</details>

</details>

---
<details><summary>After following either method, open a <code>.lua</code> mod file be amazed at autocompletion and all of that good stuff</summary>
<br>
<img alt="autocompletion" src="https://github.com/user-attachments/assets/e8be351f-1f45-4a12-91fa-055c0e895b2e"/>
</details>
<br>

# Notes
## Annotations
For your custom functions, you will need to provide type annotations to get autocompletion.

For instance, this will not autocomplete for the Mario struct:
```lua
function mario_update(m)
    -- code here
end
```

But this will autocomplete for the Mario struct:
```lua
--- @param m MarioState
function mario_update(m)
    -- code here
end
```

Learn to use the appropriate annotations for your functions, variables, and classes!

## Assignment Operators (v1.4+)
SMLua adds various assignment operators (not present in stock Lua) to allow for more convenient and C-like syntax:

### Arithmetic
| Operator | Effect       | Usage     | Equivalent   |
| -------: | :----------- | --------: | ------------ |
|    +=    | Add          |  `a += 2` | `a = a + 2`  |
|    -=    | Subtract     |  `a -= 2` | `a = a - 2`  |
|    *=    | Multiply     |  `a *= 2` | `a = a * 2`  |
|    %=    | Modulo       |  `a %= 2` | `a = a % 2`  |
|    ^=    | Power        |  `a ^= 2` | `a = a ^ 2`  |
|    /=    | Divide       |  `a /= 2` | `a = a / 2`  |
|   //=    | Floor Divide | `a //= 2` | `a = a // 2` |

### Bitwise
| Operator | Effect      | Usage     | Equivalent   |
| -------: | :---------- | --------: | ------------ |
|    &=    | AND         |  `a &= 2` | `a = a & 2`  |
|   \|=    | OR          | `a \|= 2` | `a = a \| 2` |
|   <<=    | Left Shift  | `a <<= 2` | `a = a << 2` |
|   >>=    | Right Shift | `a >>= 2` | `a = a >> 2` |
