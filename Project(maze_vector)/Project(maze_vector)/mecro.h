#pragma once
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<iostream>
#include<vector>

using namespace std;
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//���� ����
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
#define WALL 1//�迭�� ���� ���� ���� 1
#define EMPTY 0//������ 0
#define Y 0//y�� �̵�
#define X 1//x�� �̵�
#define CHARACTER 2//ĳ���� ���� ��ġ
//#define CHARACTER2P 3//ĳ���� ���� ��ġ
#define POTAL_MAX 6//��Ż ����
#define ENTRY_START 10//�Ա� ��Ż�� ���� ��ġ
#define EXIT_START 20//�ⱸ ��Ż�� ���� ��ġ
#define WIDTH 12//����
#define HEIGHT 12//����
#define RANDOM_START 30//����
#define W 119//2p �����¿�
#define A 97
#define S 115
#define D 100
#define KEY 9
#define GAMEOVER 4
#define RESET 7

struct Point
{
	int x;
	int y;
};