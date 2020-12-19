/*daeun_fuzz*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include"daeun_random.c"

int main(int argc, char* argv[])
{
	if (argc < 3) //입력이 3개보다 적다면 printf문 출력
	{ 
	printf("Usage: ./DumbFuzz [Target] [OutPutDir]\n"); // 퍼저에 필요한 target outputdir입력 
	exit(0); // 정상종료
	}
	int num = 0; // 변수 num 선언&초기화
	int error = 0; // 변수 error 선언&초기화
	printf("[+] Start Dumb Fuzzing....\n"); // 덤퍼저 시작을 알리는 출력문

	while (num < 100) // num이 100미만일 동안 반복
	{
		unsigned char cmd[2024]; // 양수 2024바이트 문자형 cmd 배열 생성
		sprintf(cmd, str); // cmd 문자열에 randomstring.c의 str을 저장
		FILE* stream = popen(cmd, "r"); // 파일포인터 stream ; cmd을 읽기모드로 오픈

		unsigned char buf[1024]; // 양수 1024바이트 문자형 buf 배열 생성
		if (stream != NULL) // stream이 null이 아니라면
    { 
			fgets(buf, 1024, stream); // stream의 문자열을 최대 1024까지 읽어 buf에 담음
			printf("[+] input : %s\n", buf); //[+]input : buf문자열 출력
		}
		pclose(stream); // 파일닫기

		printf("len : %lu\n",strlen(buf)); //buf의 문자열 길이 출력
		for(int i=0; i<strlen(buf);i++)
		{
			printf("%2x",buf[i]);//buf[i]를 두자리 hexcode로 출력
			if(buf[i] == '\x0a') //buf[i]가 줄바꿈되면
			buf[i]='\x00'; // buf[i]에 null대입
		} // buf 줄바꿈문자 없애는 과정
		
		printf("\n");
		sprintf(cmd, "python -c \'print \"%s\"\' | %s", buf, argv[1]);
    // cmd문자열에 python -c'print "buf"' | argv[1]
		printf("[+] cmd : %s", cmd); // [+] cmd : cmd 문자열 출력
		int result = system(cmd); //cmd을 result에 대입
		printf("[+] Program Terminated\n"); 
		printf("[+] result : %d\n", result); // [+] result : result값 출력
		if (result != 0) // result가 0이 아니면	
		{
			printf("error!\n");
			error++; // error 1씩 증가
			FILE* fp = fopen(argv[2], "a+");
      //파일포인터 fp; argv[3]=ouputdir을 파일 읽기 및 덧붙이기 모드로 오픈
			fwrite(buf, sizeof(buf), 1, fp); // buf에 있는 정수 1개를 fp에 저장
			fclose(fp); // 파일 닫기
		}
		else // result가 0이라면
		{
			printf("good\n");
			num++; // num 1씩 증가
		}
	}
	printf("[+] Fuzzing Done!\n"); // 퍼징 끝 출력
	printf("[+] error : %d\n", error); // 에러 개수출력
}
