#ifndef SD_CARD_HANDLER_H
#define SD_CARD_HANDLER_H

#include "pico/types.h"

typedef struct item {
  char name[50];
  uint code;
  uint count;
} Item;

extern bool sd_mount();
extern void sd_unmount();
extern uint item_write(Item item);
extern Item *item_read(char code[6]);

#endif
