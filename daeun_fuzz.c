#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "daeun_random.c"

int main(int argc, char* argv[])
{
	if (argc < 3) {
			printf("Usage: ./DumbFuzz [Target] [OutPutDir]\n");
			exit(0);
	}
	int error = 0;
	int num=0;

	printf("[+] Start Dumb Fuzzing....\n");

	unsigned char buf[10000];
	unsigned char cmd[20000];
		
	while(num++ < 1000){
		unsigned char cmd[2024];
			sprintf(cmd, random());
			FILE* stream = popen(cmd, "r");
			unsigned char buf[1024];
			if(stream != NULL){
				fgets(buf, 1024, stream);
				printf("[+] input : %s\n", buf);
		}

		for(int i=0; i<strlen(buf); i++){
			if(buf[i] == '\x0a'){
				buf[i] = '\x00'; 
			}
		}
		printf("\n");
		sprintf(cmd, "python -c \'print \"%s\"\' | %s", buf ,argv[1]);
		int result = system(cmd); 
		printf("[+] Program Terminated\n");
		printf("[+] result: %d/n", result); 
		if( result != 0)
		{
			printf("error!\n");
			error++;
			
			char path[100]; 
			sprintf(path, "./%s/%d", argv[3], num);
			FILE *fp = fopen(path,"a+"); 
			fwrite(buf, sizeof(buf),1,fp); 
			fclose(fp);
		}
		else
			printf("good\n");
	}
	printf("[+] Fuzzing Done!\n");
	printf("[+] error : %d\n",error); 
}
