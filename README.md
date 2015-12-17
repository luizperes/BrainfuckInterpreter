# Brainfuck Interpreter
This repository is a interpreter written in C for the esoteric programming language [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck). 

# News
There are two new custom commands in this interpreter.
My data now is stored in two bytes (no longer one byte).

### Version
If the current TAG version is less than 1.0, means that I am still working on it (of course). At the version v0.9 it is not __Turing Complete__ yet because I'm limiting my memory :)

### Details
I wanted to have my own interpreter for that language, since I might use it on future projects, for example on sending commands to an Arduino board (__1 BYTE COMMANDS!!!__).

I also might write a new esoteric language based on Brainfuck and/or translators for that as well.

### Usage
After compiling that (it was tested using __Clang 3.5__ and __GCC 4.8.4__), you just need to inform the .bf you want to execute:

__> ./brainfuck test.bf__

### Commands

The eight language commands, each consisting of a single character:

1. '>' increment the data pointer (to point to the next cell to the right).
2. '<' decrement the data pointer (to point to the next cell to the left).
3. '+' increment (increase by one) the byte at the data pointer.
4. '-' decrement (decrease by one) the byte at the data pointer.
5. '.' output the byte at the data pointer.
6. ',' accept one byte of input, storing its value in the byte at the data pointer.
7. '[' if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
8. ']' if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.

### Custom commands

There are __two new custom commands__ in this branch (still a single character):

9.  '!' prints out the number as a float (diving it by 100)
10. '#' prints out debugging information about the value inside the pointer and the position of the pointer.

### LICENSE
This project extends [GNU GPL v. 2](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html), so be aware of that, regarding copying, modifying and (re)destributing the application. 

