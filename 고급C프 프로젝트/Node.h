#pragma once

typedef enum syllable
{//열거형 선언
	A = 1, B = 2, C = 3, D = 4, E = 0
}Syllable;

void Node(Syllable nd)
{
	switch (nd) {
	case A://D 입력하는 타일
		puts("■◇◇◇◇■        ■        ■        ■"); return;
	case B://F 입력하는 타일
		puts("■        ■◇◇◇◇■        ■        ■"); return;
	case C://J 입력하는 타일
		puts("■        ■        ■◇◇◇◇■        ■"); return;
	case D://K 입력하는 타일
		puts("■        ■        ■        ■◇◇◇◇■"); return;
	case E:
		puts("■        ■        ■        ■        ■"); return;
	};
}