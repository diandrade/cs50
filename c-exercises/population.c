#include <cs50.h>
#include <stdio.h>

void calculate_years_to_reach_population(int start_size, int end_size);

int main(void)
{
    int start_size;
    int end_size;

    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    calculate_years_to_reach_population(start_size, end_size);
}

void calculate_years_to_reach_population(int start_size, int end_size)
{
    int births;
    int deaths;
    int net_population_change;
    int years_passed;

    years_passed = 0;
    while (start_size < end_size)
    {
        births = start_size / 3;
        deaths = start_size / 4;
        net_population_change = births - deaths;
        start_size += net_population_change;
        years_passed++;
    }

    printf("Years: %d\n", years_passed);
}
