// 命令行计算.cpp : 定义控制台应用程序的入口点。
// 

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
float f(char *s,int start,int end);

int _tmain(int argc, _TCHAR* argv[])
{
	char c[100];
	int n;
	printf("键入表达式以计算，无输入内容即退出\n");
	while(1) {
		printf("> ");
		gets(c);                             //输入
		if((n=strlen(c))==0) break;
		printf(">%.2f\n",f(c ,0,n-1));      //计算并显示
	} 

	system("pause");
	return 0;
}


float f(char *s,int start,int end){
	float data[2][128],result;
	char syn[2][128];
	char *cs;
	int ins,ine,len;
	int stack;
	int i,j,k,p,t,m;
	int flag=0;   //第一位有负号则为1

	len = end-start;
	cs=s+start;//定义需处理的开头和长度
	
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
				else if(cs[j]==')'){
					stack--;
				}
				if (stack==0) break;
			}
			if(j==(len+1)) j--;//j回位
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
		else if('0'<=cs[j]&&'9'>=cs[j]||cs[j]=='.'){            //读数字
			sscanf(cs+j,"%f",&data[0][i]);
			while('0'<=cs[j]&&'9'>=cs[j]||cs[j]=='.'){
				j++;
			}
			j--; //while复位
			i++; //数据位加一
		}
	}
	if(flag==1) data[0][0]=-data[0][0]; //首位负数处理
	//读取完毕 总数字数I 总符号数K (k=i-1)


	//开始乘除计算，以符号循环 data[t][] syn[t][] i为数的数量 k为符号的数量
	t=0;
	p=0;
	while(p<k){
		if(syn[t][p]=='*'||syn[t][p]=='/'){
			int step=0;
			m=(t+1)%2;
			for(int tpr=0;tpr<=k;tpr++){
				if(tpr==p) {
					if(syn[t][p]=='*') data[m][tpr]=data[t][tpr]*data[t][tpr+1];
					else data[m][tpr]=data[t][tpr]/data[t][tpr+1];
					step=1;
				}
				else{
					if(tpr<k) syn[m][tpr-step]=syn[t][tpr];
					data[m][tpr]=data[t][tpr+step];
				}
			}
			t=m;
			k--;
			p=0;
		}
		else p++;
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
