## [:rewind: C Reference](../c.md)

# Growing Arrays

Growing arrays are a custom type designed to handle dynamically scaling arrays in C. It allocates on the heap and only allocates what it needs, with no limit to how much it can allocate.

This won't go over every function, but it will go over the most important ones. For a complete view on all the functions, head to `src/game/memory.c`, and head over to the growing array section (starts at line 193).

## Setting Up

Define a pointer to a `GrowingArray` struct:

```c
struct GrowingArray *gGrowingArrayExample = NULL;
```

You then need to find a spot to initialize this growing array. Look for an appropriate place in your code to init the array, and call `growing_array_init` there.

You can initialize a growing array using the function

```c
struct GrowingArray *growing_array_init(struct GrowingArray *array, u32 capacity, GrowingArrayAllocFunc alloc, GrowingArrayFreeFunc free);
```

The first param is the array it points to. If you are reinitializing a growing array, you'd pass in your `gGrowingArrayExample`. If you're doing a first-time initialization, you could pass in `NULL`, however it's recommended to pass in your growing array for clarity.

The `capacity` argument is the initial capacity. You generally want to avoid reallocations as reallocations are slow, so keep this number as a good average for how much capacity your array would typically need.

Then there's an `alloc` function and a `free` function. In 99.999% of cases, you will pass in `malloc` for the allocation function and `free` for the free function. Note that while `malloc` usually doesn't zero-initialize the block of memory allocated, the growing array will zero-initialize the block, so all allocated memory is zero-initialized.

As an example initialization:

```c
gGrowingArrayExample = growing_array_init(gGrowingArrayExample, 16, malloc, free);
```

## Allocating to the Growing Array

Each growing array has a `count` and the `buffer`. The `count` is the number of active elements in the `buffer`. The `count` does **not** represent the `capacity` of the array.

To allocate data to the growing array, use the `growing_array_alloc` function.

```c
void *growing_array_alloc(struct GrowingArray *array, u32 size);
```

This function takes in your Growing Array, and requests a size. The size is the amount of bytes to allocate to the array element, typically the size of the struct being used.

The function returns a pointer to the data allocated. It always pushes to the end of the array, so if you need to store the index, the index will always be `gGrowingArrayExample->count` before allocation, or `gGrowingArrayExample->count - 1` after allocation.

## Removing Elements from a Growing Array

These are the functions for it:

```c
bool growing_array_swap_and_pop_index(struct GrowingArray *array, u32 index);
bool growing_array_swap_and_pop(struct GrowingArray *array, void *ptr);
```

One takes in a pointer to the block of data you want to remove, and another takes the index.

The `growing_array_swap_and_pop` finds the pointer in the array and then calls `growing_array_swap_and_pop_index` internally.

What "swap" and "pop" mean is quite simple. What's happening under the hood is it is taking the index provided, moving it to the end of the array, and decrementing the `count`. The element is still there and allocated, but can't be read unless you explicitly try to. On the next allocation using `growing_array_alloc`, the element will be zeroed out and the `count` will be incremented, acting like the popped element never existed.

This behavior is effectively equivalent to removing an element, we just don't bother with the processing required to actually free the element, especially since it will probably be used again either way. It would be quite inefficient to free the memory and then use it again shortly after, requiring unnecessary allocation.

Do note this swaps the last element with whatever index you passed into the function! Account for that when using this function.

## Iterating through a Growing Array

You have 2 options to iterate through a growing array. A standard for loop iterating `count` times and accessing the var via `gGrowingArrayExample->buffer[i]`, or using the `growing_array_for_each_` macro.

A simple for loop iteration looks like so:

```c
for (u32 i = 0; i < gGrowingArrayExample->count; i++) {
    // note: StoredStruct and storedStruct are placeholder names! use what you are storing
    // also note that in C++ you will need to cast gGrowingArrayExample->buffer[i]
    // into the type you are wanting
    struct StoredStruct *storedStruct = gGrowingArrayExample->buffer[i];

    // do stuff with stored struct
}
```

The other option is `growing_array_for_each_`. This macro takes in your growing array, the type for each element, and finally the last param is the variable to be created. The best way to show what it does is to show an example:

```c
growing_array_for_each_(gGrowingArrayExample, struct StoredStruct, storedStruct) {
    // do something with storedStruct. It's already the StoredStruct type
}
```

Very simple usage! Like before, `StoredStruct` and `storedStruct` are placeholders, use what you need there.

Note: When mixing types in a growing array, do **not** use `growing_array_for_each_`, use a conventional for loop instead.

## Cleanup

If you ever need to cleanup a growing array and remove it entirely, use the `growing_array_free` function:

```c
void growing_array_free(struct GrowingArray **array);
```

This function is quite simple. It just takes in your growing array and frees every element inside it, every allocated pointer, and the passed in array itself. It also `NULL`'s the passed in array, so you need to pass in a reference to the growing array, or `&gGrowingArrayExample`.
