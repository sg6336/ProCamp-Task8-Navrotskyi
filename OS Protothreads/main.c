#include "pt-1.4/pt.h"
#include <stdio.h>

static int counter;
static struct pt pt3;

static PT_THREAD(protothread1(struct pt* pt))
{
    PT_BEGIN(pt);

    while (1) {
        PT_WAIT_UNTIL(pt, counter == 10);
        printf("protothread1. Counter = %d\n", counter);
        counter = 15;
    }

    PT_END(pt);
}

static PT_THREAD(protothread2(struct pt* pt))
{
    PT_BEGIN(pt);

    while (1) {
        PT_WAIT_UNTIL(pt, counter == 20);
        printf("protothread2. Counter = %d\n", counter);
        counter = 0;
    }

    PT_END(pt);
}

static PT_THREAD(protothread3(struct pt* pt))
{
    static struct pt pt1, pt2;

    PT_BEGIN(pt);

    PT_INIT(&pt1);
    PT_INIT(&pt2);

    PT_WAIT_THREAD(pt, protothread1(&pt1) & protothread2(&pt2));

    PT_END(pt);
}

int main(void)
{
    counter = 0;

    while (PT_SCHEDULE(protothread3(&pt3))) {
        counter++;
    }
    return 0;
}
