// 命令行计算.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

float cal(char *s); 
float f(char *s,int start,int end);

int _tmain(int argc, _TCHAR* argv[])
{
	char c[100];
	float result;
	int n;
	while(1) {
		printf("> ");
		gets(c);
		if((n=strlen(c))==0) break;
		result = f(c ,0,n-1);
		printf("\n结果：%.2f\n",result);
	} 

	system("pause");
	return 0;
}


float f(char *s,int start,int end){
	float data[2][128],result;
	char syn[2][128];
	char *cs,*ce;
	int ins,ine,len;
	int stack;
	int i,j,k,p,t,ns,te;
	int flag=0;   //第一位有负号则为1

	len = end-start;
	cs=s+start;
	ce=s+end;//定义需处理的开头和结尾
	if (cs[0]=='-') {
		flag=1;
		cs++;
	}
	//开始读取：
	for(i =0,j=0,k=0;i<128&&k<128&&j<=len;j++){            //i用于数据,k符号，j用于指针
		if(cs[j]=='('){           //开始匹配括号,递归调用
			stack=1;
			ins=start+j+1;
			j++;
			for(;j<=len;j++ ){
				if(cs[j]=='('){
					stack++;
				}
				if(cs[j]==')'){
					stack--;
				}
			}
			j--;//j回位
			ine=start+j-1;
			if(stack!=0) {
				printf("\n括号匹配错误，即将退出！参数%d\n",stack);
				Sleep(500);
				exit(1);
			}
			if(ins<=ine) {
				data[0][i]=f(s,ins,ine);//找右括号结束，此时cs+j指向最后一个括号
				i++;
			}
		}

		else if(cs[j]=='+'||cs[j]=='-'||cs[j]=='*'||cs[j]=='/'){ //读符号
			sscanf(cs+j,"%c",&syn[0][k]);
			k++;
		}
		else if('0'<cs[j]&&'9'>cs[j]||cs[j]=='.'){            //读数字
			sscanf(cs+j,"%f",&data[0][i]);
			while('0'<cs[j]&&'9'>cs[j]||cs[j]=='.'){
				j++;
			}
			j--; //while复位
			i++; //数据位加一
		}
	}
	if(flag==1) data[0][0]=-data[0][0]; //首位负数处理
	//读取完毕 总数字数I 总符号数K (k=i-1)
	//开始乘除计算，以符号循环 data[t][] syn[t][p] i为数的数量 k为符号的数量
	for(p=0,t=0,i;p<k;p++){ 
		if(syn[t][p]=='*'||syn[t][p]=='/'){
			for(int m=0,n=0,tsyn=0;m<i;m++,n++){//移动，n跟踪原来的符号，m跟踪之后的数，tsyn跟踪符号
				if(n==p) {
					n++; //跳一位
					if(syn[t][p]=='*') data[t+1][m]=data[t][n-1]*data[t][n];//替换
					else data[t+1][m]=data[t][n-1]/data[t][n];
				}
				else {
					data[t+1][m]=data[t][n];
					if(n<k) syn[t+1][tsyn]=syn[t][n];
				}
			}
			t=(t+1)%2;
			i--;         //待读数减一
			k--;		//符号减一
		}


	}
	//计算加减法
	result = data[t][0];
	for(p=0;p<k;p++){
		if(syn[t][p]=='+') {
			result=result+data[t][p+1];
		}
		if(syn[t][p]=='-') {
			result=result-data[t][p+1];
		}

	}

	return result;


}
