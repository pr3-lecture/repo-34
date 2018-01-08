#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int encrypt(KEY key, const char* input, char* output) {
  int i = 0;
  int key_length = strlen(key.chars);
  // output = (char*) malloc(length(input));
  while(input[i] != '\0') {
    output[i] = ((input[i] - 'A' + 1) ^ (key.chars[i % key_length] - 'A' + 1)) + 'A' - 1;
    i++;
  }
}

int decrypt(KEY key, const char* cypherText, char* output) {
  int i = 0;
  int key_length = strlen(key.chars);

  while(cypherText[i] != '\0') {
    output[i] = ((cypherText[i] + 'A' - 1) ^ (key.chars[i % key_length] + 'A' - 1)) - 'A' + 1;
    i++;
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  int i = 0;
  KEY key;
  while(i < argc)
    printf("%s", argv[i++]);
  printf("\n");

  char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char* output = (char*) malloc(strlen(input) + 1);
  key.chars = "TPERULES";
  encrypt(key, input, output);
  printf("original  : %s\n", input);
  printf("key       : ");
  i = 0;
  while(input[i] != '\0')
    printf("%c", key.chars[i++ % strlen(key.chars)]);
  printf("\n");
  printf("output    : %s\n", output);

  char* cypherText = (char*) malloc(strlen(output) + 1);
  strncpy(cypherText, output, strlen(output));
  free(output);
  output = NULL;
  output = (char*) malloc(strlen(cypherText) + 1);
  decrypt(key, cypherText, output);
  printf("cypherText: %s\n", cypherText);
  printf("key       : ");
  i = 0;
  while(input[i] != '\0')
    printf("%c", key.chars[i++ % strlen(key.chars)]);
  printf("\n");
  printf("output    : %s\n", output);
  return 0;
}
