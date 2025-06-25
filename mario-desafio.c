#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
        printf("\n");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {

        // The whitespace behind the pyramid
        for (int k = 0; k < height - i - 1; k++)
        {
            printf(" ");
        }

        // First pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // Two whitespaces
        printf("  ");

        // Second pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // Go to the next line
        printf("\n");
    }
}
