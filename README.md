# plus ("multiple ones" here)

Do you feel that 24 hours a day is not enough?

Fortunately, a big brother is also thinking this way. He proposes that, by
gathering time, mankind will have a better life. Some dissidents call
this behavior "time crowdfunding", which is an insult to the big brother
because mankind can't produce huge amount of fortunes by keeping silent.

Please, donate 1 second (+1s) for his kindness.

I don't have that much of time so I wrote this simple two-tier JIT compiler.
The executable reads P1S source code from file, translates them into bytecode,
compiles them to machine code, and finally runs the code. The language is so
simple that all it can manipulate is an accumulator.

Now I'm glad to announce that the JIT compiler runs on both x86 and x86-64
processors, on Windows and (very likely) Linux/macOS. Tested environments are
MinGW32 (32-bit Windows API) and Cygwin64 (64-bit Unix API).

## Usage

> 👩:👨✌👍👎?🐸:👍 👩:🀄👍?🐸:👍 👩:🀄📢?🐸:💨☔,📖✋ 👩:😳 🐸:🙅,🀄📢❌,🎥📖. [source](http://music.163.com/#/song?id=230067)

Compile it first!

```cmd
plus1s <P1S text file>
```

## Features

A quick overview:

```plain
// 154 seconds in total
+1s
+1s
+1s
20 people do
    // +1s // Comments!
    // This loop will be optimized.
done
0 people do
    +1s
    // This loop will also be optimized.
done
+1s
50 people do
    +1s +1s +1s
done
```

Unlike the source of inspiration, the Plus language does not support
nested loops. The reason is nested loops are illogical in this context.
Let's see an example:

```plain
10 people do
    20 people do
        +1s // Who is the subject of this action? Each of "200 squared people"?
    done
done
```

Thanks to this <del>too young too</del> simple language form, some<del>times</del> naive
optimizations can be done. (But what's the meaning of those optimizations? Why don't
we simply add the numbers together?)

[Inspiration](https://github.com/IndeedPlusPlus/jit-in-10-minutes)

## Prerequisites

You will need `lex`/`flex` and `yacc`/`bison` to compile the language definitions.
If you don't have them, keep calm and find pre-generated C sources under
`src/lang`.

A Unix-like building environment is required. I haven't try Visual C++ yet and I
think Visual C++ should be able to compile this project. If your OS is Windows and
you are uncertain, please build it with MinGW/Cygwin.

Most importantly, though you don't need knowledge in compiler principles to
understand the code, you must have a concept how executables work in operating systems,
and basics of assembly language.

## License

MIT
