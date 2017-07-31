/*
 * cam_preformance_tool_log.cxx
 * 
 * Copyright 2017 vicent <vicent@vicentPC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <fstream> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#define   OUT_BUFF_SIZE 32
#define   READ_HANDLE 0
#define   WRITE_HANDLE 1
#define   BEEP_CHAR 7	//要filter字符
#define   MAX_BUF_LEN	4096
char szBuffer[OUT_BUFF_SIZE];

struct KpiInfo{
        char kpi_name[64];
        char kpi_start_key[64];
        char kpi_stop_key[64];
};

void parse_kpi_word(KpiInfo *info){
	int kpi_fd = open("kpi",O_RDONLY);
	char buf[MAX_BUF_LEN];
	int read_cnt = read(kpi_fd, buf, MAX_BUF_LEN);
    if ( read_cnt > 0){  
        //printf("%s\n", buf);
        char *kpi_name = info->kpi_name;
        char *kpi_start_key = info->kpi_start_key;
        char *kpi_stop_key = info->kpi_stop_key;

        char *key_start_p = buf;
        char *key_stop_p = buf;
        for(int i = 0; i < read_cnt; i++){
			//cout <<buf[i];
			if(buf[i] == '\['){
				key_stop_p = buf + i;
				if(key_stop_p > key_start_p){
					strncpy(kpi_name, key_start_p, key_stop_p - key_start_p);
					kpi_name[key_stop_p - key_start_p] = '\0';
					cout << "kpi_name:" <<kpi_name<<endl;
				}
				key_start_p = key_stop_p + 1;
			}else if(buf[i] == ','){
				key_stop_p = buf + i;
				if(key_stop_p > key_start_p){
					strncpy(kpi_start_key, key_start_p, key_stop_p - key_start_p);
					kpi_start_key[key_stop_p - key_start_p] = '\0';
					cout << "kpi_start_key:" <<kpi_start_key<<endl;
				}
				key_start_p = key_stop_p + 1;
			}else if(buf[i] == ']'){
				key_stop_p = buf + i;
				if(key_stop_p > key_start_p){
					strncpy(kpi_stop_key, key_start_p, key_stop_p - key_start_p);
					kpi_stop_key[key_stop_p - key_start_p] = '\0';
					cout << "kpi_stop_key:" <<kpi_stop_key<<endl;
				}
				key_start_p = key_stop_p + 1;	
			}else if(buf[i] == '\t'){
				key_start_p = buf + i + 1;
			}else if(buf[i] == '\n'){
				cout << "kpi_name n:"<<endl;
				key_start_p =buf + i + 1;
				//add to list
				if(*kpi_name!=0 &&*kpi_start_key!=0 && *kpi_stop_key!=0){
					cout << "kpi_start_key:" <<kpi_start_key<<endl;
					return;
				}
			}
		}
    }else{
		printf("read kpi fail!");
	}
}
int main(int argc, char **argv)
{
	//filter demo man pipe
           int pipefd[2];
           pid_t cpid;
           char buf[MAX_BUF_LEN];
           int hStdOut;
		   int nExitCode = 0;
           if (argc != 1) {
               fprintf(stderr, "Usage: %s <string>\n", argv[0]);
               exit(EXIT_FAILURE);
           }
           
           //
           KpiInfo kpi;
		   parse_kpi_word(&kpi);
		   
           if (pipe(pipefd) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

		// Duplicate stdout handle (next line will close original)
		hStdOut = dup(fileno(stdout));

		// Duplicate write end of pipe to stdout handle
		dup2(pipefd[1], fileno(stdout));

		// Close original write end of pipe, 已经由stdout托管,pipefd[1]所以可以关闭
		close(pipefd[1]);

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child writes argv[1] to pipe */
			   cout<<"sub-p"<<endl;
				close(pipefd[0]);          /* Close unused read end */ //子进程中的fork时候,clone的一份读pipefd[0]需要关闭
				char cmd[256];
				sprintf(cmd, "adb logcat|grep -i 'openCamera'", kpi.kpi_start_key);
				cout<<"cmd"<<cmd<<endl;
				if (execl("/bin/bash","bash","-c",cmd,NULL) <0 ){  
					perror("error on exec");
					exit(0);
				}
               close(pipefd[1]);          /* Reader will see EOF */
               exit(EXIT_SUCCESS);
           } else {            /* Parent reads from pipe */
				// Duplicate copy of original stdout back into stdout
				dup2(hStdOut, fileno(stdout));
				// Close duplicate copy of original stdout
				close(hStdOut);
                close(pipefd[1]);          /* Close unused write end */
				while(1){
				   while (read(pipefd[0], buf, 1) > 0){
					   write(STDOUT_FILENO, buf, 1);
					   //write(STDOUT_FILENO, "vicent:", 8);
				   }
				}
               write(STDOUT_FILENO, "\n", 1);
               close(pipefd[0]);
               wait(&nExitCode);                /* Wait for child */
               _exit(EXIT_SUCCESS);
           }
	return 0;
}

