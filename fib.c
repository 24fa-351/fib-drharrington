#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static uint64_t *memo = NULL;
static uint64_t memo_size = 0;

typedef uint64_t (*fibonacci_function)(uint64_t, uint64_t *);

void init_memoization(uint64_t size)
{
   memo_size = size;
   memo = (uint64_t *)malloc(sizeof(uint64_t) * (memo_size + 1));
   for (uint64_t i = 0; i <= memo_size; ++i)
   {
      memo[i] = -1; // -1 indicates uncomputed
   }
}

void clear_memoization()
{
   free(memo);
   memo = NULL;
   memo_size = 0;
}

uint64_t fibonacci_wrapper(fibonacci_function function, uint64_t n)
{
   if (n < 0)
   {
      return 0;
   }
   if (n <= memo_size && memo[n] != -1)
   {
      return memo[n]; // Return cached value
   }
   uint64_t result = function(n, memo);
   if (n <= memo_size)
   {
      memo[n] = result; // Cache for future calls
   }
   return result;
}

uint64_t read_file_int(const char *filename)
{
   FILE *openedFile = fopen(filename, "r");
   if (openedFile == NULL)
   {
      printf("Could not open file.\n");
      return -1;
   }

   // Char size 20 should be large enough for integers used
   // in this program, and can be increased if need be.
   char fileNumberString[20];
   if (fgets(fileNumberString, sizeof(fileNumberString), openedFile) != NULL)
   {
      uint64_t fileNumberInt = atoi(fileNumberString);
      fclose(openedFile);
      return fileNumberInt;
   }
   else
   {
      printf("Could not read the file.\n");
      fclose(openedFile);
      return -1;
   }
}

uint64_t fibonacci_recursive(uint64_t n, uint64_t *memo)
{
   if (n <= 1)
   {
      return n;
   }
   if (n > 1 && memo[n] == -1)
   {
      memo[n] = fibonacci_recursive(n - 1, memo) + fibonacci_recursive(n - 2, memo);
   }
   return memo[n];
}

uint64_t fibonacci_iterative(uint64_t n)
{
   if (n == 0)
   {
      return 0;
   }
   if (n == 1)
   {
      return 1;
   }
   uint64_t first = 0, second = 1, fibonacci = 1;
   for (uint64_t i = 2; i <= n; i++)
   {
      fibonacci = first + second;
      first = second;
      second = fibonacci;
   }
   return fibonacci;
}

uint64_t main(int argc, char *argv[])
{
   uint64_t startingNumber = atoi(argv[1]);
   if (startingNumber < 0)
   {
      printf("The Fibonacci number must be a positive integer.\n");
      return 1;
   }

   char fibonacciMethod = argv[2][0];
   if (fibonacciMethod != 'r' && fibonacciMethod != 'i')
   {
      printf("Character must be 'r' for recursive or 'i' for iterative.\n");
      return 1;
   }

   uint64_t fileNumber = read_file_int(argv[3]);
   if (fileNumber == -1)
   {
      printf("Unable to read integer from the file.\n");
      return 1;
   }

   // We subtract 1 to return the fibonacci number at the correct position.
   uint64_t fibonacciNumberPosition = startingNumber + fileNumber - 1;
   init_memoization(fibonacciNumberPosition);

   uint64_t fibonacciResult = 0;
   if (fibonacciMethod == 'r')
   {
      fibonacciResult = fibonacci_wrapper(fibonacci_recursive, fibonacciNumberPosition);
   }
   else
   {
      fibonacciResult = fibonacci_iterative(fibonacciNumberPosition);
   }

   printf("%lu\n", fibonacciResult);
   clear_memoization();
   return 0;
}
