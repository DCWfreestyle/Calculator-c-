﻿========================================================================
    控制台应用程序：命令行计算 项目概述
========================================================================

应用程序向导已为您创建了此 命令行计算 应用程序。

本文件概要介绍组成 命令行计算 应用程序的每个文件的内容。


命令行计算.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

命令行计算.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。它包含有关项目文件与筛选器之间的关联信息。在 IDE 中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。例如，“.cpp”文件与“源文件”筛选器关联。

命令行计算.cpp
    这是主应用程序源文件。

/////////////////////////////////////////////////////////////////////////////
其他标准文件:

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 命令行计算.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

/////////////////////////////////////////////////////////////////////////////
其他注释:

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////
for(p=0,t=0,i;p<k;p++){ 
		if(syn[t][p]=='*'||syn[t][p]=='/'){
			for(int m=0,n=0,tsyn=0,tdat=0;n<=k;m++,n++){//移动，n跟踪原来的符号，m跟踪原来的数，tsyn跟踪符号,tdat跟踪数
				if(n==p) {
					if(syn[t][p]=='*') data[t+1][tdat]=data[t][m]*data[t][m+1];//替换
					else data[t+1][m]=data[t][n]/data[t][n+1];
					m++;
					tdat++;
				}
				else {
					data[t+1][tdat]=data[t][m];
					tdat++;
					if(n<=k) {
						syn[t+1][tsyn]=syn[t][n];
						tsyn++;
					}
				}
			}
			t=(t+1)%2;
			i--;         //待读数减一
			k--;		//符号减一
		}


	}