// �����м���.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf("������ʽ�Լ��㣬���������ݼ��˳�\n");
	while(1) {
		printf("> ");
		gets(c);                             //����
		if((n=strlen(c))==0) break;
		printf(">%.2f\n",f(c ,0,n-1));      //���㲢��ʾ
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
	int flag=0;   //��һλ�и�����Ϊ1

	len = end-start;
	cs=s+start;//�����账��Ŀ�ͷ�ͳ���
	
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
				else if(cs[j]==')'){
					stack--;
				}
				if (stack==0) break;
			}
			if(j==(len+1)) j--;//j��λ
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
		else if('0'<=cs[j]&&'9'>=cs[j]||cs[j]=='.'){            //������
			sscanf(cs+j,"%f",&data[0][i]);
			while('0'<=cs[j]&&'9'>=cs[j]||cs[j]=='.'){
				j++;
			}
			j--; //while��λ
			i++; //����λ��һ
		}
	}
	if(flag==1) data[0][0]=-data[0][0]; //��λ��������
	//��ȡ��� ��������I �ܷ�����K (k=i-1)


	//��ʼ�˳����㣬�Է���ѭ�� data[t][] syn[t][] iΪ�������� kΪ���ŵ�����
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
