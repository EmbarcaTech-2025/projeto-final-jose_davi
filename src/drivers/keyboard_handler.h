#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

extern void keyboard_init();
extern char get_key();
extern char read_keyboard(char *expected);
extern int read_number(int len);
extern char is_number(char c);

#endif // !KEYBOARD_HANDLER_H
