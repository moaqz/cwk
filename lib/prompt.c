#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prompt.h"

#define NULL_TERMINATOR '\0'
#define LINE_FEED '\n'

/**
 *
 * Read a line from the stream and return the first character if the line contains exactly
 * one character (excluding the newline).
 */
int read_option(FILE *stream)
{
  int c, selected, count;
  count = selected = 0;

  if (stream == NULL)
  {
    stream = stdin;
  }

  while ((c = fgetc(stream)) != EOF && c != '\n')
  {
    count++;

    if (!selected)
    {
      selected = c;
    }
  }

  if (c == EOF && count == 0)
  {
    return EOF;
  }

  if (count != 1)
  {
    return NULL_TERMINATOR;
  }

  return selected;
}

/**
 * Read a line from the stream into the buffer, returning the number of characters stored.
 *
 * Reads up to size - 1 characters into buf, appending a null terminator.
 * If the line is longer than the buffer, the remaining characters are discarded.
 */
int read_text(char *buf, int size, FILE *stream)
{
  int c, i;
  i = 0;

  if (stream == NULL)
  {
    stream = stdin;
  }

  while (i < size - 1 && (c = fgetc(stream)) != EOF && c != LINE_FEED)
  {
    buf[i++] = c;
  }

  if (c == EOF && i == 0)
  {
    return EOF;
  }

  if (c != LINE_FEED && c != EOF)
  {
    while ((c = fgetc(stream)) != LINE_FEED && c != EOF)
      ;
  }

  buf[i] = NULL_TERMINATOR;
  return i;
}

int is_confirm(char input)
{
  return input == 'Y' || input == 'N' || input == 'y' || input == 'n';
}

void prompt_text(char *out, int out_size, char *prompt, text_validation_fn fn)
{
  while (1)
  {
    printf("%s: ", prompt);
    int read_chars = read_text(out, out_size, stdin);

    if (read_chars == EOF)
    {
      printf("\n");
      exit(0);
    }

    if (fn(out))
    {
      break;
    }
  }
}

void prompt_select(char *out, char *prompt, select_validation_fn fn)
{
  while (1)
  {
    printf("%s: ", prompt);
    char c = read_option(stdin);

    if (c == EOF)
    {
      printf("\n");
      exit(0);
    }

    if (c == NULL_TERMINATOR)
    {
      continue;
    }

    if (fn(c))
    {
      *out = c;
      break;
    };
  }
}

void prompt_confirm(int *out, char *prompt)
{
  char opt;
  prompt_select(&opt, prompt, is_confirm);

  if (opt == 'Y' || opt == 'y')
  {
    *out = 1;
  }
  else
  {
    *out = 0;
  }
}
