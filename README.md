# Emulated CPU
Simulates the happenings of the components of a custom CPU. Not designed to
be a performant emulator, but a fairly accurate showcase of how CPUs actually
work!

## Buidling

```
$ make -j$(nproc)
```

## Running

```
$ install/linux/bin/cpu
```

## Machine Code

The machine code for this CPU uses fixed-width 4-byte instructions. In hexadecimal,
they are as follows:

```
HLT - Halts the CPU - 0000 <word 2 ignored>
LDA - Load from address to accumulator - 0001 <memory address>
```

The machine is little endian, so the binary for LDA 6 would be:

```
00000001 00000000 00000110 00000000
```

