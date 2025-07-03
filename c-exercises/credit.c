#include <cs50.h>
#include <math.h>
#include <stdio.h>

#define AMEX_PREFIX_ONE 34
#define AMEX_PREFIX_TWO 37
#define AMEX_LENGTH 15
#define MASTERCARD_PREFIX_ONE 51
#define MASTERCARD_PREFIX_TWO 52
#define MASTERCARD_PREFIX_THREE 53
#define MASTERCARD_PREFIX_FOUR 54
#define MASTERCARD_PREFIX_FIVE 55
#define MASTERCARD_LENGTH 16
#define VISA_PREFIX_DIGIT 4
#define VISA_LENGTH_ONE 13
#define VISA_LENGTH_TWO 16
#define NUM_LEADING_DIGITS_TO_EXTRACT 2

int count_digits(long long user_credit_card_number);
int extract_leading_digits(long long user_credit_card_number);
void validate_credit_card(long long user_credit_card_number);
bool checksum(long long user_credit_card_number);

int main(void)
{
    long user_credit_card_number;

    do
    {
        user_credit_card_number = get_long("Insert some credit card number: ");
    }
    while (user_credit_card_number < 0);

    validate_credit_card(user_credit_card_number);
}

int count_digits(long long user_credit_card_number)
{
    int counter;

    counter = 0;
    while (user_credit_card_number != 0)
    {
        user_credit_card_number /= 10;
        counter++;
    }
    return counter;
}

int extract_leading_digits(long long user_credit_card_number)
{
    int counter;
    long masked_digits_count =
        count_digits(user_credit_card_number) - NUM_LEADING_DIGITS_TO_EXTRACT;

    counter = 0;
    while (counter < masked_digits_count)
    {
        user_credit_card_number /= 10;
        counter++;
    }
    return user_credit_card_number;
}

void validate_credit_card(long long user_credit_card_number)
{
    int first_two_numbers;
    int credit_card_length;

    first_two_numbers = extract_leading_digits(user_credit_card_number);
    credit_card_length = count_digits(user_credit_card_number);

    if ((first_two_numbers == AMEX_PREFIX_ONE || first_two_numbers == AMEX_PREFIX_TWO) &&
        credit_card_length == AMEX_LENGTH)
    {
        if (checksum(user_credit_card_number))
        {
            printf("AMEX\n");
            return;
        }
    }

    if ((first_two_numbers == MASTERCARD_PREFIX_ONE || first_two_numbers == MASTERCARD_PREFIX_TWO ||
         first_two_numbers == MASTERCARD_PREFIX_THREE ||
         first_two_numbers == MASTERCARD_PREFIX_FOUR ||
         first_two_numbers == MASTERCARD_PREFIX_FIVE) &&
        credit_card_length == MASTERCARD_LENGTH)
    {
        if (checksum(user_credit_card_number))
        {
            printf("MASTERCARD\n");
            return;
        }
    }

    if (first_two_numbers / 10 == VISA_PREFIX_DIGIT &&
        (credit_card_length == VISA_LENGTH_ONE || credit_card_length == VISA_LENGTH_TWO))
    {
        if (checksum(user_credit_card_number))
        {
            printf("VISA\n");
            return;
        }
    }
    printf("INVALID\n");
}

bool checksum(long long user_credit_card_number)
{
    long long digit_position_multiplier;
    long shifted_credit_card_number;
    int current_number_position;
    int penultimate_digit_sum;
    int credit_card_length;
    int extracted_digit;
    int last_digit_sum;
    int validation_sum;
    int units_digit;
    int tens_digit;
    int exponent;
    int counter;

    counter = 1;
    penultimate_digit_sum = 0;
    credit_card_length = count_digits(user_credit_card_number);
    while (counter <= credit_card_length)
    {
        current_number_position = credit_card_length - counter;
        exponent = credit_card_length - current_number_position;
        digit_position_multiplier = pow(10, exponent);
        shifted_credit_card_number = user_credit_card_number / digit_position_multiplier;
        extracted_digit = shifted_credit_card_number % 10;
        extracted_digit *= 2;
        if (extracted_digit == 10 || extracted_digit / 10 != 0)
        {
            tens_digit = extracted_digit / 10;
            units_digit = extracted_digit % 10;
            penultimate_digit_sum += (tens_digit + units_digit);
        }
        else
        {
            penultimate_digit_sum += extracted_digit;
        }
        counter += 2;
    }

    counter = 0;
    last_digit_sum = 0;
    while (counter <= credit_card_length)
    {
        current_number_position = credit_card_length - counter;
        exponent = credit_card_length - current_number_position;
        digit_position_multiplier = pow(10, exponent);
        shifted_credit_card_number = user_credit_card_number / digit_position_multiplier;
        extracted_digit = shifted_credit_card_number % 10;
        last_digit_sum += extracted_digit;
        counter += 2;
    }

    validation_sum = last_digit_sum + penultimate_digit_sum;
    if (validation_sum % 10 == 0)
    {
        return true;
    }
    return false;
}
