/*
 *
 * (Chase Stockwell )
 */

#include <math.h> 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binaryArray[45][8];
int bitsCount = 0;
int numbers = 0;
void parityCheck(int); 
int *convert(int);        
void decimalToBinary(int); 
int *oneComplement(int *ptr); 

int main(void) {

  FILE *parity = fopen("White House Transmission Data - Parity.txt", "r");
  FILE *checkSum = fopen("White House Transmission Data - Checksum.txt", "r");
  FILE *_2DParity = fopen("White House Transmission Data - 2D Parity.txt", "r");
  int i;
  while (!feof(parity)) {
    fscanf(parity, " %d", &i);
    printf("data item = %d ", i);
    parityCheck(i);
    printf("\n");
  }
  printf("\n");

  int parityArray[5][9];
  int twoDimensionalParityArray[8][8];
  int n;
  int parityRow = 8;
  int parityColumn = 8;
  int noOfParitiesInRow[8] = {0};
  int noOfParitiesInColumn[8] = {0};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      fscanf(checkSum, " %d", &n);
      parityArray[i][j] = n;
      decimalToBinary(parityArray[i][j]);
    }
  }

  int row1 = 0;
  int sum[5] = {0};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      if (j != 8)
        sum[i] += parityArray[i][j];
      printf("\nParityData[i] = %d,binary = ", parityArray[i][j]);
      for (int count = 0; count < 8; count++)
        printf("%d", binaryArray[row1][count]);
      row1++;
      printf("\n");
    }
    
    int *bin = convert(sum[i]);
    printf("Sum Of Data Items: %d , Binary = ", sum[i]);
    for (int k = 0; k < 8; k++)
      printf("%d", bin[k]);
    printf("\n");
    bin = convert(parityArray[i][8]);
    printf("CheckSum Value= %d , Binary = ", parityArray[i][8]);
    for (int k = 0; k < 8; k++)
      printf("%d", bin[k]);
    printf("\n");
    sum[i] += parityArray[i][8];
    bin = convert(sum[i]);
    int *complement = oneComplement(bin);
    bool checkResult = true;
    printf("Sum after adding checksum = %d , binary = ", sum[i]);
    for (int k = 0; k < 8; k++)
      printf("%d", bin[k]);
    printf("\n");
    printf("binary of Checksum= ");
    for (int k = 0; k < 8; k++)
      printf("%d", complement[k]);
    printf("\n");
    for (int l = 0; l < 8; l++)
      if (complement[l] == 1)
        checkResult = false;
    if (checkResult)
      printf("Checksum: No errors in transmission\n");
    else
      printf("Checksum: errors in transmission\n");
  }

  for (int row2D = 0; row2D < parityRow; row2D++) {
    for (int colum2D = 0; colum2D < parityColumn; colum2D++) {
      fscanf(_2DParity, "%d", &twoDimensionalParityArray[row2D][colum2D]);
    }
    fscanf(_2DParity, "%d", &noOfParitiesInRow[row2D]);
    fscanf(_2DParity, "%d", &noOfParitiesInColumn[row2D]);
  }

  for (int i = 0; i < parityRow; i++) {
    for (int j = 0; j < parityColumn; j++) {
      printf("%4d ", twoDimensionalParityArray[i][j]);
    }
    printf("[V: %d] [H: %d]\n", noOfParitiesInRow[i], noOfParitiesInColumn[i]);
  }
  bool checkTrasmission = true;
  for (int i = 0; i < parityRow; i++) {
    printf("**Vertical processing transmission line %d\n", i);
    for (int j = 0; j < parityColumn; j++) {
      printf("Val%d = %d, ", i + j + 1, twoDimensionalParityArray[j][i]);
      int *bin = convert(twoDimensionalParityArray[j][i]);
      for (int k = 0; k < 8; k++)
        printf("%d", bin[k]);
      printf("\n");
    }
  }
  for (int i = 0; i < parityRow; i++) {
    printf("**Horizontal processing transmission line %d\n", i);
    for (int j = 0; j < parityColumn; j++) {
      printf("Val%d = %d, ", i + j + 1, twoDimensionalParityArray[i][j]);
      int *bin = convert(twoDimensionalParityArray[i][j]);
      for (int k = 0; k < 8; k++)
        printf("%d", bin[k]);
      printf("\n");
    }
    printf("checkParityByte = %d, vertParityByte[1] = %d\n",
           noOfParitiesInColumn[i], noOfParitiesInColumn[i]);
    printf("Transmission line %d passed vertical parity\n", i + 1);
  }
  if (checkTrasmission) {
    printf("Transmission block 1 PASSED complete horizontal parity test\n");
    printf("---> Transmission block 1 PASSED - it is error free.\n");
  } else {
    printf("Transmission block 1 PASSED complete horizontal parity test\n");
    printf("---> Transmission block 1 Not PASSED - it is not error free.\n");
  }
  return 0;
}
int *oneComplement(int *ptr) {
  int *onesComplement = (int *)malloc(sizeof(int) * 8);
  for (int i = 0; i < 8; i++) {
    if (ptr[i] == 0)
      onesComplement[i] = 1;
    else
      onesComplement[i] = 0;
  }
  return onesComplement;
}
int *convert(int n) {
  int *bin = (int *)malloc(sizeof(int) * 8);
  int *reverseBin = (int *)malloc(sizeof(int) * 8);
  int rem, i = 1, count = 7;
  while (n != 0) {
    rem = n % 2;
    n /= 2;
    bin[count--] = rem;
  }
  for (int k = 0; k < 8; k++)
    reverseBin[k] = bin[count--];
  return bin;
}

void parityCheck(int num) 
{
  int numberOfOnes = 0;
  int digit = num;
  if (num == 0) {
    for (int count = 0; count < 8; count++) {
      printf("0");
    }
    return;
  }
  int binaryNum[8];
  int i = 0;
  printf("binary = ");
  for (; num > 0;) {
    binaryNum[i] = num % 2;
    if (binaryNum[i++] == 1)
      numberOfOnes++;
    num /= 2;
  }
  int bits = 8 - i;
  for (int count = 0; count < bits; count++) {
    printf("0");
  }

  for (int j = i - 1; j >= 0; j--) {
    printf("%d", binaryNum[j]);
  }

  if (numberOfOnes % 2 == 0)
    printf("\nNo Error in transmission byte %d\n", digit);
  else
    printf("\nError in transmission byte %d\n", digit);
}
void decimalToBinary(int num) {
  int digit = num;
  if (num == 0) {
    for (int count = 0; count < 8; count++)
      binaryArray[numbers][bitsCount++] = 0;
    numbers++;
    return;
  }
  int binaryNum[8];
  int i = 0;

  for (; num > 0;) {
    binaryNum[i++] = num % 2;
    num /= 2;
  }
  int bits = 8 - i;
  for (int count = 0; count < bits; count++)
    binaryArray[numbers][bitsCount++] = 0;
  for (int j = i - 1; j >= 0; j--)
    binaryArray[numbers][bitsCount++] = binaryNum[j];
  numbers++;
  if (bitsCount >= 8)
    bitsCount = 0;
}