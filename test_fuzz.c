#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
	// Args Check
	// Argv[0] ELF
	if(argc < 4){
		printf("Usage: ./DumbFuzz [Target] [InputFile] [OutputDir]\n");
		exit(0);
	}
	int num=0;
	printf("[+] Start Dumb Fuzzing....\n");
	// Loop 
	while(num <100){
		// Make Random values
		unsigned char cmd[2024];
		sprintf(cmd, "echo %s | radamsa", argv[2]);// Read Inputfile
		FILE* stream = popen(cmd, "r");
		unsigned char buf[1024];
		if(stream != NULL){
			fgets(buf, 1024, stream);
			printf("[+] input : %s\n", buf);

		}
		pclose(stream);
		// buf remove \n
		printf("len : %d\n",strlen(buf)); 
		for(int i=0; i<strlen(buf); i++){
			printf("%2x",buf[i]);
			if(buf[i] == '\x0a'){
				buf[i] = '\x00';
			}
		}
		printf("\n");
		sprintf(cmd, "python -c \'print \"%s\"\' | %s",buf ,argv[1]);
		printf("[+] cmd : %s",cmd);
		int result = system(cmd);
		printf("[+] Program Terminated\n");
		printf("[+] result: %d/n", result);
		if( result != 0)
		{
			printf("error!\n");break;
		}else{
			printf("good\n");
			num++;
		}
	}
	printf("[+] Fuzzing Done!");
}
