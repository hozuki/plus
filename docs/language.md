# Plus Language Specification

## Higher Level

```plain
PLUS1S := "+" "1" "s"
NUMBER := [1-9][\d]*
LOOP_BEGIN := NUMBER "people" "do"
LOOP_END := "done"
LOOP := LOOP_BEGIN PLUS1S+ LOOP_END
PROGRAM := (PLUS1S | LOOP)+
```

## Bytecode

Size: 1 byte each

### NOP

- Value: `0`
- Operands: None

### EXIT

- Value: `1`
- Operands: None

### INCREMENT

- Value: `2`
- Operands: None

### JUMP

- Value: `3`
- Operands:
  - `dest`
    - Size: (native integer size)
    - Value: instruction offset (in our case, its index),
             from the start of the program
