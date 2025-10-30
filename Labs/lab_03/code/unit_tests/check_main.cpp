#include <check.h>
#include <stdio.h>
#include <stdlib.h>

extern Suite *recursive_suite(void);
extern Suite *iterative_suite(void);

int main(void) {
  int cnt_failed = 0;

  SRunner *runner = srunner_create(recursive_suite());
  srunner_run_all(runner, CK_VERBOSE);
  cnt_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  runner = srunner_create(iterative_suite());
  srunner_run_all(runner, CK_VERBOSE);
  cnt_failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  return (cnt_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}