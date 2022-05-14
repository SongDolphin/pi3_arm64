cmake_minimum_required(VERSION 3.20)
enable_language(C ASM)

project(pi3_arm64.elf)

set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -e _start")
set(CMAKE_ASM_FLAGS     "-g -Iinclude -x assembler-with-cpp -MMD")
set(CMAKE_C_FLAGS       "-DCONFIG_BOARD_PI3B -g -Wall -nostdlib -nostdinc -Iinclude -MMD")

message("CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
message("CMAKE_ASM_FLAGS = ${CMAKE_ASM_FLAGS}")
message("CMAKE_EXE_LINKER_FLAGS = ${CMAKE_EXE_LINKER_FLAGS}")

file(GLOB SRC_LIST
	"kernel/*.c"
	"boot/*.S"
	"drives/*.c")

message("SOUCER = ${SRC_LIST}")
add_executable(pi3_arm64.elf ${SRC_LIST})

target_include_directories(pi3_arm64.elf PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_custom_command(TARGET pi3_arm64.elf POST_BUILD
					COMMAND aarch64-linux-gnu-objcopy pi3_arm64.elf -O binary pi3_arm64.bin
					DEPENDS pi3_arm64.elf)
