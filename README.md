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

## Building a ROM

It is recommended to use one of the example ROMs for this procedure. You will
need my tool flasher (https://github.com/CeriseSky/flasher) installed in the
system path. Then:

```
$ ./scripts/make_roms.sh
$ mv {vrom,test}.rom
$ flasher test.rom 0 roms/test2.txt
```

