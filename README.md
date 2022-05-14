# baelog-os

compilation line :

nasm boot_sect.asm -f bin -o <binary_name>

execution with qemu (for now on):

qemu-system-x86_64 -drive file=boot_sect.bin,index=0,media=disk,format=raw
