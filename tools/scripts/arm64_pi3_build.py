import os
import sys
import shutil

def Arm64_Pi3_Build_Usage():
    print("", file = sys.stderr)
    print("Usage: arm64_pi3_build.py opyions [params]", file = sys.stderr)
    print("python3 arm64_pi3_build.py run", file = sys.stderr)
    print("python3 arm64_pi3_build.py debug", file = sys.stderr)
    print("", file = sys.stderr)
    sys.exit(1)

def Arm64_CMake_Config_And_Kernel_Build():
    print('Start to build target....\n')
    shutil.rmtree('../../build')
    os.mkdir('../../build')
    os.chdir('../../build')
    os.system('cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/tool_chain/aarch64.cmake ..')
    os.system('make')
    os.system('make install')
    os.chdir('../tools/scripts')

def Arm64_Pi3_Build_Run():
    Arm64_CMake_Config_And_Kernel_Build()
    print('---------------------------------------------------------------------------------------')
    os.system('qemu-system-aarch64 -machine raspi3b -nographic -kernel ../../install/pi3_arm64.elf')

def Arm64_Pi3_Build_Debug():
    Arm64_CMake_Config_And_Kernel_Build()
    print('---------------------------------------------------------------------------------------')
    os.system('qemu-system-aarch64 -machine raspi3b -nographic -kernel ../../install/pi3_arm64.elf -S -s')

def Arm64_Pi3_Build(argc, argv):
    print(f'argc = {argc}, argv = {argv}')
    if argc != 1:
        Arm64_Pi3_Build_Usage()
    elif argc == 1 and argv[1] == "run":
        Arm64_Pi3_Build_Run()
    elif argc == 1 and argv[1] == "debug":
        Arm64_Pi3_Build_Debug()
    else:
        Arm64_Pi3_Build_Usage()
    print(f'finish build')

if __name__ == "__main__":
    Arm64_Pi3_Build(len(sys.argv) - 1, sys.argv)

