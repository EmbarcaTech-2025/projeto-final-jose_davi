[positional-arguments]
build target="production":
  cmake -G Ninja -S . -B build -D TARGET_GROUP={{target}}
  ninja -C build

clean:
  rm -rf build

load:
  picotool load -f build/src/app/$PROJECT_NAME.elf
