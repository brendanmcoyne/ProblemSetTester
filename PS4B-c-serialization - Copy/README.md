# C Serialization

Welcome to our first C programming assigment. This problem set is a bit different from the others we have seen so far. Instead of implementing a program, we will be debugging and modifying a program that is _almost_ working!

Often times as programmers we need to understand, debug, and build upon code that we did not write ourselves. This programming assigment will teach us some useful C skills -- gdb, memory management, etc, before we work up to building a program from scratch.

> KEY Takeaways: 
> - How to debug C programs using gdb 
> - How C's data types appear in memory
> - How to use pointers
> - How to use dynamically allocated memory (via malloc)
> - How to implement/use a linked list in C

## Step 0: Understanding Serialization

The codebase you have here is a simple serialization library. Serialization is the process of encoding typed data (an int, float, c struct, etc.) and turning it into a compressed storable or sendable format. You can imagine it as turning structured data into binary.

If you have used/seen the python package `pickle` this is one example of a serialization library.

An example of serialization in python is included in the `python_example/` directory. We can see how the `pickle` libary allows python programmers to take a structured format 'test_object', transform it into intermediate serialized data (saved in `data.pickle` file), and then later read and transform it back into a structured data object.

```python
import pickle

test_object = {"name": "Bob", "values": [123,15,41,12,1], "city": "Boston"}

print(pickle.dumps(test_object))

with open("data.pickle", "wb") as f:
    pickle.dump(test_object, f)

with open("data.pickle", "rb") as f:
    loaded_obj = pickle.load(f)

print(loaded_obj)
```

Serialization can be useful for storing data in a file to load into your program later, it can also be useful for formatting data in a format that can easily be sent over the network.

We will be completeing the serialization library provided in this assignment. How do we know if that array of bytes from the sender should be interpreted as an int, float, or array of characters? This will be detailed in our serialization functions.

Ideally, we want to take some structured data, i.e 2 ints, 1 char. And then pack them into a format that we can send over the network. How does this look? For example:

```
    struct P {
        int x
        int y
        char icon
    }
```
Let's say we initialize one struct P as follows and then "serialize" it.

```
struct P test = {3,6,'L'}
```

Packed into serialized format this could ressemble:
```
[03, 00, 00, 00, 06, 00, 00, 00,  4c]
```

Then, with a deserialization function we can recieve an array of bytes and re-create the original struct.

## Step 0.25: Let's Play a Game

Take a look at `game.c`. Inside this file contains a simple text-based game written in C.
Read through the code, can you figure out what it does?

Run the following command to `make` the files in the project:

```
    make build/game
```

Now, try running the game with:
```
 ./build/game
```

- You will see that you can type `N` to start a new game. 
- You can then specify what character you wish to represent your player. 
- Then, you are repeatedly propted to press: 'u','d','l','r' to navigate your player around a board, looking for a treasure.

The developers of this game want to add a save/load from a file feature to their game.
Currently, the workings of this feature are all in place. The only missing part? The serialization library.

By the end of this assignment, while playing a game, you will be able to press `s` to save your game to a specified filepath.

Then, if restarting the program, instead of starting a new game, you may type `L`, to load a game from a specified function.

Test and see what happens if you try to `s` to save your game currently. You will see a `Segmentation Fault`! Oh no!

## Step 0.5: Understanding Existing Serialization Code

The existing serialization library provided to you *almost* works.

It is compiled of several files:
- buffer.c
- serialize.c
- serialize_custom.c
- file_loader.c

For each of these files, there is a corresponding header file.
- buffer.h
- serialize.h
- serialize_custom.h
- file_loader.h

Header files allow you to use `#include` external function definitions so that, for example, we can call library functions from our code. The body of these external functions will later be included when we compile and link our C program together.

Take a look at these files and the provided comments before beginning the assignment. See if you can piece together how these files work together. The comments will help you as you complete the assignment!

## Note
A struct that you will be using frequently is the `Buffer` struct. This struct is defined in `buffer.h`. Make sure you understand the fields of this struct before moving forwards!

## Step 1: Debugging Existing Code

Complete the following tasks:

1. Debug the serialization library so that it successfully serializes ints and floats.  

    - Run `make`. We will see that it attempts to build several files: `build/test` and `build/game` for example.  

    - On this first run of `make`, we will get several compilation warnings. You can ignore these for the time being, as they should be resolved when you implement the missing functionality for this assignment. At this point `make` will successfully build the necessary files.

2. Run the program in gdb to find where the program is throwing errors/segmentation faults.

    - Run: `gdb build/test`

    - You will notice the gdb program interrupts before completeing. What file and line number was it running that caused the error? Identify and resolve this error.

    - As you work through this assignment, you should continue to use 'gdb build/test' to identify your next error to resolve. When you have finished all required work, 'gdb build/test' should complete without error. 
    
    - Note: Some tests will report a 0/1 score, as we have not implemented them yet!

> ### Note Memcpy
> The current implemenation of `serialize` and `deserialize` makes heavy use of a C stdlib function known as `memcpy`. What does memcpy do?
>
> Notice, the function header is as follows:
> ```void *memcpy(void *dest, void *src, size_t n);```
>
> From this function header, we can see that memcpy takes in a pointer to a destination region in memory, and a pointer to a src region in memory, aswell as `n`, a size (in bytes) to copy.
>
> Type in `man 3 memcpy` to see a description of this function.
> 
> ``` The  memcpy() function copies n bytes from memory area src to memory area dest.  The memory areas must not overlap.```



After resolving the first few errors you encounter after 'gdb build/test', (read the comments carefully for additional hints), you should be able to run `make` and `./build/test` and pass the following tests:
```
./build/test
Test Serialize Int 1          : 1/1
Test Serialize Int 2          : 1/1
Test Serialize Float 1        : 1/1
``` 

## Step 2: Implementing Serialization of char type

Add serialization capabilities for the `char` type in `serialize.c`

At this point you should be able to run `make` and `./build/test` and pass the following tests:
```
./build/test
Test Serialize Char 1         : 1/1
Test Serialize Char 2         : 1/1
``` 

## Step 3: Implementing Serialization of string or char* type

Now add serialization of the char * (or C string) data type.

HINT: if you serialize multiple things, what order do you need to deserialize them in?

HINT: when implementinging `deserialize_string`, consider that the caller doesn't know the size of the string that's being deserialized. Therefore the pointer they pass in might not point to a large enough allocation for the string. Therefore, you'll need to reallocate it to ensure that it's large enough. You might want to look into the `realloc()` standard library function.

At this point you should be able to run `make` and `./build/test` and pass the following tests:
```
Test Serialize String 1: 1/1
Test Serialize String 2: 1/1
```

## Step 4: Implementing Serialization of a Struct

Now we wish to serialize more complicated data structures. Add serialization capabilities for structs P and T in `serialize_custom.c`.

At this point you should be able to run `make` and `./build/test` and pass the following tests:
```
Test Serialize Struct P       : 1/1
Test Serialize Struct T       : 1/1
Test Serialize Struct P+T     : 1/1
```

## Step 5: Linked List

Next we want to serialize a linked list data type in `serialize_custom.c`.

At this point you should be able to run `make` and `./build/test` and pass the following tests:
```
Test Serialize Linked List    : 1/1
Test Serialize Linked List 2  : 1/1
```

## Step 6: Read and Write to file

The final feature we wish to add is the ability to read/write our serialized data to a file on our computer. We will call these `.pepper` files (as opposed to python's `.pickle` files).

Just as with assembly, C allows you to make linux **syscalls** directly from your code.

We will use two system calls: one to write serialized data to a file, and another to read serialized data from a file.

In order to be able to read back the correct number of bytes upon deserialization, we must save three pieces of metadata to our binary data file as well when serializing:
- The first 8 bytes should be the `size_t size`
- The next 8 bytes should be the `size_t top`
- The next `size` bytes should be the data array.

Implement the folowing method:
- `serialize_file(int fd, Buffer *b)` which takes an open **file descriptor** and a buffer of serialized data and properly writes the data to the file with the `write` system call. 

At this point you should be able to run `make` and `./build/test` and pass the following tests:
```
Test Serialize to/from File   : 1/1
```

## Step 7: Enjoy Saving/Loading in game.c

Now, try playing the treasure hunting game again. This time, make sure to hit `s` at some point mid-game and specify a filepath to save your game.

Press any invalid command key to exit the game (i.e. press `q`), then, restart the game and type `L` to load a game (instead of starting a new one).

You should be able to resume the game where you left off! No more segfaults!

