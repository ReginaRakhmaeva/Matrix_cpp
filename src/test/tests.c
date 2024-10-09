#include "tests.h"

#include <stdio.h>

int main(void) {
  int fail = 0;

  Suite *s[] = {s21_matrix_oop_test(), NULL};

  for (int i = 0; s[i] != NULL; ++i) {
    SRunner *runner = srunner_create(s[i]);
    srunner_run_all(runner, CK_NORMAL);
    fail += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  printf("FAIL: %d\n", fail);
  return 0;
}