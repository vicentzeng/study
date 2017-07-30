// LogAna.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <process.h> 
#include <io.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define BUF_LEN 256
using namespace std;

#define   OUT_BUFF_SIZE 32
#define   READ_HANDLE 0
#define   WRITE_HANDLE 1
#define   BEEP_CHAR 7	//要filter字符

char szBuffer[OUT_BUFF_SIZE];

int Filter(char* szBuff, ULONG nSize, int nChar)
{
	char* szPos = szBuff + nSize - 1;
	char* szEnd = szPos;
	int nRet = nSize;

	while (szPos > szBuff)
	{
		if (*szPos == nChar)
		{
			memmove(szPos, szPos + 1, szEnd - szPos);
			--nRet;
		}
		--szPos;
	}
	return nRet;
}

bool init_shell_pipeline()
{
	//cin从定向
	char test_str[128];
	system("adb devices > data");
	fstream fin;
	fin.open("data", ios::in);
	streambuf *log_buf = cin.rdbuf(fin.rdbuf());  //用 rdbuf() 重新定向cin
	/*cin >> test_str;	//读取cin到buf
	cout << "Test E" << endl;
	printf("%s\n", test_str);
	cout << "Test X" << endl;
	//cin.rdbuf(log_buf);
	*/
	//shell管道
	//http://blog.csdn.net/iamagoodguy_/article/details/39453265
	static char buf[BUF_LEN];
	/*for (int i = 0; i < argc; ++i) {
		printf("[from args]:%s\n", argv[i]);
	}*/
	
	//fork新子进程
	//system("adb");
	//Process p = Runtime.getRuntime().exec("cmd");
	int adb_pid = _spawnl(_P_DETACH,"adb","logcat");
	//_fork();
	//_dup2(adb_pid, 1);


	//接收子进程消息
	while (fgets(buf, BUF_LEN, stdin) != NULL) {
		printf("from stdin:%s\n", buf);
	}

	return true;
}

int main(int argc, char** argv)
{
	//init_shell_pipeline();

	//filter Demo
	//https://msdn.microsoft.com/en-us/library/aa298531(v=vs.60).aspx
	int nExitCode = STILL_ACTIVE;
	if (argc >= 2)
	{
		HANDLE hProcess;
		int hStdOut;
		int hStdOutPipe[2];

		// Create the pipe
		if (_pipe(hStdOutPipe, 512, O_BINARY | O_NOINHERIT) == -1)
			return   1;

		// Duplicate stdout handle (next line will close original)
		hStdOut = _dup(_fileno(stdout));

		// Duplicate write end of pipe to stdout handle
		if (_dup2(hStdOutPipe[WRITE_HANDLE], _fileno(stdout)) != 0)
			return   2;

		// Close original write end of pipe
		_close(hStdOutPipe[WRITE_HANDLE]);

		// Spawn process
		hProcess = (HANDLE)_spawnvp(P_NOWAIT, argv[1],
			(const char* const*)&argv[1]);

		// Duplicate copy of original stdout back into stdout
		if (_dup2(hStdOut, _fileno(stdout)) != 0)
			return   3;

		// Close duplicate copy of original stdout
		_close(hStdOut);

		if (hProcess)
		{
			int nOutRead;
			while (nExitCode == STILL_ACTIVE)
			{
				nOutRead = _read(hStdOutPipe[READ_HANDLE],
					szBuffer, OUT_BUFF_SIZE);
				printf("vicent %d\n", nOutRead);
				if (nOutRead)
				{
					nOutRead = Filter(szBuffer, nOutRead, BEEP_CHAR);
					fwrite(szBuffer, 1, nOutRead, stdout);
				}

				if (!GetExitCodeProcess(hProcess, (unsigned long*)&nExitCode))
					return 4;
			}
		}
	}

	printf("\nPress \'ENTER\' key to continue... ");
	getchar();
	return nExitCode;
}


/**** Java 重定向
String[] args = {"python3", pythonFile};
Process process = Runtime.getRuntime().exec(args);
int exitValue = process.waitFor();
BufferedInputStream in = new BufferedInputStream(process.getInputStream());
BufferedInputStream err = new BufferedInputStream(process.getErrorStream());
BufferedReader inBr = new BufferedReader(new InputStreamReader(in));
BufferedReader errBr = new BufferedReader(new InputStreamReader(err));
String lineStr;
while ((lineStr = inBr.readLine()) != null) {
logger.info(lineStr);
}
while ((lineStr = errBr.readLine()) != null) {
logger.error(lineStr);
}
inBr.close();
errBr.close();
in.close();
err.close();
*/