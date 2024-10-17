## [:rewind: Lua Reference](../lua.md)

Setting up Visual Studio Code will allow you to have all of the modern benefits of IDEs like autocomplete.

---

1. Install the `Lua` extension by `sumneko` in VS Code:

![extension](https://user-images.githubusercontent.com/12403224/158046548-a8deba76-ca5f-4f35-aa73-62984820d290.png)

---

2. Goto settings (`ctrl+,`) and type `diagnostics disable` in the settings search bar:

![diagnostics](https://user-images.githubusercontent.com/12403224/158046741-3bcf513c-5da8-42ee-b3aa-ab2dbab0e3dc.png)

---

3. Add a new item called `lowercase-global` and click `ok`

![lowercase-global](https://user-images.githubusercontent.com/12403224/158046761-65883e86-fd17-4d90-a566-78fe93b4b51d.png)

---

4. Type `workspace library` in the settings search bar:

![workspace-library](https://user-images.githubusercontent.com/12403224/158046786-12b8a150-65a7-4f23-96c7-1508f8f80713.png)

---

5. Add a new item containing the location of `<your repo>/autogen/lua_definitions`

![lua-definitions](https://user-images.githubusercontent.com/12403224/158046824-1894318a-7ce9-41ef-bacc-17f95fa05f31.png)

---

6. Open a lua mod file be amazed at autocompletion and all of that good stuff
![autocompletion](https://user-images.githubusercontent.com/12403224/158046991-77670bae-33a9-467c-a07d-3ce6eba28673.png)

---

Note: For your custom functions you will need to provide type definitions to get autocomplete.

For instance, this will not autocomplete for the mario struct:
```
function mario_update(m)
    -- code here
end
```

But this will autocomplete for the mario struct:
```
--- @param m MarioState
function mario_update(m)
    -- code here
end
```