/*
 * main.cxx
 * 
 * Copyright 2016 vicent <vicent@vicentPC>
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
#include <cmath>
#include <stdio.h>
#define Pi 3.1415926
#define LENGTH_MAX (1024*1024)
using namespace std;
double cacul_value[LENGTH_MAX];
void Test(int a){
    double max = 100;
    int ret = max*tanh(a/max);
    printf("ret:%d\n", ret);
    double rate = tanh(a/max);
    printf("rete:%lf", rate);
}
void testMathFun(){
	clock_t t_beg,t_end;
	t_beg = clock();
	for(int i = 0; i < LENGTH_MAX; i++){
		//cacul_value[i] = 1 - exp(-i/100.0);
		//cacul_value[i] = 2/Pi *atan((i%1024)/100.0);
		//cacul_value[i] = sqrt(i);
		//cacul_value[i] = tanh(i);
		}
	t_end = clock();
	for (int i = 0; i < LENGTH_MAX ;i++){
		//cout << "i:"<<i<<'\t'<<cacul_value[i] <<'\n';
		}
	cout <<"time elapse:"<< (double)(t_end - t_beg)/CLOCKS_PER_SEC <<endl;
	}
int main(int argc, char **argv)
{
	//testMathFun();
	Test(50);
	return 0;
}

