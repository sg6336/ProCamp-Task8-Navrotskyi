#include "pt-1.4/pt.h"

#include <stdio.h>

//struct pt { unsigned short lc; };
//#define PT_THREAD(name_args)  char name_args
//#define PT_BEGIN(pt)          switch(pt->lc) { case 0:
//#define PT_WAIT_UNTIL(pt, c)  pt->lc = __LINE__; case __LINE__: \
//                              if(!(c)) return 0
//#define PT_END(pt)            } pt->lc = 0; return 2
//#define PT_INIT(pt)           pt->lc = 0

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