//============================================================================
// Name        : Graph.cpp
// Author      : CX
// Version     :
// Copyright   : Graph Matrix List DFS BFS Dijstra Floyd Prim Kruskal 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "GraphAllInOne.h"

using namespace std;

int testGraphMatrix()
{
	//顶点
	char v[] = {'A','B','C','D','E','F','G'};
	vector<char> vexs;
	for(unsigned int i=0;i<sizeof(v)/sizeof(v[0]);i++)
		vexs.push_back(v[i]);
	EdgeData e[]={
			EdgeData('A','B',12),
			EdgeData('A','F',16),
			EdgeData('A','G',14),
			EdgeData('B','C',10),
			EdgeData('B','F',7),
			EdgeData('C','D',3),
			EdgeData('C','E',5),
			EdgeData('C','F',6),
			EdgeData('D','E',4),
			EdgeData('E','F',2),
			EdgeData('E','G',8),
			EdgeData('F','G',9),
	};
	vector<EdgeData>edges(sizeof(e)/sizeof(e[0]));
	for(unsigned int i=0;i<edges.size();i++)
	{
		edges[i]=e[i];
	}
	GraphAllInOne *pG = new GraphAllInOne(vexs,edges,'M');
	pG->PrintGraph();
	pG->IteratorBFS();
//	pG->IteratorDFS();
//	pG->Prim('A');
//	pG->Kruskal();
//	pG->Dijkstra('D');
//	pG->Floyd();
	delete pG;
	return 0;
}

int testGraphLink()
{
	//顶点
	char v[] = {'A','B','C','D','E','F','G'};
	vector<char> vexs;
	for(unsigned int i=0;i<sizeof(v)/sizeof(v[0]);i++)
		vexs.push_back(v[i]);
	EdgeData e[]={
			EdgeData('A','B',12),
			EdgeData('A','F',16),
			EdgeData('A','G',14),
			EdgeData('B','C',10),
			EdgeData('B','F',7),
			EdgeData('C','D',3),
			EdgeData('C','E',5),
			EdgeData('C','F',6),
			EdgeData('D','E',4),
			EdgeData('E','F',2),
			EdgeData('E','G',8),
			EdgeData('F','G',9),
	};
	vector<EdgeData>edges(sizeof(e)/sizeof(e[0]));
	for(unsigned int i=0;i<edges.size();i++)
	{
		edges[i]=e[i];
	}
	GraphAllInOne *pG;
	pG = new GraphAllInOne(vexs,edges,'L');
//	pG->PrintGraph();
	pG->IteratorBFS();
//	pG->IteratorDFS();
//	pG->Prim('A');
//	pG->Kruskal();
//	pG->Dijkstra('D');
//	pG->Floyd();
	delete pG;
	return 0;
}

int main() {
	cout << "Graph All in One" << endl; // prints Graph All in One
	testGraphLink();
	testGraphMatrix();
	return 0;
}
