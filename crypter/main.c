#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

int main(int argc, char const *argv[]) {
  int i = 0;
  printf("ARGUMENTS: ");
  while(i < argc)
    printf("%s ", argv[i++]);
  printf("\n");
  if(argc < 2)
    return 7; // E_ARGUMENTS_TOO_SHORT
  if(argc > 3)
    return 7; // E_ARGUMENTS_TOO_LONG

  int buff_length = 255;
  char buff[255];
  KEY key;
  key.chars = argv[1];
  int mode = (strcmp(argv[0], "encrypt.exe") == 0 ||
              strcmp(argv[0], "./encrypt") == 0) ? 0 : 1; // 0 for encrypt
  printf("MODE %d\n", mode);
  printf("KEY: %s, LENGTH: %d\n", key.chars, strlen(key.chars));
  // int mode = argv[0]
  if(argc == 2) {
    // strncpy(key.chars, argv[1], strlen(argv[1])); strange fault


    printf("Enter a String: ");
    fgets(buff, buff_length, stdin);
    buff[strlen(buff)-1] = '\0';
    printf("\nYour text: %s, Length: %d\n", buff, strlen(buff));
  }

  if(argc == 3) {
    FILE* f = NULL;

    f = fopen(argv[2] , "r");
     if(f == NULL) {
        perror("Error opening file");
        return(-1);
     }
     if(fgets(buff, 60, f) != NULL) {
        printf("READ fom %s: %s, LENGTH: %d\n", argv[2], buff, strlen(buff));
     }
     fclose(f);
  }

  char* output = (char*) malloc(strlen(buff)+1);
  if(mode == 0) {
    int status = encrypt(key, buff, output);
    printf("ENCRYPT STATUS: %d, Input: %s, Output: %s.", status, buff, output);
  } else {
    int status = decrypt(key, buff, output);
    printf("DECRYPT STATUS: %d, Input: %s, Output: %s.", status, buff, output);
  }

  return 0;
}
