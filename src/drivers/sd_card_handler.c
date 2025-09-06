#include "sd_card_handler.h"
#include "ff.h"
#include <pico/time.h>
#include <pico/types.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  uint8_t buf[60];
  char path[12];

  sprintf(path, "%06u.txt", item.code);

  fr = f_open(&fil, path, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
  if (FR_OK != fr && FR_EXIST != fr) {
    return 1;
  }

  memcpy(buf, &item, 60);
  fr = f_write(&fil, buf, sizeof(Item), &bw);
  if (FR_OK != fr) {
    return 1;
  }

  f_sync(&fil);

  fr = f_close(&fil);
  sleep_ms(100);
  if (FR_OK != fr) {
    printf("f_close error: %d\n", fr);
    return 1;
  }

  return bw;
}

Item *item_read(uint32_t code) {
  uint br;
  uint8_t buf[60];
  char path[12];

  Item *item = malloc(sizeof(Item));
  sprintf(path, "%06u.txt", code);
  puts(path);

  fr = f_open(&fil, path, FA_OPEN_EXISTING | FA_READ);
  if (FR_OK != fr && FR_EXIST != fr) {
    free(item);
    return NULL;
  }

  fr = f_read(&fil, buf, sizeof(Item), &br);
  memcpy(item, buf, 60);

  fr = f_close(&fil);
  if (FR_OK != fr) {
    free(item);
    return NULL;
  }

  if (br == sizeof(Item))
    return item;
  free(item);
  return NULL;
}

uint write_log(AccessLog log) {
  uint bw;
  size_t log_len = sizeof(log);
  uint8_t buf[log_len];
  char path[sizeof(log.timestamp) + 5];

  sprintf(path, "%s.txt", log.timestamp);

  fr = f_open(&fil, path, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
  if (FR_OK != fr && FR_EXIST != fr) {
    return 1;
  }

  memcpy(buf, &log, log_len);
  fr = f_write(&fil, buf, log_len, &bw);
  if (FR_OK != fr) {
    return 1;
  }

  f_sync(&fil);

  fr = f_close(&fil);
  sleep_ms(100);
  if (FR_OK != fr) {
    return 1;
  }

  return bw;
}
