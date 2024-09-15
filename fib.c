#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

uint64_t fibonacci_recursive(uint64_t n)
{
   if (n == 0)
   {
      return 0;
   }
   if (n == 1)
   {
      return 1;
   }
   return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
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

   uint64_t fibonacciResult = 0;
   // We subtract 1 to return the fibonacci number at the correct position.
   uint64_t fibonacciNumberPosition = startingNumber + fileNumber - 1;
   if (fibonacciMethod == 'r')
   {
      fibonacciResult = fibonacci_recursive(fibonacciNumberPosition);
   }
   else
   {
      fibonacciResult = fibonacci_iterative(fibonacciNumberPosition);
   }

   printf("%lu", fibonacciResult);

   return 0;
}
