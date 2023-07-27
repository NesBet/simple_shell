#include <stdio.h>

/**
 * sum_of_evens - Finds the sum of all even numbers between 1 and n.
 * @n: Positive integer.
 *
 * Return: The sum of all the bounded even numbers.
 */
int sum_of_evens(int n)
{
    int total = 0;

    for (int i = 2; i <= n; i += 2)
    {
        total += i;
    }

    return total;
}

int main(void)
{
    int num;
    
    printf("Please enter a positive integer: ");
    scanf("%d", &num);

    if (num <= 0)
    {
        printf("Only positive integers are allowed.\n");
        return 1;
    }

    int result = sum_of_evens(num);
    printf("The sum of even numbers from 1 to %d is: %d\n", num, result);

    return 0;
}
