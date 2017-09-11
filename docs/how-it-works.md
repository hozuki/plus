# How It Works

This document explains how the Plus language works, from reading the text source
to outputting the result.

In general, the whole process walks through 6 stages:

1. [Lexical Analysis](#lexical-analysis)
2. [Syntactic Analysis](#syntactic-analysis) (Parsing)
3. [Building AST](#building-ast)
4. [Compiling to Bytecode](#compiling-to-bytecode)
5. [Optimization](#optimization)
6. [Generating Machine Code](#generating-machine-code)

This is how most of the computer languages are finally executed. *No, not cutting
off their heads.* Some may differ in stage 3, where native languages (e.g. C, D,
Rust) will be directly optimized, and virtual machine (VM) languages (e.g. C#,
Smalltalk, Ruby) are compiled to [bytecode](https://en.wikipedia.org/wiki/Bytecode)
(or "intermediate code"), waiting to be executed by VMs. *Again, not cutting off
their heads.*

The Plus language only implements an accumulator, and it keeps going up. Real
languages are much more complicated. 

## Lexical Analysis

The source file is split into [tokens](https://en.wikipedia.org/wiki/Token_%28parser%29).
There are 5 kinds of tokens in this simple language. Take a look at this example:

```plain
+1s
10 people do
    +1s +1s
done
```

| Token Value (Lexeme) | Kind |
|---|---|
`+1s` | Increment operation |
Integer (positive), without leading zeros | Integer
`people` | "people" keyword
`do` | "do" keyword
`done` | "done" keyword

Each kind represents a basic unit kind in the syntax.

In this project, [flex](http://flex.sourceforge.net/) is used to generate the
lexer from [lexer description](../src/lang/plus1s.l).

## Syntactic Analysis

After getting tokens, statements are built based on the syntax. Each valid
sentence is composed by one or more tokens, in specified order. For example,
the loop in Plus looks like:

```plain
N people do
    ...
done
```

We know that N is definitely a positive integer, and the statement(s) in the
loop should be one or more "+1s"s. One form, mapped to one meaning. Multiple
forms corresponding to one meaning is also possible, but this case doesn't have
to show up in the Plus language.

In this project, [bison](https://www.gnu.org/software/bison/) is used to
generate the parser from [parser description](../src/lang/plus1s.y).

## Building AST

Abstract syntax tree (AST) is the abstract representation of a piece of code.
Words are understood by humans, and ASTs, containing full information about
the original code, are understood by compilers. This is the final output of the
parser, from a piece of code.

This is the AST of the program in Lexical Analysis section:

```plain
program
    |
    +- increment
    |
    +- loop -- (loop count: 10)
    |    |
    |    increment
    |    |
    |    increment
    |   
    (end)
```

## Compiling to Bytecode

Bytecode is like instruction in assembly language, but a program written in
bytecode is not directly bound to one specific platform and/or one processor
architecture. It is in the level between human-readable code, and machine code.

The program above can be noted as:

```plain
inc
inc
ls 10 // loop start; statements in the loop will be repeated for 10 times
inc
inc
le // loop end; automatically links to the nearest loop start before
   // this instruction
```

Yes, the whole bytecode set is defined by the language designer, including
notation, operands, meanings...

## Optimization

During the compile process, the bytecode emitter checks if a loop is empty, or it
repeats for 0 times. When an empty loop is detected, the whole loop is omitted so
no bytecode is generated for this loop. And again, since the language form is
really simple, the emitter can just use a simple depth-first traversal to detect
empty loops, and omit all loops that contain only empty loops.

## Generating Machine Code

If you have knowledge about assembly language, you can easily get to the point:

```assembly
inc eax ; increment (+1s)
add eax, 1 ; logically eqivalent

mov ecx, # ; a simple loop (# people do)
inc eax
loop
```

All the machine codes can be found on the Internet. To make the work even easier,
you can use online tools like [this (dis)assembler](https://defuse.ca/online-x86-assembler.htm).
X64 assembly is a little different from X86 assembly. The former is able to access
registers `rax`, `rbx`, etc. Sure, you can still use registers like `eax`, but
beware of instruction lengths.

Since machine codes have no alignments, the executable bytes are stored one after
another. For example:

```assembly
inc eax ; 0x40
inc eax ; 0x40
        ; complete executable bytes: { 0x40, 0x40 }
```

When entering a function, you should set up a stack frame:

```assembly
push ebp
mov  ebp, esp
sub  esp, N ; size of all variables used in this function
push ecx ; preserve the value of ECX register which will be used as the loop counter
xor eax, eax ; clear the accumulator
```

And when a function exits, restore the stack and return:

```assembly
pop ecx
mov esp, ebp
pop ebp
ret
```

The rest is filling the function body with increments and loops. Quite straightforward.

Apart from the processor architecture, API of the OS also matters. Fortunately
Windows and UNIX-like systems have similar function pairs, which have different
names and (maybe) different parameter list, but do the same thing. For this
part you should read the API documents.
