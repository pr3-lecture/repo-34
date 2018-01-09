#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int strcon(const char* source, char needle) {
  int i = 0;
  int contains_needle = 0;
  while(source[i] != '\0' && !contains_needle) {
    contains_needle = source[i] == needle;
    i++;
  }
  return contains_needle;
}

int checkKey(const KEY key) {
  if(!key.chars || !strlen(key.chars))
    return E_KEY_TOO_SHORT;

  int i = 0;
  int key_chars_length = strlen(KEY_CHARACTERS);
  char* key_chars = KEY_CHARACTERS;

  while(i < key_chars_length && strcon(key_chars, key.chars[i]))
    i++;

  return i == strlen(key.chars) ? 0 : E_KEY_ILLEGAL_CHAR ;
}

int checkInput(const char* input) {
  if(!input || !strlen(input))
    return 5; // E_MESSAGE_TOO_SHORT

  int i = 0;
  int message_chars_length = strlen(MESSAGE_CHARACTERS);
  char* message_chars = MESSAGE_CHARACTERS;

  while(i < message_chars_length && strcon(message_chars, input[i]))
    i++;

  return i == strlen(input) ? 0 : E_MESSAGE_ILLEGAL_CHAR;
}

int checkDecypherText(const char* decypherText) {
  if(!decypherText || !strlen(decypherText))
    return 6; // E_CYPHER_TOO_SHORT

  int i = 0;
  int cypher_chars_length = strlen(CYPHER_CHARACTERS);
  char* cypher_chars = CYPHER_CHARACTERS;

  while(i < cypher_chars_length && strcon(cypher_chars, decypherText[i]))
    i++;

  return i == strlen(decypherText) ? 0 : E_CYPHER_ILLEGAL_CHAR;
}

int encrypt(KEY key, const char* input, char* output) {
  int valid_key = checkKey(key);
  int valid_input = checkInput(input);

  if(valid_key != 0)
    return valid_key;
  if(valid_input != 0)
    return valid_input;

  int i = 0;
  int key_length = strlen(key.chars);
  // output = (char*) malloc(length(input));
  while(input[i] != '\0') {
    output[i] = ((input[i] - 'A' + 1) ^ (key.chars[i % key_length] - 'A' + 1)) + 'A' - 1;
    i++;
  }
  return 0;
}

int decrypt(KEY key, const char* cypherText, char* output) {
  int valid_key = checkKey(key);
  int valid_cypherText = checkDecypherText(cypherText);

  if(valid_key != 0)
    return valid_key;
  if(valid_cypherText != 0)
    return valid_cypherText;

  int i = 0;
  int key_length = strlen(key.chars);

  while(cypherText[i] != '\0') {
    output[i] = ((cypherText[i] - 'A' + 1) ^ (key.chars[i % key_length] - 'A' + 1)) + 'A' - 1;
    i++;
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  // int i = 0;
  // KEY key;
  // while(i < argc)
  //   printf("%s", argv[i++]);
  // printf("\n");
  //
  // char* input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  // char* output = (char*) malloc(strlen(input) + 1);
  // key.chars = "TPERULES";
  // encrypt(key, input, output);
  // printf("original  : %s\n", input);
  // printf("key       : ");
  // i = 0;
  // while(input[i] != '\0')
  //   printf("%c", key.chars[i++ % strlen(key.chars)]);
  // printf("\n");
  // printf("output    : %s\n", output);
  //
  // char* cypherText = (char*) malloc(strlen(output) + 1);
  // strncpy(cypherText, output, strlen(output));
  // free(output);
  // output = NULL;
  // output = (char*) malloc(strlen(cypherText) + 1);
  // decrypt(key, cypherText, output);
  // printf("cypherText: %s\n", cypherText);
  // printf("key       : ");
  // i = 0;
  // while(input[i] != '\0')
  //   printf("%c", key.chars[i++ % strlen(key.chars)]);
  // printf("\n");
  // printf("output    : %s\n", output);
  // key.chars = NULL;
  // printf("checkKey(): %d\n", checkKey(key));
  // input = NULL;
  // printf("checkInput(): %d\n", checkInput(input));
  // output = "";
  // printf("checkDecypherText(): %d\n", checkDecypherText(output));

  int i = 0;
  while(i < argc)
    printf("%s ", argv[i++]);
  printf("\n");
  if(argc < 2)
    return 7; // E_ARGUMENTS_TOO_SHORT
  if(argc > 3)
    return 7; // E_ARGUMENTS_TOO_LONG

  // int mode = argv[0]
  if(argc == 2) {
    int buff_length = 255;
    char buff[255];
    KEY key;
    key.chars = argv[1];
    // strncpy(key.chars, argv[1], strlen(argv[1])); strange fault

    printf("KEY: %s, LENGTH: %d\n", key.chars, strlen(key.chars));

    printf("Enter a String: ");
    fgets(buff, buff_length, stdin);
    printf("\nYou String: %s, Length: %d\n", buff, strlen(buff));
  }

  if(argc == 3) {
    FILE* f;
    int buff_length = 255;
    char buff[255];
    KEY key;
    key.chars = argv[1];
    // strncpy(key.chars, argv[1], strlen(argv[1])); strange fault

    printf("KEY: %s, LENGTH: %d\n", key.chars, strlen(key.chars));

    f = fopen(argv[2] , "r");
     if(f == NULL) {
        perror("Error opening file");
        return(-1);
     }
     if(fgets(buff, 60, f) != NULL) {
        printf("GELESEN von %s: %s, LENGTH: %d\n", argv[2], buff, strlen(buff));
     }
     fclose(f);
  }

  return 0;
}
