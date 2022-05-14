# baelog-os

https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
was a great help

compilation line :

nasm boot_sect.asm -f bin -o <binary_name>

execution with qemu (for now on):

qemu-system-x86_64 -drive file=<binary_name>,index=0,media=disk,format=raw
