#include "sd_card_handler.h"
#include "f_util.h"
#include "ff.h"
#include <pico/time.h>
#include <pico/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

FATFS fs;
FRESULT fr;
FIL fil;

bool sd_mount() {
  fr = f_mount(&fs, "", 1);
  if (FR_OK != fr) {
    return false;
  }

  return true;
}

void sd_unmount() { f_unmount(""); }

uint item_write(Item item) {
  uint bw;
  char code[8];

  sprintf(code, "%u", item.code);

  fr = f_open(&fil, code, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
  if (FR_OK != fr && FR_EXIST != fr) {
    return 1;
  }

  fr = f_write(&fil, &item, sizeof(Item), &bw);
  if (FR_OK != fr) {
    return 1;
  }

  fr = f_close(&fil);
  if (FR_OK != fr) {
    return 1;
  }

  return bw;
}

Item *item_read(uint32_t code) {
  char path[8];
  uint br;

  Item *item = malloc(sizeof(Item));
  sprintf(path, "%u", code);

  fr = f_open(&fil, path, FA_OPEN_EXISTING | FA_WRITE | FA_READ);
  if (FR_OK != fr && FR_EXIST != fr) {
    panic("f_open(%s) error: %s (%d)\n", code, FRESULT_str(fr), fr);
  }

  fr = f_read(&fil, item, sizeof(Item), &br);
  if (FR_OK != fr) {
    panic("f_write(%s) error: %s (%d)\n", code, FRESULT_str(fr), fr);
  }

  fr = f_close(&fil);
  if (FR_OK != fr) {
    printf("f_close error: %s (%d)\n", FRESULT_str(fr), fr);
  }

  if (br == sizeof(Item))
    return item;
  return NULL;
}
