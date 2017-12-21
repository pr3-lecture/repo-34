#include <stdio.h>
#include <stdlib.h>
#include "crypto.h"

int length(const char* s) {
  int length = 0;
  while(s[length++] != '\0');
  return length - 1;
}

int encrypt(KEY key, const char* input, char* output) {
  int i = 0;
  int key_length = length(key.chars);
  // output = (char*) malloc(length(input));
  printf("%d     %d\n", key_length, length(input));
  while(input[i] != '\0') {
    output[i] = ((input[i] - 'A' + 1) ^ (key.chars[i % key_length] - 'A' + 1)) + 'A' - 1;
    i++;
  }
  printf("in: %s\n", output);
}

int main(int argc, char const *argv[]) {
  // int a = 1;
  // int b = 1;
  // int c = a ^ b;
  // char s[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  // char k[] = "TPERULES";

  // printf("a: %d\n", a);
  // printf("b: %d\n", b);
  // printf("c: %d\n", c);

  // int i = 0;
  // while(s[i] != '\0') {
  //   printf("original => %2d, %c; key => %2d, %c; crypt => %2d, %c\n",
  //                                                 s[i] - 'A' + 1, s[i],
  //                                                 k[i % length(k)] - 'A' + 1, k[i % length(k)],
  //                                                 (s[i] - 'A' + 1) ^ (k[i % length(k)] - 'A' + 1), ((s[i] -'A' + 1) ^ (k[i % length(k)] - 'A' + 1)) + 'A' - 1);
  //   i++;
  // }

  // printf("original: %d; key: %d\n", length(s), length(k));

  KEY key;
  char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  printf("size %d  length %d\n", sizeof input, length(input));
  char* output = (char*) malloc(length(input));
  key.chars = "TPERULES";
  encrypt(key, input, output);
  printf("ou: %s\n", output);
  return 0;
}
