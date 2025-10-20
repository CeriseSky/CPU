#!/bin/sh

# doesn't actually compile any roms, just creates a blank 4K virtual rom chip.
# Apologies for the HORRIFIC script name lol

set -e

dd if=/dev/urandom of=vrom.rom bs=1024 count=4

