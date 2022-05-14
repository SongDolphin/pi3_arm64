cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/tool_chain/aarch64.cmake ..
make
qemu-system-aarch64 -machine raspi3b -nographic -kernel pi3_arm64.elf -s -S
