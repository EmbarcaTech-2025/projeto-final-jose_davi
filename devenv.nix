{ pkgs, lib, config, inputs, ... }:

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
    libusb1 
    newlib 
    pico-sdk
    minicom
    quirc
  ];

  env.PROJECT_NAME = "projeto_final";
  env.PICO_SDK_PATH = "${pico-sdk}/lib/pico-sdk";

  scripts.picoserial.exec = ''
    sudo minicom --device /dev/ttyACM0
  '';
}
