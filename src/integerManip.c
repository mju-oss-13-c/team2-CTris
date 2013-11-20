#include"integerManip.h"
#include<stdlib.h>

#define MAX(a, b) (a > b ? a : b)

int countIntegerDigits(int n)
{
	int digits = 0;
	do
	{
		digits++;
		n/=10;
	}while(n != 0);
	return digits;
}
void integerToString(int n, char *str, int strLen)
{
	int i, numLength;
	numLength = countIntegerDigits(n);
	if(n < 0)
		numLength++;

	for(i = MAX(numLength, strLen) - 1; i >= 0; i--)
	{
		if(i < strLen) //se è possibile scrivere
		{
			if(i < numLength) //scriviamo il numero
			{
				//se era un numero != da 0 ed è arrivato a 0 => era un numero negativo ed è il momento di inserire il '-'
				if(n == 0 && numLength > 1)
					str[i] = '-';
				else
					str[i] = (n % 10) + '0';
			}
			else
				str[i] = '\0';
		}

		if(i < numLength) //è possibile ridurre il numero
			n /= 10;
	}
}