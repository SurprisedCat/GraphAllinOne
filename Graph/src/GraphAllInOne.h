/*
 * GraphAllInOne.h
 *
 *  Created on: 2017年6月1日
 *      Author: lelouch
 */

#ifndef GRAPHALLINONE_H_
#define GRAPHALLINONE_H_

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <stack>
#include <cstring>
#include <stdio.h>
#include "datastructure.h"
#define MAX 52 //最多52个节点 A-Z a-z

class GraphAllInOne {
private:
	int mVexNum;//图的顶点数目
	int mEdgNum;//图的边的数目
	std::vector<EdgeData> edgesdata;

	VNode vertex[MAX];//邻接表

	int mMatrix[MAX][MAX];   // 邻接矩阵
	char mVertex[MAX];

private:
	int getPosition(char ch);//通过顶点的内容查找顶点的序号
	bool linkLast(VNode & v,ENode * e);//用在邻接表中，将邻接节点放到目标节点的表项中
	void DFS(int index,int* visited);//深度优先搜索的递归函数
	bool isEdgesEnqueued(char start,char end,const char q[][2],int dimension1) const;//用在prim算法查看边是否已经入队
	bool primIsRing(char s,char e,int *visited);
	int getWeight(int start, int end);//用在Dijkstra算法中,获取两点间边的权值
public:
	char types;//记录表明是邻接表还是矩阵

public:
	//vertex表示顶点；edges表示边；types: L 邻接表 M矩阵
	GraphAllInOne(std::vector<char> &vertex, std::vector<EdgeData> &edges, char p_types);
	//广度优先遍历
	int IteratorBFS();
	//深度优先遍历
	int IteratorDFS();
	//生成树 Prim算法
	std::queue<EdgeData> Prim(char v);//选取一个节点v开始
	//生成树Kruskal算法
	std::queue<EdgeData> Kruskal();
	//Dijkstra算法
	void Dijkstra(char v);//从顶点v开始计算最短路径
	//Floyd算法
	void Floyd();
	//打印出图
	void PrintGraph();
	//析构函数
	virtual ~GraphAllInOne();
};

#endif /* GRAPHALLINONE_H_ */
