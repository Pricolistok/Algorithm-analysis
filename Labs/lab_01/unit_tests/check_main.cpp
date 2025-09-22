#include <check.h>
#include <stdlib.h>
#include <stdio.h>

extern Suite *simple(void);
extern Suite *vinograd(void);
extern Suite *vinograd_upd(void);

int main(void)
{
    int cnt_failed = 0;

    SRunner *runner = srunner_create(simple());
    srunner_run_all(runner, CK_VERBOSE);
    cnt_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    runner = srunner_create(vinograd());
    srunner_run_all(runner, CK_VERBOSE);
    cnt_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    runner = srunner_create(vinograd_upd());
    srunner_run_all(runner, CK_VERBOSE);
    cnt_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (cnt_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
