// �����м���.cpp : �������̨Ӧ�ó������ڵ㡣
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
		printf("\n�����%.2f\n",result);
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
	int flag=0;   //��һλ�и�����Ϊ1

	len = end-start;
	cs=s+start;
	ce=s+end;//�����账��Ŀ�ͷ�ͽ�β
	if (cs[0]=='-') {
		flag=1;
		cs++;
	}
	//��ʼ��ȡ��
	for(i =0,j=0,k=0;i<128&&k<128&&j<=len;j++){            //i��������,k���ţ�j����ָ��
		if(cs[j]=='('){           //��ʼƥ������,�ݹ����
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
			j--;//j��λ
			ine=start+j-1;
			if(stack!=0) {
				printf("\n����ƥ����󣬼����˳�������%d\n",stack);
				Sleep(500);
				exit(1);
			}
			if(ins<=ine) {
				data[0][i]=f(s,ins,ine);//�������Ž�������ʱcs+jָ�����һ������
				i++;
			}
		}

		else if(cs[j]=='+'||cs[j]=='-'||cs[j]=='*'||cs[j]=='/'){ //������
			sscanf(cs+j,"%c",&syn[0][k]);
			k++;
		}
		else if('0'<cs[j]&&'9'>cs[j]||cs[j]=='.'){            //������
			sscanf(cs+j,"%f",&data[0][i]);
			while('0'<cs[j]&&'9'>cs[j]||cs[j]=='.'){
				j++;
			}
			j--; //while��λ
			i++; //����λ��һ
		}
	}
	if(flag==1) data[0][0]=-data[0][0]; //��λ��������
	//��ȡ��� ��������I �ܷ�����K (k=i-1)
	//��ʼ�˳����㣬�Է���ѭ�� data[t][] syn[t][p] iΪ�������� kΪ���ŵ�����
	for(p=0,t=0,i;p<k;p++){ 
		if(syn[t][p]=='*'||syn[t][p]=='/'){
			for(int m=0,n=0,tsyn=0;m<i;m++,n++){//�ƶ���n����ԭ���ķ��ţ�m����֮�������tsyn���ٷ���
				if(n==p) {
					n++; //��һλ
					if(syn[t][p]=='*') data[t+1][m]=data[t][n-1]*data[t][n];//�滻
					else data[t+1][m]=data[t][n-1]/data[t][n];
				}
				else {
					data[t+1][m]=data[t][n];
					if(n<k) syn[t+1][tsyn]=syn[t][n];
				}
			}
			t=(t+1)%2;
			i--;         //��������һ
			k--;		//���ż�һ
		}


	}
	//����Ӽ���
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
