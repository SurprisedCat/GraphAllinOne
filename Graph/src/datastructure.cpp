/*
 * datastructure.cpp
 *
 *  Created on: 2017年6月1日
 *      Author: lelouch
 */
#include "datastructure.h"
using namespace std;
VNode::VNode(char p_data, ENode *p_nextnode):data(p_data),next(p_nextnode)
{}
VNode::VNode():data('\0'),next(NULL)
{}

ENode::ENode(int p_vIndex, int p_weight,ENode *p_next):vIndex(p_vIndex),weight(p_weight),next(p_next)
{}
ENode::ENode():vIndex(-1),weight(INF),next(NULL)
{}

EdgeData::EdgeData(char s,char e,int w):start(s),end(e),weight(w)
{}
EdgeData::EdgeData():start('\0'),end('\0'),weight(INF)
{}
bool EdgeData::operator <(const EdgeData &a)const//重载<，实现less伪函数
{
	return this->weight>a.weight;
}
//并查集
UnionSet::UnionSet()
{
	for(int i=0;i<MAX;i++)
	{
		father[i] = 0;
		rank[i] = 0;
	}
}
//初始化
void UnionSet::makeSet(int x)
{
	father[x] = x; //根据实际情况指定的父节点可变化
	rank[x] = 0;   //根据实际情况初始化秩也有所变化
}
/* 查找x元素所在的集合,回溯时压缩路径*/
int UnionSet::findSet(int x)
{
	if(father[x] != x)
		x = findSet(father[x]);
	return father[x];
}
/*
按秩合并x,y所在的集合
下面的那个if else结构不是绝对的，具体根据情况变化
但是，宗旨是不变的即，按秩合并，实时更新秩。
*/
void UnionSet::myUnion(int x, int y)
{
	//找到x,y的集合根节点
	x = findSet(x);
	y = findSet(y);
	if(x == y) return ;//说明两个节点在一个集合中
	if(rank[x]>rank[y])//x集合的深度大于y，将x作为父集合
	{
		father[y] = x;
	}
	else
	{
		if(rank[x] == rank[y])//考虑两个深度一样的情况，将y作为父集合，同时深度加1
		{
			rank[y]++;
		}
		father[x] = y;////y集合的深度大于等于x，将y作为父集合
	}
}
