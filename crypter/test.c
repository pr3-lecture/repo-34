#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

#define mu_assert(message, test) do { if (!(test)) return message; return 0; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
#define CORRECT_INPUT "ABCDEGHIJKLMNOP"
#define INPUT_WITH_EXCLAMATON_MARK "ABCDEGHIJK!MNOP"
#define CORRECT_INPUT_ENCRYPT "URFVPKMZ^[I_[CU"
#define CORRECT_KEY "TPERULES"
int tests_run = 0;

// static char* test1() {
//     mu_assert("Meldung", 1 == 1);
// }

/*--------------------------- test key ---------------------------*/
static char* test_CORRECT_KEY() {
    KEY key;
    key.chars = "TPERULES";
    mu_assert("Correct Key passed", checkKey(key) == 0);
}

static char* test_TOO_SHORT_KEY() {
    KEY key;
    key.chars = "";
    mu_assert("key too short", checkKey(key) == E_KEY_TOO_SHORT);
}

static char* test_NULL_KEY() {
    KEY key;
    key.chars = NULL;
    mu_assert("key is null", checkKey(key) == E_KEY_TOO_SHORT);
}


/*--------------------------- test input ---------------------------*/
static char* test_CORRECT_INPUT() {
   mu_assert("Input passed", checkInput(CORRECT_INPUT) == 0);
}

static char* test_INCORRECT_INPUT_1() {
   mu_assert("Input not passed", checkInput("ABCDEGHIJK!MNOP") == E_MESSAGE_ILLEGAL_CHAR);
}

static char* test_INCORRECT_INPUT_2() {
   mu_assert("Input not passed", checkInput("AaCDEGHIJKCMNOP") == E_MESSAGE_ILLEGAL_CHAR);
}

static char* test_INCORRECT_INPUT_3() {
   mu_assert("Input not passed", checkInput("ABC1EGHIJKEMNOP") == E_MESSAGE_ILLEGAL_CHAR);
}

static char* test_INCORRECT_INPUT_4() {
   mu_assert("Input not passed", checkInput("ABCEEGHIJKEMNOP\n") == E_MESSAGE_ILLEGAL_CHAR);
}

static char* test_NULL_INPUT() {

   mu_assert("Input is null", checkInput(NULL) == 5);
}

/*--------------------------- test encrypt ---------------------------*/
static char* test_CORRECT_ENCRYPT_STATUS() {
  char* output = (char*) malloc(strlen(CORRECT_INPUT) + 1);
  KEY key;
  key.chars = CORRECT_KEY;
  mu_assert("Encrypt successful status", encrypt(key, CORRECT_INPUT, output) == 0);
}

static char* test_CORRECT_ENCRYPT_OUTPUT() {
  char* output = (char*) malloc(strlen(CORRECT_INPUT) + 1);
  KEY key;
  key.chars = CORRECT_KEY;
  encrypt(key, CORRECT_INPUT, output);
  mu_assert("Encrypt successful output", strcmp(output, CORRECT_INPUT_ENCRYPT) == 0);
}

/*--------------------------- test decrypt ---------------------------*/
static char* test_CORRECT_DECRYPT_STATUS() {
  char* output = (char*) malloc(strlen(CORRECT_INPUT_ENCRYPT) + 1);
  KEY key;
  key.chars = CORRECT_KEY;
  mu_assert("Decrypt successful status", decrypt(key, CORRECT_INPUT, output) == 0);
}

static char* test_CORRECT_DECRYPT_OUTPUT() {
  char* output = (char*) malloc(strlen(CORRECT_INPUT_ENCRYPT) + 1);
  KEY key;
  key.chars = CORRECT_KEY;
  decrypt(key, CORRECT_INPUT_ENCRYPT, output);
  mu_assert("Decrypt successful", strcmp(output, CORRECT_INPUT) == 0);
}

static char* allTests() {
    // mu_run_test(test1);
    mu_run_test(test_CORRECT_KEY);
    mu_run_test(test_TOO_SHORT_KEY);
    mu_run_test(test_NULL_KEY);

    mu_run_test(test_CORRECT_INPUT);
    mu_run_test(test_INCORRECT_INPUT_1);
    mu_run_test(test_INCORRECT_INPUT_2);
    mu_run_test(test_INCORRECT_INPUT_3);
    mu_run_test(test_INCORRECT_INPUT_4);
    mu_run_test(test_NULL_INPUT);

    mu_run_test(test_CORRECT_ENCRYPT_STATUS);
    mu_run_test(test_CORRECT_ENCRYPT_OUTPUT);

    mu_run_test(test_CORRECT_DECRYPT_STATUS);
    mu_run_test(test_CORRECT_DECRYPT_OUTPUT);

    return 0;
}

int main() {
    char *result = allTests();

    if (result != 0) printf("%s\n", result);
    else             printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
