#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MUL  -20
#define REV  -15
#define EMP  -1

void putUI(void)
{
	/*
	메인 화면 출력
	*/
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
	/*
	합계와 마지막으로 낸 카드를 출력하는 함수

	합계(sum)와 마지막으로 낸 카드(card)를 인자로 받음
	*/
	printf("|-----합계:%d", sum);
	if (card >= 0)							//일반적인 숫자카드일 때
		printf("(+%d)-----|\n\n", card);	//+(숫자) 형태로 출력
	else if (card == -10)					//-10일 때
		printf("(%d)-----|\n\n", card);		//-10의 형태로 출력
	else if (card == REV)					//REV일 때
		printf("(R)-----| \n\n");			//R로 출력
	else if (card == MUL)					//x2일 때
		printf("(x2)-----| \n\n");			//x2로 출력
	else									//그 외 오류상황
		printf("(%d)-----| \n\n", card);	//숫자형태로 출력
}
void printMyCard(int arr[])
{
	/*
	나의 카드를 출력하는 함수

	카드 배열(arr)을 인자로 받음
	*/
	int i;
	puts(" 1  2  3  4  5 ");
	for (i = 0; i < 5; i++)
	{
		if (arr[i] < 0)					//arr[i]가 특수카드일 경우
		{
			switch (arr[i])
			{
			case MUL:					//x2일 때
				printf("%2s ", "x2");
				break;
			case REV:					//REV일 때
				printf("%2s ", "R");
				break;
			case -10:					//-10일 때
				printf("%3d", arr[i]);  //-10은 세칸 차지하므로 뒤를 띄지 않음
				break;
			}
		}
		else							//일반 숫자카드일 때
			printf("%2d ", arr[i]);
	}
	putchar('\n');
}
void getCard(int card[], int *num)
{
	/*
	카드팩에서 카드를 하나 뽑는 함수

	카드팩 배열(card)와 카드 변수의 포인터(*num)을 인자로 받음
	*/
	int n;
	
	while (1)
	{
		n = rand() % 69;				//0~69 사이에서 난수 생성
		if (card[n] != EMP)				//card[n]이 비어있지 않으면
		{
			*num = card[n];				//카드 변수에 card[n] 할당
			card[n] = EMP;				//card[n]을 비움
			return;
		}
	}									//card[n]이 비어있으면 계속 반복
}
void getCards(int card[], int arr[])
{
	/*
	카드 다섯장을 얻는 함수

	카드팩 배열(card)와 플레이어의 카드 배열(arr)을 인자로 받음
	*/
	int i;
	for (i = 0; i < 5; i++)
		getCard(card, &arr[i]);			//다섯 번 getCard() 호출
}
int isItOver(int sum)			
{
	/*
	게임이 끝났는지 판단하는 함수

	합계를 인자로 받음
	일반적으로는 1 반환
	게임이 끝날 경우는 -1 반환
	*/
	if (sum <= 0)						//합계가 0 이하면
		return 1;						//정상적 반환
	else if ((sum % 11 == 0) || (sum >= 77))//합계가 11의 배수이거나 77 이상이면
		return -1;						//게임 끝
	else								//그 외는
		return 1;						//정상적 반환
}
void returnCard(int card[], int num)
{
	/*
	플레이어가 낸 카드를 카드팩에 돌려주는 함수

	카드팩 배열(card)와 낸 카드(num)을 인자로 받음
	*/
	int i=0;
	while (1)
	{
		if (card[i] == EMP)				//card[i]가 비어있으면
		{
			card[i] = num;				//card[i]에 낸 카드를 돌려줌
			return;
		}
		i++;							//무한반복
	}
}
int drawCard(int num, int *sum)
{
	/*
	카드를 내는 함수

	내는 카드(num)와 합계의 포인터(*sum)을 인자로 받음 
	일반 카드는 0 반환
	x2는 MUL 반환
	REV는 REV 반환
	*/
	if (num >= 0)						//일반 카드일 경우
		*sum += num;					//합계에 냈던 카드를 더함
	else								//특수 카드일 경우
	{
		switch (num)
		{
		case -10:						//-10일 때
			*sum += -10;				//-10을 더함
			break;
		case MUL:						//x2일 때
			return MUL;					//x2 리턴
			break;
		case REV:						//REV일 때
										//REV 리턴(추가예정)
			break;
		}
	}
	return 0;							//그 외는 0 리턴
}

int myTurn(int myCard[], int *sum, int cardPack[])
{
	/*
	나의 턴을 실행하는 함수

	나의 카드(myCard)와 합계 변수의 포인터(*sum), 카드팩(cardPack)을 인자로 받음
	일반 카드는 0 반환
	x2는 MUL 반환
	REV는 REV 반환
	*/
	int n, returnVal = 0;
	printMyCard(myCard);				//나의 카드를 출력
	scanf("%d", &n);					//낼 카드를 선택

	if (n < 1 || n > 5)					//범위를 벗어날 경우
		n = rand() % 5 + 1;				//1~5 사이에서 랜덤으로 선택

	returnVal = drawCard(myCard[n - 1], sum);//returnVal에 drawCard의 반환값을 대입
	printGameUI(*sum, myCard[n-1]);		//합계와 마지막으로 낸 카드 출력
	returnCard(cardPack, myCard[n - 1]);//냈던 카드를 카드팩에 돌려줌
	getCard(cardPack, &myCard[n-1]);	//카드를 하나 더 뽑음

	/*for (n = 0; n < 5; n++)
		printf("%d ", myCard[n]);
	printf("sum: %d \n", *sum);*/
	return returnVal;					//returnVal 반환
}
int AI(int sum, int card[])
{
	/*
	AI의 인공지능 구현

	합계와 AI의 카드를 인자로 받음
	우선 일반 카드에서 낼 수 있는 카드를 찾음
	낼 수 있는 일반 카드가 없으면 특수 카드를 냄

	낼 수 있는 카드의 인덱스 반환
	*/
	int i, n, len = 0;
	int able[5];

	for (i = 0; i < 5; i++)				
		if ((card[i] > 0) && (isItOver(sum + card[i])==1))//card[i]가 일반 카드이고 냈을 때 게임오버되지 않으면
			able[len++] = i;			//카드의 인덱스를 able[len]에 저장한뒤 len 증가
	if (len == 0)						//일반 카드에서 가능한 카드가 없으면
		for (i = 0; i < 5; i++)		
		{
			if (card[i] <= 0)			//카드가 특수 카드일 때
			{
				if (card[i] != -10)		//-10 카드가 아니면
					able[len++] = i;	//카드의 인덱스를 able[len]에 저장한 뒤 len 증가
				else if ((card[i] == -10) && (isItOver(sum - 10) == 1))//카드가 -10이고 냈을 때 게임오버되지 않으면
					able[len++] = i;	//카드의 인덱스를 able[len]에 저장한 뒤 len 증가
				else;
			}
		}
	if (len == 0)						//낼 수 있는 카드가 없으면
		return (rand() % 5);			//아무거나 리턴
	n = able[rand() % len];				//가능한 인덱스중 하나를 정한 뒤 리턴
	return n;
}
int AITurn(int AICard[], int *sum, int cardPack[])
{
	/*
	AI의 턴을 실행하는 함수

	AI의 카드(AICard)와 합계(*sum), 카드팩(cardPack)을 인자로 받음
	일반 카드는 0 반환
	x2는 MUL 반환
	REV는 REV 반환
	*/
	int n, returnVal = 0;
	n = AI(*sum, AICard);				//AI가 고른 카드의 인덱스를 n에 저장
	returnVal = drawCard(AICard[n], sum);//카드를 드로우하고 반환값을 returnVal에 저장
	//printf("/n = %d/ \n", n);			
	printGameUI(*sum, AICard[n]);		//합계와 마지막으로 낸 카드 출력
	returnCard(cardPack, AICard[n]);	//AI가 낸 카드를 카드팩에 돌려줌
	getCard(cardPack, &AICard[n]);		//카드를 하나 뽑음

	/*for (n = 0; n < 5; n++)
		printf("/%d/ ", AICard[n]);
	printf("/sum: %d/ \n", *sum);*/
	return returnVal;					//returnVal 반환
}


int gamePlay(void)
{
	/*
	게임을 실행하는 함수

	내가 졌으면 0, 이기면 1 반환
	*/
	int cardPack[] = {2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 
		5 , 5 , 5 , 6 , 6 , 6 , 7 , 7 , 7 , 8 , 
		8 , 8 , 9 , 9 , 9 , 3,  3,  3 , 4 , 4 ,
		5,  5,  6,  6,  7,  7,  8,  9, 10,  10,
		10, 10, 10, 12, 22, 33, 44, 55, 66, 76, 
		MUL,MUL,MUL,MUL,MUL,REV,REV,REV,REV,REV,
		-10.-10,-10,-10,-10, 0, 0 , 0 , 0  ,0 };//카드팩 배열, 총 70장
	int myCard[5];
	int AICard[5];							
	int sum = 0;						//합계
	int trig;							//x2를 활성화하는 트리거

	getCards(cardPack, myCard);			//내게 카드 5개를 줌
	getCards(cardPack, AICard);			//AI에게 카드 5개를 줌
	printGameUI(sum, 0);				//합계와 마지막 카드(0) 출력
	
	do
	{
		trig = myTurn(myCard, &sum, cardPack);//내 턴을 실행하고 반환값을 트리거에 저장
		if (isItOver(sum) == -1)		//합계가 게임오버되는 값이면
			return 0;					//0 반환

		if (trig == MUL)				//트리거가 x2면
			AITurn(AICard, &sum, cardPack);//AI턴을 한 번 더 실행
		trig = AITurn(AICard, &sum, cardPack);//AI 턴을 실행하고 반환값을 트리거에 저장
		if (isItOver(sum) == -1)		//합계가 게임오버되는 값이면
			return 1;					//-1 반환
		if (trig == MUL)				//트리거가 x2면
			myTurn(myCard, &sum, cardPack);//내 턴을 한 번 더 실행
	} while (1);
}
void endGame(int i)
{
	/*
	게임이 끝났을 때 실행되는 함수
	*/
	if (i==1)							//내가 이겼으면
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
										//내가 졌으면
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
	srand((int)time(NULL));				//시드값 생성

while (1)
{
	putUI();							//메인화면 띄움
	scanf("%d", &swch);

	switch (swch)
	{
	case 1:								//1을 선택했으면
		endGame(gamePlay());			//게임을 시작하고 gamePlay()의 반환값으로 endGame() 실행
		continue;
	case 2:								//2를 선택했으면
		return 0;						//프로그램 종료
	default:
		continue;
	}
}

}