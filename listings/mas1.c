#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pvm3.h"

const N = 40000;

void main() {
    int mytid, n;       /* my task id */
    int tids[1000];    /* task ids   */
    int me, i, nproc, master, msgtype;
    float a = 0.0;
    float b = 1.0;
    mytid = pvm_mytid();
    msgtype = 0;
    pvm_recv(-1, msgtype);
    pvm_upkint(&nproc, 1, 1);
    pvm_upkint(tids, nproc, 1);
    n = N / nproc;
    float result[n];
    for (i = 0; i < n; i++) {
        usleep(1);
        result[i] = (float) rand() / RAND_MAX;
        result[i] = result[i] / (n + 1);
    }
    pvm_initsend(PvmDataDefault);
    pvm_pkfloat(&b, 1, 1);
    msgtype = 5;
    master = pvm_parent();
    pvm_send(master, msgtype);

    pvm_exit();
}
