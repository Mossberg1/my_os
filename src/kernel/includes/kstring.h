#pragma once

#include <ktypes.h>

void *kmemset(void *buf, char c, size_t n);
void *kmemcpy(void *dst, const void *src, size_t n);
char *kstrcpy(char *dst, const char *src);
int kstrcmp(const char *s1, const char *s2);
