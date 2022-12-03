#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable :4996)
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <process.h> 
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")//게임 구동에 필요한 헤더파일

//사용자 정의 헤더파일
#include "Node_game.h"//게임 타일 배열
#include "Node.h"//타일 UI 열거형으로 저장

int scr = 0;//게임 진행할 때 점수 (전역 변수로 선언)

char str[10];//PERFECT!,NICE TRY 출력

char temp_name[4];
int temp_score;//점수 저장할 때 사용되는 변수

struct score {//점수 저장 구조체
    char name[4];//점수 저장할 사용자 닉네임
    int score;//점수
} player[10];//TOP 10 저장할 때 쓰일 구조체 배열

void compose(int p)//게임 진행 시 입력받은 키보드 키에 의해 점수 차등 부여
{
    if (GetAsyncKeyState(0x44) & 0x8000) {//D 키 입력 받았을 때
        if (Node_game[p] == 1) {//D키를 입력받아야 할 피아노 타일일 때
            scr = scr + 100;//100점 부여
            strcpy(str, "PERFECT!");//PERFECT! 출력
        }
        else if (Node_game[p] == 0) {//입력받아야 할 키가 없다면 출력한 PERFECT 제거
            strcpy(str, "        ");
        }
        else {
            strcpy(str, "NICE TRY");//다른 키를 입력받거나 키를 입력하지 않으면
            scr = scr - 50;//50점 차감
        }
    }

    if (GetAsyncKeyState(0x46) & 0x8000) {//F 키 입력 받았을 때
        if (Node_game[p] == 2) {//F키를 입력받아야 할 피아노 타일일 때
            scr = scr + 100;
            strcpy(str, "PERFECT");
        }
        else if (Node_game[p] == 0) {
            strcpy(str, "        ");
        }
        else {
            strcpy(str, "NICE TRY");
            scr = scr - 50;
        }
    }

    if (GetAsyncKeyState(0x4A) & 0x8000) {//J 키 입력 받았을 때
        if (Node_game[p] == 3) {//J키를 입력받아야 할 피아노 타일일 때
            scr = scr + 100;
            strcpy(str, "PERFECT");
        }
        else if (Node_game[p] == 0) {
            strcpy(str, "        ");
        }
        else {
            strcpy(str, "NICE TRY");
            scr = scr - 50;
        }
    }

    if (GetAsyncKeyState(0x4B) & 0x8000) {//K 키 입력 받았을 때
        if (Node_game[p] == 4) {//K키를 입력받아야 할 피아노 타일일 때
            scr = scr + 100;
            strcpy(str, "PERFECT");
        }
        else if (Node_game[p] == 0) {
            strcpy(str, "        ");
        }
        else {
            strcpy(str, "NICE TRY");
            scr = scr - 50;
        }
    }
}

void Push_score()//TOP 10 저장 함수
{
    if (temp_score > player[0].score) {//플레이어가 1등했을 때
        char temp1[4];
        int temp2;
        for (int j = 9; j >0; j--) {//기존 TOP 10 명단 한 줄씩 밀기 (1등->2등,2등->3등,...)
            strcpy(temp1, player[j - 1].name);//이니셜 밀기
            strcpy(player[j - 1].name, player[j].name);
            strcpy(player[j].name, temp1);

            temp2 = player[j - 1].score;//점수 밀기
            player[j - 1].score = player[j].score;
            player[j].score = temp2;
        }
        player[0].score = temp_score;//1등에 플레이어 점수 저장
        strcpy(player[0].name, temp_name);
    }
    
    int i;
    for (i = 0; i < 9; i++) {//플레이어 점수가 1등에서 10등 사이일 때
        if (temp_score < player[i].score && temp_score>player[i + 1].score) {
            for (int j = 9; j > i; j--) {//플레이어 점수보다 낮은 점수 한 줄씩 밀기
                strcpy(player[j].name,player[j-1].name);//이니셜 밀기

                player[j].score = player[j-1].score;//점수 밀기
            }
            player[i + 1].score = temp_score;//TOP 10 사이에 플레이어 점수 저장
            strcpy(player[i + 1].name, temp_name);
        }
    }
}

void enterscore()
{
    printf("축하합니다! top 10에 드셨습니다. \n***명예의 전당에 이름을 올리실 수 있습니다.***\n");
    printf("이니셜을 입력해주세요. (영어) : ");
    scanf(" %s",&temp_name);
    printf("\n\n메인 화면의 명예의 전당에서 이름을 확인하실 수 있습니다!!");
    Push_score();//TOP 10 점수 저장 함수 호출
    system("cls");//화면 초기화
}

void Compare()//게임 후 TOP10에 드는지 확인하는 함수
{
    if (player[9].score < temp_score) {
        enterscore();//TOP10 안에 들 경우 이니셜 입력 함수로 넘어감
    }
    else
        return 0;
}

void game()//리듬 게임 진행 함수
{
    Syllable nd;//열거형으로 제작한 피아노 타일 불러옴

    char Note_start[2][43] = {//게임 진행 UI
    {"■■■■■■■■■■■■■■■■■■■■■"},
    {"------------------------------------------"}
    };
    char Note_end[43] = { "■■■■■■■■■■■■■■■■■■■■■" };

    PlaySound(TEXT("문리버.wav"), NULL, SND_ASYNC);//음악 재생

    int k = 0;
    scr = 0;

    while (k != 320) {
        printf("%s		%s\n", Note_start[0], str);
        Node(0);
        printf("%s		SCORE: %d\n", Note_start[1], scr);
        strcpy(str,"            ");

        int a;
        for (a = k + 2; a < k + 17; a++) {//배열 출력 범위를 조절하여 타일을 옮김
            Node(Node_game[a]);
        };
        compose(k + 1);//점수 부여 함수 호출
        k++;

        printf("%s", Note_end);
        Sleep(250);//2.5초마다 화면 전환

        //더블 버퍼링 (화면 전환 딜레이 삭제)
        COORD pos = { 0,0 };//COORD 라는 구조체는 선언되어 있는 x, y 값을 저장하는 역할
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        //GetStdHandle(STD_OUTPUT_HANDLE) 콘솔창 핸들을 커서의 위치를 이동시키는 함수
    }
    system("cls");
    //게임 완료 후
    printf("\n\nscore: %d\n\n", scr);//최종 점수 출력
    temp_score = scr;
    Sleep(5000);
    system("cls");

    Compare();//TOP10과의 점수 비교 함수 호출
}

void Save()//외부 txt 파일에 TOP10 명단 저장
{
    FILE* fp = fopen("score.txt", "r+");
    for (int i = 0; i < 10; i++) {
        fprintf(fp, "%s\n", player[i].name);
    }
    for (int i = 0; i < 10; i++) {
        fprintf(fp, "%d\n", player[i].score);
    }
    fclose(fp);
    return 0; 
}

void Load()//외부 txt 파일에서 TOP10 명단 불러옴
{
    FILE* fp = fopen("score.txt", "r+");
    for (int i = 0; i < 10; i++) {
        fscanf(fp, "%s\n", player[i].name);
    }
    for (int i = 0; i < 10; i++) {
        fscanf(fp, "%d\n", &player[i].score);
    }
    fclose(fp);
    return 0;
}

void ViewScore()//TOP10 점수 보여줌
{
    printf("---------------\n");  
    printf("     이름 : 점수\n");
    for (int i = 0; i < 10; i++) {
        printf("%4d) %s : %d\n",i+1,player[i].name,player[i].score);
    }
    printf("---------------");
    getchar();
    getchar();
    system("cls");
}

int main()//프로그램 메인 진행
{
    FILE* fp = fopen("score.txt", "r+");
    int a;//프로그램 진행 변수
    Load();//txt 파일에서 점수 정보 불러옴
    while (1)
    {
        printf("1. 점수표 보기\n");//메인 화면
        printf("2. 게임 시작\n");
        printf("3. 게임 종료\n");
        printf("번호 입력>");
        scanf("%d", &a);

        switch (a) 
        {
        case 1:
            
            system("cls");
            ViewScore();//점수 출력 함수 호출
            break;

        case 2:
            system("cls");
            game();//리듬 게임 진행 함수 호출
            break;

        case 3: 
            Save();//txt 파일에 TOP10 정보 저장
            system("cls");
            return 0;//종료

        default:
            printf("다시 입력하세요.\n");
            break;
        }
    }

    return 0;
}
/*
main함수
1. 점수표보기: ViewScore 
2. 게임시작: Game()_노래시작 및 게임진행 -> 결과로 나오는 점수 저장 -> Compare()_이전에 저장한 점수와 비교 
-> enterScore()_이니셜 작성 / 아니면 nice try 출력후 return 0
3. end
*/