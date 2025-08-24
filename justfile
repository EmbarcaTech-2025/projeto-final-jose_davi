[positional-arguments]
build device="MASTER":
    cmake -G Ninja -S . -B build -D DEVICE={{ device }}
    ninja -C build

[confirm("Clean build folder? (y/n)")]
clean:
    rm -rf build

load:
    picotool load -f build/src/app/$PROJECT_NAME.elf
