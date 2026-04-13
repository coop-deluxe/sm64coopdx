## [:rewind: C Reference](../c.md)

# Config File

The configuration file is where all of the user's settings are stored. It's a decently easy to use system that allows you to add entries to the config file and use it with ease.

## Configuring the config file

Entries for the config file are handled in 2 files, `configfile.c`, and `configfile.h`, both are found in the `src/pc` directory.

To add an entry, at the top of the file there are a bunch of different variables. Go to wherever you deem appropriate and add your entry. A config file has these valid types:

```c
enum ConfigOptionType {
    CONFIG_TYPE_BOOL,
    CONFIG_TYPE_UINT,
    CONFIG_TYPE_FLOAT,
    CONFIG_TYPE_BIND,
    CONFIG_TYPE_STRING,
    CONFIG_TYPE_U64,
    CONFIG_TYPE_COLOR,
};
```

In the `options` array, you can add in your config file entry. Go to the same place you deemed appropriate, and add in your entry. An entry consists of a name, this is the key used to find your value. It then takes in a type, which is the type of the value. It lastly takes in that value set. These are the possible types of value:

```c
union {
    bool *boolValue;
    unsigned int *uintValue;
    float *floatValue;
    char *stringValue;
    u64 *u64Value;
    u8 (*colorValue)[3];
};
```

Lastly, head to the header file, or `configfile.h`, and add your variable there.