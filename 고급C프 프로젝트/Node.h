#pragma once

typedef enum syllable
{//������ ����
	A = 1, B = 2, C = 3, D = 4, E = 0
}Syllable;

void Node(Syllable nd)
{
	switch (nd) {
	case A://D �Է��ϴ� Ÿ��
		puts("��ޡޡޡޡ�        ��        ��        ��"); return;
	case B://F �Է��ϴ� Ÿ��
		puts("��        ��ޡޡޡޡ�        ��        ��"); return;
	case C://J �Է��ϴ� Ÿ��
		puts("��        ��        ��ޡޡޡޡ�        ��"); return;
	case D://K �Է��ϴ� Ÿ��
		puts("��        ��        ��        ��ޡޡޡޡ�"); return;
	case E:
		puts("��        ��        ��        ��        ��"); return;
	};
}