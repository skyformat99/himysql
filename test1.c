/*
 * Description: 
 *     History: damonyang@tencent.com, 2013/09/24, create
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <error.h>
# include <errno.h>
# include <unistd.h>

# include "himysql.h"

void fail_callback(himysql_t *hm)
{
    fprintf(stderr, "%u\n%s\n%s\n", himysql_errno(hm), himysql_error(hm), hm->sql);
}

int main()
{
    himysql_t *hm = himysql_init("localhost", 0, "test", "root", "shit", NULL, HM_USE_THREAD);
    if (hm == NULL)
        error(1, 0, "himysql_init fail");
    himysql_set_fail_cb(hm, fail_callback);

    /*
    if (himysql(hm, "show databases") != HM_OK)
        error(1, errno, "himysql fail: %s", himysql_error(hm));

    int i;
    for (i = 0; i < hm->num_rows; ++i)
    {
        assert(himysql_fetch_row(hm) == HM_OK);
        printf("%d: %s\n", i, hm->row[0]);
    }

    if (himysql(hm, "insert into t values (%d, %s, %b), (%d, %s, %b)", \
                22, "damonyang", "hello", (size_t)5, \
                23, "marvin", "world", (size_t)5) != HM_OK)
        error(1, errno, "himysql fail: %s", himysql_error(hm));

    himysql_fini(hm);
    */

    int i;
    for (i = 0; i < 300; ++i)
    {
        if (himysql(hm, "insert into time (id, time) values (%d, %ld)", \
                    i + 1, time(NULL)) != HM_OK)
            error(1, errno, "himysql fail: %s", himysql_error(hm));

        usleep(200 * 1000);
    }

    return 0;
}

