#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;

void test1()
{
	system("cls");
	int num1 = 0, num2 = 0;
	cout << "두 수 입력" << endl;
	cin >> num1;
	cin >> num2;
	if (num1 > num2)
	{
		if (num1 % 2 == 0)
			cout << num1<< endl;
	}
	else if(num1 < num2)
	{
		if (num2 % 2 == 0)
			cout << num2 << endl;
	}
	system("pause");
}

void test2()
{
	system("cls");
	int num1 = 0, num2 = 0, num3 = 0;
	cout << "성적 3개 입력" << endl;
	cin >> num1;
	cin >> num2;
	cin >> num3;
	int avg = (num1 + num2 + num3) / 3;
	if (avg >= 90)
		cout << "A" << endl;
	else if (avg >= 80 && avg < 90)
		cout << "B" << endl;
	else if (avg >= 70 && avg < 80)
		cout << "C" << endl;
	else if (avg >= 60 && avg < 70)
		cout << "D" << endl;
	else
		cout << "F" << endl;
	system("pause");
}

void test3()
{
	system("cls");
	int num = 0;
	for (int i = 1; i <= 1000; i++)
	{
		if (i * 3 == 0)
		{
			if (i * 5 == 0)
				num += i;
		}
		else
			num += i;
	}
	cout << num << endl;
	system("pause");
}

void test4()
{
	system("cls");
	int num = 0;
	int input = 1;
	while (input != 0)
	{
		system("cls");
		cout << "0입력시 까지 계속 더함" << endl;
		cin >> input;
		num += input;
		cout << num << endl;
		system("pause");
	}
	system("pause");
}

void test5()
{
	system("cls");
	int rnum = (rand() % 99) + 1;
	int input = 0;
	while (true)
	{
		system("cls");
		cout << "맞힐 때 까지 수를 입력(1~100)" << endl;
		cin >> input;
		if (rnum == input)
		{
			cout << "수는 " << rnum << " 이었습니다." << endl;
			break;
		}
		else if (rnum > input)
			cout << "up" << endl;
		else
			cout << "down" << endl;
		system("pause");
	}
	system("pause");
}

void main()
{
	/*1. 두수를 입력 받아 큰 수가 짝수이면 출력하시오(if문)

2. 세 과목의 성적을 입력 받아 합계와 평균을 구하고 평균이 90이상이면 “A”, 
80이상이면 “B”, 70 이상이면 “C”, 60 이상이면 “ D”, 60미만이면 “F”를 출력하시오.(if문)

3.1~1000까지의 합을 구하라.단 3의 배수는 제외하고 3의 배수이면서
  5의 배수는 제외하지 않는 조건으로 구하라.(for문)

4. 정수를 반복하여 입력 받아 입력 받은 정수들의 합계를 구하시오
(0을 입력 받을 때 까지 계속하여 입력 받게 만들 것)(while문)

5. updown 게임을 완성하시오.*/

	srand(time(NULL));
	test1();
	test2();
	test3();
	test4();
	test5();
}