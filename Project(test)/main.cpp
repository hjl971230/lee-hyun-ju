#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;

void test1()
{
	system("cls");
	int num1 = 0, num2 = 0;
	cout << "�� �� �Է�" << endl;
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
	cout << "���� 3�� �Է�" << endl;
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
		cout << "0�Է½� ���� ��� ����" << endl;
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
		cout << "���� �� ���� ���� �Է�(1~100)" << endl;
		cin >> input;
		if (rnum == input)
		{
			cout << "���� " << rnum << " �̾����ϴ�." << endl;
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
	/*1. �μ��� �Է� �޾� ū ���� ¦���̸� ����Ͻÿ�(if��)

2. �� ������ ������ �Է� �޾� �հ�� ����� ���ϰ� ����� 90�̻��̸� ��A��, 
80�̻��̸� ��B��, 70 �̻��̸� ��C��, 60 �̻��̸� �� D��, 60�̸��̸� ��F���� ����Ͻÿ�.(if��)

3.1~1000������ ���� ���϶�.�� 3�� ����� �����ϰ� 3�� ����̸鼭
  5�� ����� �������� �ʴ� �������� ���϶�.(for��)

4. ������ �ݺ��Ͽ� �Է� �޾� �Է� ���� �������� �հ踦 ���Ͻÿ�
(0�� �Է� ���� �� ���� ����Ͽ� �Է� �ް� ���� ��)(while��)

5. updown ������ �ϼ��Ͻÿ�.*/

	srand(time(NULL));
	test1();
	test2();
	test3();
	test4();
	test5();
}