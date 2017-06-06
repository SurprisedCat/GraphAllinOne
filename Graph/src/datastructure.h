/*
 * datastructure.h
 *
 *  Created on: 2017年6月1日
 *      Author: lelouch
 */

#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

#define MAX 52
#include <cstring>

#define INF (~(0x01<<31)) // 定义最大值为0x7FFFFFFF

class ENode {
public:
	int vIndex;//指向的顶点序号
	int weight;//边的权重
	ENode *next;
public:
	ENode(int p_vIndex,int p_weight,ENode *p_next);
	ENode();
};

class VNode {
public:
	char data;
	ENode *next;
public:
	VNode(char p_data,ENode *p_next);
	VNode();
};

class EdgeData{
public:
	char start;//边的起点
	char end;	//边的终点
	int weight;//边的权重
public:
	EdgeData(char s,char e,int w);
	EdgeData();
	bool operator<(const EdgeData &a) const;//重载<，实现less伪函数
};

//并查集

class UnionSet
{
private:
	int father[MAX];   /* father[x]表示x的父节点*/
	int rank[MAX];     /*rank[x]表示x的秩*/
public:
	UnionSet();
	//初始化
	void makeSet(int x);
	/* 查找x元素所在的集合,回溯时压缩路径*/
	int findSet(int x);
	/*
	按秩合并x,y所在的集合
	下面的那个if else结构不是绝对的，具体根据情况变化
	但是，宗旨是不变的即，按秩合并，实时更新秩。
	*/
	void myUnion(int x, int y);
};
#endif /* DATASTRUCTURE_H_ */
