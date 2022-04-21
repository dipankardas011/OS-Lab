#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NO_PG_FRAMES 8
/*
 * @assume
 * here page frames == pageNumbers
 */
struct pageFrame
{
    unsigned char referenceBit;
    int pageNumber;
} arr[NO_PG_FRAMES] = {0};

#define CONSTADD (1 << 8)

void getBinary(unsigned char n)
{
    while (n > 0)
    {
        printf("%d", n & 1);
        n >>= 1;
    }
    printf("\t");
}

void display()
{
    printf("Refernce bits\tPage_No\n\n");
    for (int i = 0; i < NO_PG_FRAMES; i++)
    {
        getBinary(arr[i].referenceBit);
        printf("%d\n", arr[i].pageNumber);
    }
}

void findPlaceInsert(int *currPages)
{
    unsigned char currReference[NO_PG_FRAMES] = {0};

    for (int i = 0; i < NO_PG_FRAMES; i++)
    {
        int pgInsert = currPages[i];
        // search
        int pgFrameIdx;
        for (pgFrameIdx = 0; pgFrameIdx < NO_PG_FRAMES; pgFrameIdx++)
        {
            if (arr[pgFrameIdx].pageNumber == pgInsert)
            {
                // present
                currReference[pgFrameIdx] = 1;
                break;
            }
        }
        if (pgFrameIdx == NO_PG_FRAMES)
        {
            // notfound do nothing
            // insert in a suitable place
            int minV = (1 << 8) + 1, minIdx = 0;
            for (int pgFrameIdx = 0; pgFrameIdx < NO_PG_FRAMES; pgFrameIdx++)
            {
                if (arr[pgFrameIdx].referenceBit < minV)
                {
                    minV = arr[pgFrameIdx].referenceBit;
                    minIdx = pgFrameIdx;
                }
            }
            arr[minIdx].pageNumber = pgInsert;
            currReference[minIdx] = 1;
        }
    }
    // update the values
    // first left shift then add (1 << 8) * currReference[i]
    for (int i = 0; i < NO_PG_FRAMES; i++)
    {
        unsigned char temp = currReference[i];

        arr[i].referenceBit = ((arr[i].referenceBit) >> 1) | (CONSTADD * currReference[i]);

        currReference[i] = 0;
    }
}

void initPageNumbers()
{
    for (int i = 0; i < NO_PG_FRAMES; i++)
        arr[i].pageNumber = -1;
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    initPageNumbers();
    int Tn = 0;
    printf("Enter the number of timeDiff: ");
    scanf("%d", &Tn);

    while (Tn-- > 0)
    {
        int pagesToInsert[NO_PG_FRAMES] = {0};
        for (int i = 0; i < NO_PG_FRAMES; i++)
        {
            pagesToInsert[i] = rand() % 100;
        }

        findPlaceInsert(pagesToInsert);
        display();
    }
    return 0;
}
