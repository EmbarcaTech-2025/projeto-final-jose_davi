#ifndef SD_CARD_HANDLER_H
#define SD_CARD_HANDLER_H

#include "pico/types.h"
#include <stdint.h>

typedef struct {
  char name[50];
  uint32_t code;
  uint32_t count;
} Item;

extern bool sd_mount();
extern void sd_unmount();
extern uint item_write(Item item);
extern Item *item_read(uint32_t code);

#endif
