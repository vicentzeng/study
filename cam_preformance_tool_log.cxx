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
using namespace std;
int main(int argc, char **argv)
{
	char test_str[128];
	system("adb devices > data");
	ifstream fin("data"); 
	streambuf *log_buf;
	log_buf= cin.rdbuf(fin.rdbuf());  //用 rdbuf() 重新定向cin
	cin>>test_str;
	cout<<"Test E"<<endl;
	cout<<test_str<<endl;
	printf("%s\n", test_str);
	cout<<"Test X"<<endl;
	cin.rdbuf(log_buf); 
	//shell管道
	//http://blog.csdn.net/iamagoodguy_/article/details/39453265
    #define BUF_LEN 256  
    static char buf[BUF_LEN];  
    for (int i = 0; i < argc; ++i){  
        printf("[from args]:%s\n", argv[i]);  
    }  
    while (fgets(buf, BUF_LEN, stdin) != NULL){  
        printf("[from stdin][%s]\n", buf);  
    }  

	return 0;
}

