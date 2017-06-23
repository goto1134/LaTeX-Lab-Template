#include <stdio.h>
#include <stdlib.h>
#include "pvm3.h"

static const int N = 40000;

void main() {
    struct timeval t;
    int mytid;
    int nproc = 40;
    int numt, msgtype, who, i;
    float result[N], X[N], b;
    int tids[N];
    mytid = pvm_mytid();
    double time1, time2, time;
    gettimeofday(&t, NULL);
    time1 = t.tv_usec;

    numt = pvm_spawn("mas1", (char **) 0, 0, "", nproc, tids);

    if (numt < nproc) {
        for (i = 0; i < numt; i++) {
            pvm_kill(tids[i]);
        }
        pvm_exit();
        exit(1);
    }
    printf("SUCCESSFUL\n");
    pvm_initsend(PvmDataDefault);
    pvm_pkint(&nproc, 1, 1);
    pvm_pkint(tids, nproc, 1);
    pvm_mcast(tids, nproc, 0);
    msgtype = 5;
    for (i = 0; i < nproc; i++) {
        pvm_recv(-1, msgtype);
        pvm_upkfloat(&b, 1, 1);
    }

    gettimeofday(&t, NULL);
    time2 = t.tv_usec;
    time = time2 - time1;
    printf("time: %f", time);
    pvm_exit();
}