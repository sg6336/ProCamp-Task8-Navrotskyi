
#include ".\pt-1.4\pt.h"

static int counter;
static struct pt example_pt;

struct pt pt;

static
PT_THREAD(example(struct pt* pt))
{
    PT_BEGIN(pt);

    while (1) {
        //pt->lc = 15; case 15: if (!(counter == 1000)) return 0;
        PT_WAIT_UNTIL(pt, counter == 1000);
        printf("Threshold reached. Counter = %d\n", counter);
        counter = 0;
    }

    PT_END(pt);
}

int main(void)
{
    counter = 0;
    PT_INIT(&example_pt);

    while (1) {
        example(&example_pt);
        counter++;
    }
    return 0;
}