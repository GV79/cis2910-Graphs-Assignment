#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*****************************
CIS2910 Assignment Graphs
Author: Giavinh Lam
Assumptions: Proper format of
input text file, length of
a row < 100 characters
Results: Only the second pair
of graphs had the same sorted
ascending degree sequence
*****************************/

int compare(const void * a, const void * b); // compare function for qsort
int compareArrays(int array[20], int arrayTwo[20]); // comparing degree sequences
void initialize(int array[20]); // initializing it, so that qsort doesn't have unused indexes of 0 appearing in beginning
int returnDegree(char input[100]); // returns degree based on how many 1s there are in that row of the matrix

int main(int argc, char ** argv)
{
    if (argc != 2) // In command line, when running, must also include input file as an argument
    {
        printf("Error - Not enough arguments. Must specify input file.\n");
        exit(0);
    }

    FILE * data;
    int degreeOne[20]; // assume n <= 20 (# of vertices)
    int degreeTwo[20]; //two int arrays as we are comparing two graphs
    char dataText[100];
    int length = 0;
    int i = 0;
    int counter; // once you compare two graphs, reset

    data = fopen(argv[1], "r");

    while (fgets(dataText, 100, data))
    {
        if (strchr(dataText, ' ') == NULL)
        {
            length = atoi(dataText);
            if (counter == 0)
            {
                initialize(degreeOne);
                initialize(degreeTwo);
            }

            counter++;
            i = 0;
        }
        else
        {
            if (counter == 1)
            {
                degreeOne[i] = returnDegree(dataText);
                i++;
            }
            else
            {
                degreeTwo[i] = returnDegree(dataText);
                i++;
            }

            if (i == length && counter == 2) // compare two graphs now
            {
                qsort(degreeOne, 20, sizeof(int), compare);
                qsort(degreeTwo, 20, sizeof(int), compare);

                printf("Degree seq for G1: ");
                for (i = 0; i < length; i++)
                {
                    printf("%d ", degreeOne[i]);
                }
                printf("\nDegree seq for G2: ");

                for (i = 0; i < length; i++)
                {
                    printf("%d ", degreeTwo[i]);
                }

                if (compareArrays(degreeOne, degreeTwo) == 1)
                    printf("\nThe graphs have the same degree sequence. Isomorphism is possible.\n");
                else
                    printf("\nThe graphs do NOT have the same degree sequence. They are not isomorphic.\n");
                printf("\n");
                initialize(degreeOne); // reset for next pair of graphs
                initialize(degreeTwo);
                counter = 0;
                i = 0;
            }

        }
    }
    return 0;
}

int compare(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int compareArrays(int array[20], int arrayTwo[20])
{
    int p;
    for (p = 0; p < 20; p++)
    {
        if (array[p] != arrayTwo[p])
        {
            return 0;
        }
    }
    return 1;
}

void initialize(int array[20])
{
    int k;
    for (k = 0; k < 20; k++)
    {
        array[k] = 90; //Basically ignore indexes during sorting that don't matter
    }
}

int returnDegree(char input[100])
{
    int totalDegree = 0;
    int j = 0;

    for (j = 0; j < strlen(input); j++)
    {
        if (input[j] == '1')
        {
            totalDegree++;
        }
    }
    return totalDegree;
}
