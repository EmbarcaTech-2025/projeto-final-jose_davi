{
  pkgs,
  lib,
  config,
  inputs,
  ...
}:

let
  pico-sdk = pkgs.pico-sdk.override { withSubmodules = true; };
in
{
  packages = with pkgs; [
    cmake
    ninja
    gcc
    gcc-arm-embedded
    just
    picotool
    pico-sdk
    python3
    quirc
    minicom
  ];

  env = {
    PROJECT_NAME = "sd_card";
    PICO_SDK_PATH = "${pico-sdk}/lib/pico-sdk";
  };

  scripts.picoserial.exec = ''
    sudo minicom --device /dev/ttyACM0
  '';
}
