#include <cs50.h>
#include <stdio.h>

#define QUARTER_VALUE 25
#define DIME_VALUE 10
#define NICKEL_VALUE 5
#define PENNY_VALUE 1

int calculateCoins(int c);

int main(void)
{
    float dollarsToBeConverted;
    int totalAmountOfCoins;

    do
    {
        dollarsToBeConverted = get_float("Change owed: ");
    }
    while (dollarsToBeConverted < 0);

    totalAmountOfCoins = dollarsToBeConverted * 100;
    printf("%d\n", calculateCoins(totalAmountOfCoins));
}

int calculateCoins(int c)
{
    int quarters, dimes, nickels, pennies;

    quarters = 0;
    while (c >= QUARTER_VALUE)
    {
        c -= QUARTER_VALUE;
        quarters++;
    }

    dimes = 0;
    while (c >= DIME_VALUE)
    {
        c -= DIME_VALUE;
        dimes++;
    }

    nickels = 0;
    while (c >= NICKEL_VALUE)
    {
        c -= NICKEL_VALUE;
        nickels++;
    }

    pennies = 0;
    while (c >= PENNY_VALUE)
    {
        c -= PENNY_VALUE;
        pennies++;
    }

    return quarters + dimes + nickels + pennies;
}
