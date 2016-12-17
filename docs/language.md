# Plus Language Specification

## Higher Level

See [lexical](../src/lang/plus1s.l) and [grammatical](../src/lang/plus1s.y) definitions.

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

### LOOP_START

- Value: `3`
- Operands:
  - `count`
    - Size: (native integer size)
    - Value: number of people (loop)
