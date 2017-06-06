/*
 * GraphAllInOne.cpp
 *
 *  Created on: 2017年6月1日
 *      Author: lelouch
 */

#include "GraphAllInOne.h"

using namespace std;
	//vertex表示顶点；edges表示边；types: L 邻接表 M矩阵
	GraphAllInOne::GraphAllInOne(vector<char> &vex,vector<EdgeData> &edges,char p_types)
	{
		//常用参数初始化
		types = p_types;
		mVexNum = vex.size();
		mEdgNum = edges.size();
		edgesdata = edges;
		memset(mMatrix,0,sizeof(int)*MAX*MAX);
		memset(vertex,0,sizeof(VNode)*MAX);
		if(types == 'L')
		{
			//初始化
			for(int i=0;i<mVexNum;i++)
			{
				vertex[i].data = vex[i];
				vertex[i].next = NULL;
			}
			for(int i = 0;i<mEdgNum;i++)
			{
				char start = edges[i].start;
				char end = edges[i].end;
				int weight = edges[i].weight;

				int p1 = getPosition(start);
				int p2 = getPosition(end);
				if(p1 == -1 || p2 == -1)
					abort();
				ENode *node1 = new ENode(p2,weight,NULL);//这是p1--p2这条边的数据，放到p1的邻接表项中
				if(!linkLast(vertex[p1],node1))
					abort();
				ENode *node2 = new ENode(p1,weight,NULL);//这是p1--p2这条边的数据，放到p2的邻接表项中
				if(!linkLast(vertex[p2],node2))
					abort();
			}
		}
		else if(types == 'M')
		{
			for(int i = 0;i<mVexNum;i++)
			{
				mVertex[i] = vex[i];//将节点数据存储到队列中，不使用VNode
				for(int j=0;j<mVexNum;j++)
				{
					if(i!=j)
						mMatrix[i][j] = INF;
					else
						mMatrix[i][j] = 0;
				}
			}
			for(vector<EdgeData>::iterator it=edgesdata.begin();it!=edgesdata.end();it++)
			{
				cout<<getPosition(it->start)<<getPosition(it->end)<<endl;
				mMatrix[getPosition(it->start)][getPosition(it->end)] = it->weight;
				mMatrix[getPosition(it->end)][getPosition(it->start)] = it->weight;
			}
		}
		else
		{
			cout<<"Types Error";
			abort();
		}
	}
	//广度优先遍历
	int GraphAllInOne::IteratorBFS()
	{
		cout<<"BFS: "<<endl;
		//使用队列实现图的广度遍历
		queue<int> q;
		//设置访问标志,并初始化为0（未访问）
		int visited[mVexNum];
		for(int i=0;i<mVexNum;i++)
			visited[i]=0;
		//邻接表存储
		if(types == 'L')
		{
			for(int i=0;i<mVexNum;i++)//遍历各个顶点
			{
				if(!visited[i])
				{
					q.push(i);//入队列的时候记录visited
					visited[i] = 1;
					cout<<vertex[i].data<<" ";
					while(!q.empty())
					{
						int qfront = q.front();//出队列，并入队其所有邻接的顶点
						q.pop();
						ENode * e = vertex[qfront].next;
						while(e != NULL)//邻接表有顶点，并且这个顶点未被访问过，则入队
						{
							if(!visited[e->vIndex])
							{
								q.push(e->vIndex);
								visited[e->vIndex] = 1;
								cout<<vertex[e->vIndex].data<<" ";
							}

							e = e->next;
						}
					}
				}
			}
		}
		if(types == 'M')
		{

		}
		cout<<endl;
		return 1;
	}
	//深度优先遍历 递归函数
	void GraphAllInOne::DFS(int index,int* visited)
	{
		if(types == 'L')
		{
			cout<<vertex[index].data<<" ";
			visited[index] = 1;
			ENode *e = vertex[index].next;
			while(e != NULL)
			{
				if(!visited[e->vIndex])
					DFS(e->vIndex,visited);
				e = e->next;
			}
		}
	}
	//深度优先遍历
	int GraphAllInOne::IteratorDFS()
	{
		//使用递归实现图的深度遍历
		cout<<"DFS: "<<endl;
		//设置访问标志,并初始化为0（未访问）
		int visited[mVexNum];
		for(int i=0;i<mVexNum;i++)
			visited[i]=0;
		if(types=='L')
		{
			for(int i=0;i<mVexNum;i++)
			{
				if(!visited[i])
				{
					DFS(i,visited);
				}
			}
		}
		if(types=='M')
		{

		}
		cout<<endl;
		return 1;
	}
	//用在Prim算法中，判断是否已经入队列
	bool GraphAllInOne::isEdgesEnqueued(char start,char end,const char q[][2],int dimension1) const
	{
		for(int i=0;i<dimension1;i++)
		{
			if((q[i][0] == start && q[i][1] == end) || (q[i][0] == end && q[i][1] == start))
				return true;
		}
		return false;
	}
	//在Prim算法中判读边是否成环
	bool GraphAllInOne::primIsRing(char s,char e,int*visited)
	{
		int p1 = getPosition(s);
		int p2 = getPosition(e);
		if(visited[p1] && visited[p2])
			return true;
		return false;
	}
	//生成树 Prim算法
	queue<EdgeData> GraphAllInOne::Prim(char v)//选取一个节点v开始
	{
		cout<<"Prim: "<<endl;
		queue<EdgeData> result;//存放最终结果
		if(types=='L')
		{
			int p = getPosition(v);//从char--》节点位置
			int visited[mVexNum];
			for(int i=0;i<mVexNum;i++)
				visited[i]=0;
			visited[p] = 1;//从p开始访问
			priority_queue<EdgeData,vector<EdgeData>,less<EdgeData> > pq;
			char enqueued[mEdgNum][2];
			int counter=0;//边的计数器
			for(int i=0;i<mVexNum-1;i++)//运行mVexNum-1次，找到mVexNum-1条边
			{
				ENode *elink = vertex[p].next;//将p相邻的边入队列
				while(elink != NULL)
				{
					if(!isEdgesEnqueued(vertex[p].data,vertex[elink->vIndex].data,enqueued,mEdgNum))
					{
						pq.push(EdgeData(vertex[p].data,vertex[elink->vIndex].data,elink->weight));
						enqueued[counter][0] = vertex[p].data;
						enqueued[counter][1] = vertex[elink->vIndex].data;
						counter++;
					}
					elink = elink->next;
				}
				bool flag = false;//记录是否找到合适的边
				while(!flag)
				{
					EdgeData smallest = pq.top();
					pq.pop();
					if(primIsRing(smallest.start,smallest.end,visited))//判断是否有一个环
						continue;
					else//增加的边没有形成环路
					{
						flag = true;
						result.push(smallest);
					}
				}
				cout<<result.back().start<<"---"<<result.back().end<<"---"<<result.back().weight<<endl;
				p = getPosition(result.back().end);//这个是本次找到的新节点
				visited[p] = 1;//将这个节点标志位已经访问
			}
		}
		if(types=='M')
		{


		}
		return result;
	}
	//生成树Kruskal算法
	queue<EdgeData> GraphAllInOne::Kruskal()
	{
		queue<EdgeData> result;
		if(types=='L')
		{
			cout<<"Kruskal:"<<endl;
			//初始化并查集参数
			UnionSet myUnion;
			for(int i=0;i<mVexNum;i++)
				myUnion.makeSet(i);
			//将所有的边放到一个优先级队列中
			priority_queue<EdgeData,vector<EdgeData>,less<EdgeData> > pq;
			char enqueued[mEdgNum][2];
			int counter=0;//边的计数器
			for(int i=0;i<mVexNum;i++)
			{
				ENode *elink = vertex[i].next;//将p相邻的边入队列
				while(elink != NULL)
				{
					if(!isEdgesEnqueued(vertex[i].data,vertex[elink->vIndex].data,enqueued,mEdgNum))
					{
						pq.push(EdgeData(vertex[i].data,vertex[elink->vIndex].data,elink->weight));
						enqueued[counter][0] = vertex[i].data;
						enqueued[counter][1] = vertex[elink->vIndex].data;
						counter++;
					}
					elink = elink->next;
				}
			}
			for(int i=0;i<mVexNum-1;i++)//找到那些边
			{
				int flag = 0;//找到合适边的标记
				while(!flag)
				{
					EdgeData nextEdge = pq.top();
					pq.pop();
					int p1 = getPosition(nextEdge.start);
					int p2 = getPosition(nextEdge.end);
					if(myUnion.findSet(p1) == myUnion.findSet(p2))
					{
						continue;
					}
					flag =1;//这条边合适
					//并查集
					myUnion.myUnion(p1,p2);
					result.push(nextEdge);
					cout<<result.back().start<<"---"<<result.back().end<<"---"<<result.back().weight<<endl;
				}
			}
		}
		if(types=='M')
		{

		}
		return result;
	}

	//用于D算法
	/*
	 * 获取边<start, end>的权值；若start和end不是连通的，则返回无穷大。
	 */
	int GraphAllInOne::getWeight(int start, int end)
	{
	    ENode *e;
	    if (start==end)
	        return 0;

	    e = vertex[start].next;
	    while (e!=NULL)
	    {
	        if (end == e->vIndex)
	            return e->weight;
	        e = e->next;
	    }
	    return INF;
	}
	//Dijkstra算法
	void GraphAllInOne::Dijkstra(char v)//从顶点v开始计算最短路径
	{
		cout<<"Dijkstra Algorithm for "<<v<<endl;
		// prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
		int prev[mVexNum];
		for(int i=0;i<mVexNum;i++)
			prev[i]=i;
		//长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
		int dist[mVexNum];
		for(int i=0;i<mVexNum;i++)
			dist[i] = INF;
		//访问标识符
		bool visited[mVexNum];
		for(int i=0;i<mVexNum;i++)
			visited[mVexNum] = false;
		if(types=='L')
		{
			int p = getPosition(v);//找出顶点的位置
			dist[p] = 0;//自身的距离是0
			visited[p] = true;
			//循环mVexNum次，每一次找出一个顶点
			for(int i=0;i<mVexNum-1;i++)
			{
				int nextIndex = p;
				int tempMin = INF;
				for(int j=0;j<mVexNum;j++)
				{
					if(!visited[j])
					{
						int w = getWeight(p, j);
						int newDist = (w == INF? INF:(dist[p]+w));//放置w溢出，因为设置INF 为0x7fffffff
						if(newDist<dist[j])//更新距离
						{
							dist[j]=newDist;
							prev[j] = p;//这一轮找出的prev是p

						}
						if(tempMin > dist[j])//找出这一轮中最小权值的点
						{
							tempMin = dist[j];
							nextIndex = j;
						}
					}
				}
				visited[nextIndex] = true;
				p = nextIndex;
			}
			for(int i=0;i<mVexNum;i++)
			{
				cout<<"start with "<<v<<" to "<<vertex[i].data<<", distance is "<<dist[i]<<endl;
				cout<<"The trace is:";
				int traceIndex = i;
				stack<char> outputDijkstra;
				while(traceIndex != getPosition(v))
				{
					outputDijkstra.push(vertex[traceIndex].data);
					traceIndex = prev[traceIndex];
				}
				outputDijkstra.push(v);
				while(!outputDijkstra.empty())
				{
					cout<<outputDijkstra.top()<<" ";
					outputDijkstra.pop();
				}
				cout<<endl;
			}
		}
		if(types=='M')
		{

		}
	}
	//Floyd算法
	void GraphAllInOne::Floyd()
	{
		if(types=='L')
		{
			//floyd算法用邻接表很麻烦，所以生成矩阵
			int dist[mVexNum][mVexNum];
			int path[mVexNum][mVexNum];
			for(int i=0;i<mVexNum;i++)
			{
				for(int j=0;j<mVexNum;j++)
				{
					dist[i][j] = getWeight(i, j);//"顶点i"到"顶点j"的路径长度为"i到j的权值"。
					path[i][j] = j;//初始化路径表为j,"顶点i"到"顶点j"的最短路径是经过顶点j。
				}
			}
			for(int k=0;k<mVexNum;k++)
			{
				for(int i=0;i<mVexNum;i++)
				{
					for(int j=0;j<mVexNum;j++)
					{
		                // 如果经过下标为k顶点路径比原两点间路径更短，则更新dist[i][j]和path[i][j]
		                int tmp = (dist[i][k]==INF || dist[k][j]==INF) ? INF : (dist[i][k] + dist[k][j]);
		                if (dist[i][j] > tmp)
					   {
						   // "i到j最短路径"对应的值设，为更小的一个(即经过k)
						   dist[i][j] = tmp;
						   // "i到j最短路径"对应的路径，经过k
						   path[i][j] = path[i][k];
					   }
					}
				}
			}
			 // 打印floyd最短路径的结果
			cout << "floyd: " << endl;
			cout<<"Weight: "<<endl;
			for (int i = 0; i < mVexNum; i++)
			{
				for (int j = 0; j < mVexNum; j++)
					cout << setw(2) << dist[i][j] << "  ";
				cout << endl;
			}
			cout<<"Path: "<<endl;
			for (int i = 0; i < mVexNum; i++)
			{
				for (int j = 0; j < mVexNum; j++)
					cout << setw(2) << path[i][j] << "  ";
				cout << endl;
			}
		}
		if(types=='M')
		{

		}
	}
	//打印出图
	void GraphAllInOne::PrintGraph()
	{
		if(types=='L')
		{
			cout<<"List Graph:"<<endl;
			for(int i=0;i<mVexNum;i++)
			{
				cout << i << "(" << vertex[i].data << "): ";
				ENode *node = vertex[i].next;
				while (node != NULL)
				{
					cout << node->vIndex << "(" << vertex[node->vIndex].data << ") ";

					node = node->next;
				}
				cout << endl;
			}
		}
		if(types=='M')
		{
			cout<<"Matrix Graph:"<<endl;
			//printGraph(mMatrix, mVexNum);
		}
	}

	void GraphAllInOne::printGraph(int vlen,int &M[vlen][vlen])
	{
		cout<<setw(2)<<'M'<<" ";
		for(int i = 0;i<vlen;i++)
			cout<<setw(2)<<mVertex[i]<<" ";
		cout<<endl;
		for(int i=0;i<vlen;i++)
		{
			cout<<setw(2)<<mVertex[i]<<" ";
			for(int j=0;j<vlen;j++)
			{
				if(M[i][j] != INF)
					cout<<setw(2)<<M[i][j]<<" ";
				else
					cout<<setw(2)<<"N"<<" ";
			}
			cout<<endl;
		}
	}
	//通过节点内容寻找节点序号
	int GraphAllInOne::getPosition(char ch)
	{
		if(types == 'L')
		{
			for(int i=0;i<mVexNum;i++)
			{
				if(ch == vertex[i].data)
					return i;
			}
		}
		if(types == 'M')
		{
			for(int i=0;i<mVexNum;i++)
				if(ch == mVertex[i])
					return i;
		}
		return -1;
	}
	//用在邻接表中，将邻接节点放到目标节点的表项中
	bool GraphAllInOne::linkLast(VNode & v,ENode * e)
	{
		if(v.next == NULL)
		{
			v.next = e;
			return true;
		}
		else
		{
			ENode * temp = v.next;
			while(temp->next)
			{
				temp = temp->next;
			}

			temp->next = e;
			return true;
		}
		return false;
	}
	//析构函数
	GraphAllInOne::~GraphAllInOne()
	{
		if(types == 'L')
		{
//			cout<<"Destroy the linked list 'new'ed before."<<endl;
			for(int i=0;i<mVexNum;i++)//delete之前new出来的链表
			{
//				cout<<"delete:";
				if(vertex[i].next != NULL)
				{
					ENode *e = vertex[i].next;
					ENode *n = vertex[i].next;
 					while(e != NULL)
 					{
 						e = n->next;
// 						cout<<vertex[i].data<<n->vIndex<<" ";
 						delete n;
 						n = e;
 					}
// 					cout<<endl;
				}
			}
		}
		if(types == 'M')
		{
			cout<<"Matrix Destroyed"<<endl;
		}
	}
