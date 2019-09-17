
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Controller.h"

void test()
{
    int errCode = 0;
    student::Controller contrl;

    errCode = contrl.open("../match.txt");
    if (errCode)
    {
        printf("====Controller open() failed .==========\n");
        return;
    }

    errCode = contrl.run("/home/test/5");
    if (errCode)
    {
        printf("====Controller run() failed .==========\n");
        return;
    }
}

int main()
{
    test();
    return 0;
}


