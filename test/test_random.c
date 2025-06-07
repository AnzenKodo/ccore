/* definition for RAND_MAX constant */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DEF_RANDOM_COUNT 10000
/* random number storage */
static unsigned long long g_seed;

/**
 * Used to seed the generator
 * @param seed initializing "generator"
 */
void fast_srand(unsigned int seed)
{
    g_seed = seed;
}

/**
 * Compute a pseudo random integer. Output value in range [0, RAND_MAX]
 * @return pseudo random integer
 */
int fast_rand()
{
    g_seed = (214013*g_seed+2531011);
    return (g_seed>>32)&RAND_MAX;
}
int cStrToInt(const char* sz)
{
    char* pEnd;
    if(sz==NULL)    {
        return 0;
    }
    return strtol(sz,&pEnd, 10);
}

int main(int argc, char* argv[])  {
    int i, n;
    int randomCount = DEF_RANDOM_COUNT;
    int randomType = 0;
    int dontPrint = 0;
    for(i=1; i<argc; i++)   {
        if(argv[i][0]=='-') {
            switch(argv[i][1])  {
                case 't':/* type */
                    if(i+1<argc)    {
                        randomType = cStrToInt(argv[++i]);
                    }
                    break;
                case 'c':
                    if(i+1<argc)    {
                        randomCount = cStrToInt(argv[++i]);
                    }
                    break;
                case 'p':
                    dontPrint = 1;
                    break;
            }
        }
        else    {
            randomCount = cStrToInt(argv[i]);
        }
    }
    if(randomCount<0)   {
        randomCount = DEF_RANDOM_COUNT;
    }
    switch(randomType)  {
        case 2:
            srandom(time(NULL));
            break;
        case 1:
            srand(time(NULL));
            break;
        default:
            fast_srand(time(NULL));
            break;
    }
    for(i=0; i<randomCount; i++)    {
        switch(randomType)  {
            case 3:
                n = arc4random();
                break;
            case 2:
                n = random();
                break;
            case 1:
                n = rand();
                break;
            default:
                n = fast_rand();
                break;
        }
        if(dontPrint)   {
            continue;
        }
        printf("%d\n",fast_rand());
    }
    //             fast_srand(time(NULL));
    // for (i=0; i < 10; i++) fast_rand();
    //     printf("%d\n",fast_rand());
}

