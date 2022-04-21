#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define NO_PG_FRAMES 8
/*
 * @assume
 * here page frames == pageNumbers
 */
struct pageFrame
{
    int referenceBit;
    int pageNumber;
} arr[NO_PG_FRAMES] = {0};

#define CONSTADD (1 << 8)

void getBinary(int n, int i) {
    if (i < 0)
        return;
    getBinary((n>>1), i-1);
    printf("%d", (n & 1));
}

void display()
{
    printf("Refernce bits\tPage_No\n\n");
    for (int i = 0; i < NO_PG_FRAMES; i++)
    {
        getBinary(arr[i].referenceBit, NO_PG_FRAMES);
        
        printf("\t%d\n", arr[i].pageNumber);
    }
}

void findPlaceInsert(int *currPages)
{
    // int currReference[NO_PG_FRAMES] = {0};

    for (int i = 0; i < NO_PG_FRAMES; i++)
    {
        int pgInsert = currPages[i];
        // search
        int pgFrameIdx;
        for (pgFrameIdx = 0; pgFrameIdx < NO_PG_FRAMES; pgFrameIdx++)
        {
            if (arr[pgFrameIdx].pageNumber == pgInsert)
            {
                // Page HIT
                arr[pgFrameIdx].referenceBit |= CONSTADD;
                break;
            }
        }
        if (pgFrameIdx == NO_PG_FRAMES)
        {
            // Page MISS
            // insert in a suitable place
            int minV = INT_MAX, minIdx = 0;
            for (int pgFrameIdx = 0; pgFrameIdx < NO_PG_FRAMES; pgFrameIdx++)
            {
                if (arr[pgFrameIdx].referenceBit < minV)
                {
                    minV = arr[pgFrameIdx].referenceBit;
                    minIdx = pgFrameIdx;
                }
            }
            arr[minIdx].pageNumber = pgInsert;
            arr[minIdx].referenceBit |= CONSTADD;
        }
    }
    // update the values
    for (int i = 0; i < NO_PG_FRAMES; i++)
        arr[i].referenceBit >>= 1;

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
            pagesToInsert[i] = rand() % 10;

        printf("[ ");
        for (int i = 0; i < NO_PG_FRAMES; i++)
            printf("%d ", pagesToInsert[i]);
        printf("]\n");

        findPlaceInsert(pagesToInsert);
        display();
    }
    remove(argv[0]);
    return 0;
}
