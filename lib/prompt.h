#include <stdio.h>

typedef int (*text_validation_fn)(const char *input);
typedef int (*select_validation_fn)(char input);

int read_text(char *buf, int size, FILE *stream);
int read_option(FILE *stream);

int is_confirm(char input);

void prompt_confirm(int *out, char *prompt);
void prompt_select(char *out, char *prompt, select_validation_fn fn);
void prompt_confirm(int *out, char *prompt);
