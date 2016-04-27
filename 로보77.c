#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MUL  -20
#define REV  -15
#define EMP  -1

void putUI(void)
{
	/*
	���� ȭ�� ���
	*/
	puts(" ------------------------------------------------- ");
	puts("|  -----   -----   ----    -----  |-----| |-----| |");
	puts("| |     | |     | |    |  |     | |    |  |    |  |");
	puts("| |_____| |     | |-----  |     |     |       |   |");
	puts("| |  |    |     | |     | |     |    |       |    |");
	puts("| |    |  |_____| |_____| |_____|    |       |    |");
	puts("|_________________________________________________|");
	puts("|     1.�÷���                         2.����     |");
	puts("|_________________________________________________|");
}
void printGameUI(int sum, int card)
{
	/*
	�հ�� ���������� �� ī�带 ����ϴ� �Լ�

	�հ�(sum)�� ���������� �� ī��(card)�� ���ڷ� ����
	*/
	printf("|-----�հ�:%d", sum);
	if (card >= 0)							//�Ϲ����� ����ī���� ��
		printf("(+%d)-----|\n\n", card);	//+(����) ���·� ���
	else if (card == -10)					//-10�� ��
		printf("(%d)-----|\n\n", card);		//-10�� ���·� ���
	else if (card == REV)					//REV�� ��
		printf("(R)-----| \n\n");			//R�� ���
	else if (card == MUL)					//x2�� ��
		printf("(x2)-----| \n\n");			//x2�� ���
	else									//�� �� ������Ȳ
		printf("(%d)-----| \n\n", card);	//�������·� ���
}
void printMyCard(int arr[])
{
	/*
	���� ī�带 ����ϴ� �Լ�

	ī�� �迭(arr)�� ���ڷ� ����
	*/
	int i;
	puts(" 1  2  3  4  5 ");
	for (i = 0; i < 5; i++)
	{
		if (arr[i] < 0)					//arr[i]�� Ư��ī���� ���
		{
			switch (arr[i])
			{
			case MUL:					//x2�� ��
				printf("%2s ", "x2");
				break;
			case REV:					//REV�� ��
				printf("%2s ", "R");
				break;
			case -10:					//-10�� ��
				printf("%3d", arr[i]);  //-10�� ��ĭ �����ϹǷ� �ڸ� ���� ����
				break;
			}
		}
		else							//�Ϲ� ����ī���� ��
			printf("%2d ", arr[i]);
	}
	putchar('\n');
}
void getCard(int card[], int *num)
{
	/*
	ī���ѿ��� ī�带 �ϳ� �̴� �Լ�

	ī���� �迭(card)�� ī�� ������ ������(*num)�� ���ڷ� ����
	*/
	int n;
	
	while (1)
	{
		n = rand() % 69;				//0~69 ���̿��� ���� ����
		if (card[n] != EMP)				//card[n]�� ������� ������
		{
			*num = card[n];				//ī�� ������ card[n] �Ҵ�
			card[n] = EMP;				//card[n]�� ���
			return;
		}
	}									//card[n]�� ��������� ��� �ݺ�
}
void getCards(int card[], int arr[])
{
	/*
	ī�� �ټ����� ��� �Լ�

	ī���� �迭(card)�� �÷��̾��� ī�� �迭(arr)�� ���ڷ� ����
	*/
	int i;
	for (i = 0; i < 5; i++)
		getCard(card, &arr[i]);			//�ټ� �� getCard() ȣ��
}
int isItOver(int sum)			
{
	/*
	������ �������� �Ǵ��ϴ� �Լ�

	�հ踦 ���ڷ� ����
	�Ϲ������δ� 1 ��ȯ
	������ ���� ���� -1 ��ȯ
	*/
	if (sum <= 0)						//�հ谡 0 ���ϸ�
		return 1;						//������ ��ȯ
	else if ((sum % 11 == 0) || (sum >= 77))//�հ谡 11�� ����̰ų� 77 �̻��̸�
		return -1;						//���� ��
	else								//�� �ܴ�
		return 1;						//������ ��ȯ
}
void returnCard(int card[], int num)
{
	/*
	�÷��̾ �� ī�带 ī���ѿ� �����ִ� �Լ�

	ī���� �迭(card)�� �� ī��(num)�� ���ڷ� ����
	*/
	int i=0;
	while (1)
	{
		if (card[i] == EMP)				//card[i]�� ���������
		{
			card[i] = num;				//card[i]�� �� ī�带 ������
			return;
		}
		i++;							//���ѹݺ�
	}
}
int drawCard(int num, int *sum)
{
	/*
	ī�带 ���� �Լ�

	���� ī��(num)�� �հ��� ������(*sum)�� ���ڷ� ���� 
	�Ϲ� ī��� 0 ��ȯ
	x2�� MUL ��ȯ
	REV�� REV ��ȯ
	*/
	if (num >= 0)						//�Ϲ� ī���� ���
		*sum += num;					//�հ迡 �´� ī�带 ����
	else								//Ư�� ī���� ���
	{
		switch (num)
		{
		case -10:						//-10�� ��
			*sum += -10;				//-10�� ����
			break;
		case MUL:						//x2�� ��
			return MUL;					//x2 ����
			break;
		case REV:						//REV�� ��
										//REV ����(�߰�����)
			break;
		}
	}
	return 0;							//�� �ܴ� 0 ����
}

int myTurn(int myCard[], int *sum, int cardPack[])
{
	/*
	���� ���� �����ϴ� �Լ�

	���� ī��(myCard)�� �հ� ������ ������(*sum), ī����(cardPack)�� ���ڷ� ����
	�Ϲ� ī��� 0 ��ȯ
	x2�� MUL ��ȯ
	REV�� REV ��ȯ
	*/
	int n, returnVal = 0;
	printMyCard(myCard);				//���� ī�带 ���
	scanf("%d", &n);					//�� ī�带 ����

	if (n < 1 || n > 5)					//������ ��� ���
		n = rand() % 5 + 1;				//1~5 ���̿��� �������� ����

	returnVal = drawCard(myCard[n - 1], sum);//returnVal�� drawCard�� ��ȯ���� ����
	printGameUI(*sum, myCard[n-1]);		//�հ�� ���������� �� ī�� ���
	returnCard(cardPack, myCard[n - 1]);//�´� ī�带 ī���ѿ� ������
	getCard(cardPack, &myCard[n-1]);	//ī�带 �ϳ� �� ����

	/*for (n = 0; n < 5; n++)
		printf("%d ", myCard[n]);
	printf("sum: %d \n", *sum);*/
	return returnVal;					//returnVal ��ȯ
}
int AI(int sum, int card[])
{
	/*
	AI�� �ΰ����� ����

	�հ�� AI�� ī�带 ���ڷ� ����
	�켱 �Ϲ� ī�忡�� �� �� �ִ� ī�带 ã��
	�� �� �ִ� �Ϲ� ī�尡 ������ Ư�� ī�带 ��

	�� �� �ִ� ī���� �ε��� ��ȯ
	*/
	int i, n, len = 0;
	int able[5];

	for (i = 0; i < 5; i++)				
		if ((card[i] > 0) && (isItOver(sum + card[i])==1))//card[i]�� �Ϲ� ī���̰� ���� �� ���ӿ������� ������
			able[len++] = i;			//ī���� �ε����� able[len]�� �����ѵ� len ����
	if (len == 0)						//�Ϲ� ī�忡�� ������ ī�尡 ������
		for (i = 0; i < 5; i++)		
		{
			if (card[i] <= 0)			//ī�尡 Ư�� ī���� ��
			{
				if (card[i] != -10)		//-10 ī�尡 �ƴϸ�
					able[len++] = i;	//ī���� �ε����� able[len]�� ������ �� len ����
				else if ((card[i] == -10) && (isItOver(sum - 10) == 1))//ī�尡 -10�̰� ���� �� ���ӿ������� ������
					able[len++] = i;	//ī���� �ε����� able[len]�� ������ �� len ����
				else;
			}
		}
	if (len == 0)						//�� �� �ִ� ī�尡 ������
		return (rand() % 5);			//�ƹ��ų� ����
	n = able[rand() % len];				//������ �ε����� �ϳ��� ���� �� ����
	return n;
}
int AITurn(int AICard[], int *sum, int cardPack[])
{
	/*
	AI�� ���� �����ϴ� �Լ�

	AI�� ī��(AICard)�� �հ�(*sum), ī����(cardPack)�� ���ڷ� ����
	�Ϲ� ī��� 0 ��ȯ
	x2�� MUL ��ȯ
	REV�� REV ��ȯ
	*/
	int n, returnVal = 0;
	n = AI(*sum, AICard);				//AI�� �� ī���� �ε����� n�� ����
	returnVal = drawCard(AICard[n], sum);//ī�带 ��ο��ϰ� ��ȯ���� returnVal�� ����
	//printf("/n = %d/ \n", n);			
	printGameUI(*sum, AICard[n]);		//�հ�� ���������� �� ī�� ���
	returnCard(cardPack, AICard[n]);	//AI�� �� ī�带 ī���ѿ� ������
	getCard(cardPack, &AICard[n]);		//ī�带 �ϳ� ����

	/*for (n = 0; n < 5; n++)
		printf("/%d/ ", AICard[n]);
	printf("/sum: %d/ \n", *sum);*/
	return returnVal;					//returnVal ��ȯ
}


int gamePlay(void)
{
	/*
	������ �����ϴ� �Լ�

	���� ������ 0, �̱�� 1 ��ȯ
	*/
	int cardPack[] = {2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 
		5 , 5 , 5 , 6 , 6 , 6 , 7 , 7 , 7 , 8 , 
		8 , 8 , 9 , 9 , 9 , 3,  3,  3 , 4 , 4 ,
		5,  5,  6,  6,  7,  7,  8,  9, 10,  10,
		10, 10, 10, 12, 22, 33, 44, 55, 66, 76, 
		MUL,MUL,MUL,MUL,MUL,REV,REV,REV,REV,REV,
		-10.-10,-10,-10,-10, 0, 0 , 0 , 0  ,0 };//ī���� �迭, �� 70��
	int myCard[5];
	int AICard[5];							
	int sum = 0;						//�հ�
	int trig;							//x2�� Ȱ��ȭ�ϴ� Ʈ����

	getCards(cardPack, myCard);			//���� ī�� 5���� ��
	getCards(cardPack, AICard);			//AI���� ī�� 5���� ��
	printGameUI(sum, 0);				//�հ�� ������ ī��(0) ���
	
	do
	{
		trig = myTurn(myCard, &sum, cardPack);//�� ���� �����ϰ� ��ȯ���� Ʈ���ſ� ����
		if (isItOver(sum) == -1)		//�հ谡 ���ӿ����Ǵ� ���̸�
			return 0;					//0 ��ȯ

		if (trig == MUL)				//Ʈ���Ű� x2��
			AITurn(AICard, &sum, cardPack);//AI���� �� �� �� ����
		trig = AITurn(AICard, &sum, cardPack);//AI ���� �����ϰ� ��ȯ���� Ʈ���ſ� ����
		if (isItOver(sum) == -1)		//�հ谡 ���ӿ����Ǵ� ���̸�
			return 1;					//-1 ��ȯ
		if (trig == MUL)				//Ʈ���Ű� x2��
			myTurn(myCard, &sum, cardPack);//�� ���� �� �� �� ����
	} while (1);
}
void endGame(int i)
{
	/*
	������ ������ �� ����Ǵ� �Լ�
	*/
	if (i==1)							//���� �̰�����
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
										//���� ������
	}
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
	srand((int)time(NULL));				//�õ尪 ����

while (1)
{
	putUI();							//����ȭ�� ���
	scanf("%d", &swch);

	switch (swch)
	{
	case 1:								//1�� ����������
		endGame(gamePlay());			//������ �����ϰ� gamePlay()�� ��ȯ������ endGame() ����
		continue;
	case 2:								//2�� ����������
		return 0;						//���α׷� ����
	default:
		continue;
	}
}

}