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
#include <stdlib.h>
#define Pi 3.1415926
#define LENGTH_MAX (1024*1024)
using namespace std;
double cacul_value[LENGTH_MAX];
int a[LENGTH_MAX] = { 5,9,4,8,3,7,2,6,1,0};
int switch_t = 0;
int b[LENGTH_MAX];
int c0[LENGTH_MAX];

void switch_arr(int i ,int count){
	//printf("pos：%d cnt:%d ", i, count);
	for(int j = 0; j <= count/2; j++){
		int temp = a[i+j];
		a[i+j] = a [ i + count - j];
		a [ i + count - j] = temp;
		//printf("after switch %d %d \n", a[i+j],a [ i + count - j]);
		}
	}
void TestSort(){
for (int k = 0; k < LENGTH_MAX; k++){
	for (int j = 0; j < LENGTH_MAX - 1; j++){
		if ( a[j] > a[j+1] ) b[j] = 1;
		else b[j] = 0;
		//cout<<b[j];
		}
	int beg = 0;
	int count = 0;
	//int beg_0 = 0;
	//int count_0 = 0;
	bool flag = true;
	for (int j = 0; j < LENGTH_MAX - 1; j++){
		if ( b[j] == 1) {
			if (!count) beg = j;
			count ++;
			if (j == LENGTH_MAX - 2){
				switch_arr(beg,count);
				count = 0;
				flag = false;
			}
		}else {
			if (count > 0){
				switch_arr(beg,count);
				count = 0;
				flag = false;
			}
		}
	}

//printf("\n\nafter k = %d\n", k );
	if(flag) break;
	for (int i = 0; i < LENGTH_MAX; i++){
		//a[i] = rand()%LENGTH_MAX;
		//cout << a[i]<<endl;
		}
}
}
void Test(int a){
    double max = 100;
    int ret = max*tanh(a/max);
    printf("ret:%d\n", ret);

    double rate = tanh(a/max);
    printf("rete:%lf\n", rate);
    
    double reduce;
    reduce = tanh(a/max);
    printf("reduce:%lf\n", reduce);
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
void pre_sort(){
		for (int j = 0; j < LENGTH_MAX - 1; j++){
		if ( a[j] > a[j+1] ) b[j] = 1;
		else b[j] = 0;
		//cout<<b[j];
		switch_t++;
		}
	int beg = 0;
	int count = 0;
	for (int j = 0; j < LENGTH_MAX - 1; j++){
		if ( b[j] == 1) {
			if (!count) beg = j;
			count ++;
			if (j == LENGTH_MAX - 2){
				switch_arr(beg,count);
				count = 0;
			}
		}else {
			if (count > 0){
				switch_arr(beg,count);
				count = 0;
			}
		}
	}
}

void testQsort(int arr[], int low, int high){
	if(low>=high) return;	//拆分只有一个元素的情况
	int first = low;		//记录界限位置
	int last = high;
	int key = arr[first];	//用第一个作为界线 拆分为两组

    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
            switch_t++;
        }
        a[first] = a[last];	/*将比第一个小的移到低端*/
        while(first < last && a[first] <= key)
        {
            ++first;
            switch_t++;
        }
        a[last] = a[first]; /*将比第一个大的移到高端*/
    }

	arr[first] = key;
	testQsort(arr, low, first - 1);
	testQsort(arr, first +1, high);
	}


int main(int argc, char **argv)
{
	//testMathFun();
	//Test(50);
	for (int i = 0; i < LENGTH_MAX; i++){
		a[i] = rand()%LENGTH_MAX;
		//cout << a[i]<<endl;
	}
	clock_t t_beg,t_end;
	t_beg = clock();
	pre_sort();
	testQsort(a, 0, LENGTH_MAX - 1 );
	//TestSort();
	t_end = clock();
	for (int i = 0; i < LENGTH_MAX; i++){
		//a[i] = rand()%LENGTH_MAX;
		cout << a[i]<<endl;
	}

	cout <<"time elapse:"<< (double)(t_end - t_beg)/CLOCKS_PER_SEC <<"\t"<<switch_t<<endl;
	return 0;
}

