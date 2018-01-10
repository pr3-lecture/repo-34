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
  int invalid_key = checkKey(key);
  int invalid_input = checkInput(input);

  if(invalid_key || invalid_input)
    output = NULL;

  if(invalid_key)
    return invalid_key;
  if(invalid_input)
    return invalid_input;

  int i = 0;
  int key_length = strlen(key.chars);
  // output = (char*) malloc(length(input));
  while(input[i] != '\0') {
    output[i] = ((input[i] - 'A' + 1) ^ (key.chars[i % key_length] - 'A' + 1)) + 'A' - 1;
    i++;
  }
  output[i] = '\0';
  return 0;
}

int decrypt(KEY key, const char* cypherText, char* output) {
  int invalid_key = checkKey(key);
  int invalid_cypherText = checkDecypherText(cypherText);

  if(invalid_key || invalid_cypherText)
    output = NULL;

  if(invalid_key)
    return invalid_key;
  if(invalid_cypherText)
    return invalid_cypherText;

  int i = 0;
  int key_length = strlen(key.chars);

  while(cypherText[i] != '\0') {
    output[i] = ((cypherText[i] - 'A' + 1) ^ (key.chars[i % key_length] - 'A' + 1)) + 'A' - 1;
    i++;
  }
  output[i] = '\0';
  return 0;
}
