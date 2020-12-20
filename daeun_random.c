#include<stdio.h>
#include<stdlib.h> //srand,rand 함수
#include<time.h>   //time 함수
#define value 10000 //int value = 10000;
extern long int random(void) {
	int i;
	int data[value]; //난수 값 저장 배열
	srand(time(NULL)); //난수 발생 시드를 현재 시각으로 한다.
	for (i = 0; i < value; i++) {
	data[i] = (rand() % 256) + 1;
	} // 1000개의 숫자가 1에서 256까지의 값이 랜덤으로 생성되어 배열에 저장
	char str[value]; //숫자,대문자,소문자로 구성하는 문자열 저장 배열
	int option; // 옵션 : 0이면 숫자, 1이면 소문자, 2이면 대문자 생성
	for (int i = 0; i < data[(rand() % 10000) + 1]; i++) { 
		option = rand() % 3;
		if (option == 0)
			str[i] = '0' + rand() % 10; //숫자 생성
		else if (option == 1)
			str[i] = 'a' + rand() % 26; //소문자 생성
		else
			str[i] = 'A' + rand() % 26; //대문자 생성
		} //str배열은 랜덤 data값 만큼 받음.
	return 0;
}
