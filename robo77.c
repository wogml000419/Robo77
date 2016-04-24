#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MUL  -20
#define REV  -15
#define EMP  -1

void putUI(void)
{
	puts(" ------------------------------------------------- ");
	puts("|  -----   -----   ----    -----  |-----| |-----| |");
	puts("| |     | |     | |    |  |     | |    |  |    |  |");
	puts("| |_____| |     | |-----  |     |     |       |   |");
	puts("| |  |    |     | |     | |     |    |       |    |");
	puts("| |    |  |_____| |_____| |_____|    |       |    |");
	puts("|_________________________________________________|");
	puts("|     1.플레이                         2.종료     |");
	puts("|_________________________________________________|");
}
void printGameUI(int sum, int card)
{
	printf("|-----합계:%d", sum);
	if (card >= 0)
		printf("(+%d)-----|\n\n", card);
	else if (card == -10)
		printf("(%d)-----|\n\n", card);
	else if (card == REV)
		printf("(R)-----| \n\n");
	else if (card == MUL)
		printf("(x2)-----| \n\n");
	else
		printf("(%d)-----| \n\n", card);
}
void printMyCard(int arr[])
{
	int i;
	puts(" 1  2  3  4  5 ");
	for (i = 0; i < 5; i++)
	{
		if (arr[i] < 0)
		{
			switch (arr[i])
			{
			case MUL:
				printf("%2s ", "x2");
				break;
			case REV:
				printf("%2s ", "R");
				break;
			case -10:
				printf("%2d ", arr[i]);
				break;
			}
		}
		else
			printf("%2d ", arr[i]);
	}
	putchar('\n');
}
void getCard(int card[], int *num)
{
	int n;
	
	while (1)
	{
		n = rand() % 69;
		if (card[n] != EMP)
		{
			*num = card[n];
			card[n] = EMP;
			return;
		}
	}
}
void getCards(int card[], int arr[])
{
	int i;
	for (i = 0; i < 5; i++)
		getCard(card, &arr[i]);
}
int isItOver(int sum)
{
	if (sum <= 0)
		return 1;
	else if ((sum % 11 == 0) || (sum >= 77))
		return -1;
	else
		return 1;
}
void returnCard(int card[], int num)
{
	int i=0;
	while (1)
	{
		if (card[i] == EMP)
		{
			card[i] = num;
			return;
		}
		i++;
	}
}
int drawCard(int num, int *sum)
{
	if (num >= 0)
		*sum += num;
	else
	{
		switch (num)
		{
		case -10:
			*sum += -10;
			break;
		case MUL:
			return MUL;
			break;
		case REV:
			
			break;
		}
	}
	return 0;
}

int myTurn(int myCard[], int *sum, int cardPack[])
{
	int n, returnVal = 0;
	printMyCard(myCard);
	scanf("%d", &n);
	returnVal = drawCard(myCard[n - 1], sum);
	printGameUI(*sum, myCard[n-1]);
	returnCard(cardPack, myCard[n - 1]);
	getCard(cardPack, &myCard[n-1]);

	/*for (n = 0; n < 5; n++)
		printf("%d ", myCard[n]);
	printf("sum: %d \n", *sum);*/
	return returnVal;
}
int AI(int sum, int card[])
{
	int i, n, len = 0;
	int able[5];

	for (i = 0; i < 5; i++)
		if ((card[i] > 0) && (isItOver(sum + card[i])==1))
			able[len++] = i;
	if (len == 0)
		for (i = 0; i < 5; i++)
		{
			if (card[i] <= 0)
			{
				if (card[i] != -10)
					able[len++] = i;
				else if ((card[i] == -10) && (isItOver(sum - 10) == 1))
					able[len++] = i;
				else;
			}
		}
	if (len == 0)
		return (rand() % 5);
	n = able[rand() % len];
	return n;
}
int AITurn(int AICard[], int *sum, int cardPack[])
{
	int n, returnVal = 0;
	n = AI(*sum, AICard); 
	returnVal = drawCard(AICard[n], sum);
	//printf("/n = %d/ \n", n);
	printGameUI(*sum, AICard[n]);
	returnCard(cardPack, AICard[n]);
	getCard(cardPack, &AICard[n]);

	/*for (n = 0; n < 5; n++)
		printf("/%d/ ", AICard[n]);
	printf("/sum: %d/ \n", *sum);*/
	return returnVal;
}


int gamePlay(void)
{
	int cardPack[] = {2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 
		5 , 5 , 5 , 6 , 6 , 6 , 7 , 7 , 7 , 8 , 
		8 , 8 , 9 , 9 , 9 , 3,  3,  3, 4,  4,
		5,  5,  6,  6,  7,  7,  8,  9, 10,  10,
		10, 10, 10, 12, 22, 33, 44, 55, 66, 76, 
		MUL,MUL,MUL,MUL,MUL,REV,REV,REV,REV,REV,
		-10.-10,-10,-10,-10, 0, 0 , 0 , 0  ,0 };
	int myCard[5];
	int AICard[5];
	int n = 0;
	int sum = 0;
	int trig;

	getCards(cardPack, myCard);
	getCards(cardPack, AICard);
	printGameUI(sum, n);
	
	do
	{
		trig = myTurn(myCard, &sum, cardPack);
		if (isItOver(sum) == -1)
			return 0;

		if (trig == MUL)
			AITurn(AICard, &sum, cardPack);
		trig = AITurn(AICard, &sum, cardPack);
		if (isItOver(sum) == -1)
			return 1;
		if (trig == MUL)
			myTurn(myCard, &sum, cardPack);
	} while (1);
}
void endGame(int i)
{
	if (i==1)
	{
		puts(" --------------------------------------------------------- ");
		puts("| |     | -------  ------ -------  -----   -----  |     | |");
		puts("| |     |    |    |          |    |     | |     |  |   |  |");
		puts("|  |   |     |    |          |    |     | |_____|   | |   |");
		puts("|   | |      |    |          |    |     | |  |       |    |");
		puts("|    |    ___|___ |______    |    |_____| |    |     |    |");
		puts("|_________________________________________________________|");
	}
	else
	{
		puts(" -------------------------------------------------------------------- ");
		puts("|  -----     |    ||   ||  ------     -----  |     |  ------  -----  |");
		puts("| |         | |   | | | | |          |     | |     | |       |     | |");
		puts("| |   ---  |___|  |  |  | |------    |     |  |   |  |------ |_____| |");
		puts("| |     | |     | |     | |          |     |   | |   |       |  |    |");
		puts("| |_____| |     | |     | |______    |_____|    |    |______ |    |  |");
		puts("|____________________________________________________________________|");
	}
}

int main(void)
{
	int swch;
	srand((int)time(NULL));

while (1)
{
	putUI();
	scanf("%d", &swch);

	switch (swch)
	{
	case 1:
		endGame(gamePlay());
		continue;
	case 2:
		return 0;
	default:
		continue;
	}
}

}