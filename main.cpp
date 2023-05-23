#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<vector>

using namespace std;

const string filename = "graph4.txt";
struct Vertex;

struct Edge
{
    Vertex *start;  // ���
    Vertex *end;   // �յ�
    double weight; // Ȩ��
};

struct Vertex
{
    string name; // ��������
    set<Edge* > edges;  // ����ı�
};

struct Graph
{
    set<Vertex* > vertexs; // ���㼯��
    set<Edge* > edges;  // �߼���
    map<string, Vertex* > vertexMap; // �������Ƶ������ӳ��, ���ڿ��ٲ��Ҷ���
};

void initGraphFromFile(Graph & G)
{
    ifstream ifs(filename, ios::in);
    string v,s,e;
    double w;
    while(!ifs.eof())
    {
        ifs >> v;
        if(v=="vertex")
        {
            ifs >> v;
            Vertex * vertex = new Vertex; // ��������
            vertex->name = v; // ���ö�������
            G.vertexs.insert(vertex); // ��������뵽ͼ��
            G.vertexMap[v] = vertex; // ��������뵽�������Ƶ������ӳ����
        }
        else if(v=="edge")
        {
            ifs>>s>>e>>w;
            Edge * edge = new Edge; // ������
            edge->start = G.vertexMap[s]; // ���ñߵ����
            edge->end = G.vertexMap[e]; // ���ñߵ��յ�
            edge->weight = w; // ���ñߵ�Ȩ��
            G.edges.insert(edge); // ���߼��뵽ͼ��
            G.vertexMap[s]->edges.insert(edge); // ���߼��뵽���ı߼�����
        }
    }
}

void bellmanFord(const Graph&G,const Vertex* start) //startΪԴ��
{
// ��ʼ��
    map<Vertex*, double> dist; // ���㵽Դ��ľ���,�����Դ��Ϊͼ�еĵ�һ������
    map<Vertex*, Vertex*> path; // ���㵽Դ���·��  // �����Դ��Ϊͼ�еĵ�һ������
    for(auto & v : G.vertexs)
    {
        dist[v] = INT_MAX; // ��ʼ������Ϊ�����
        path[v] = nullptr; // ��ʼ��·��Ϊ��
    }
    dist[const_cast<Vertex*>(start)] = 0; // Դ�㵽Դ��ľ���Ϊ0

    // �ɳ�
    for(int i=0; i<G.vertexs.size()-1; ++i) // ִ��n-1���ɳڲ���
    {
        for(auto & e : G.edges) // �������б�
        {
            if(dist[e->start]!=INT_MAX && dist[e->end]>dist[e->start]+e->weight) // ������ڸ��̵�·��
            {
                dist[e->end] = dist[e->start]+e->weight; // ���¾���
                path[e->end] = e->start; // ����·��
            }
        }
    }

    // ��⸺Ȩ��·
    for(auto & e : G.edges) // �������б�
    {
        if(dist[e->start]!=INT_MAX && dist[e->end]>dist[e->start]+e->weight) // ������ڸ��̵�·��
        {
            cout << "���ڸ�Ȩ��·" << endl;
            return; // �㷨��ͬ��Dijkstra�㷨, ������ڸ�Ȩ��·, ���㷨�޷�����ִ��
        }
    }

    // ������
    for(auto & v : G.vertexs)
    {
        cout << v->name << ": ";
        if(dist[v]==INT_MAX)
        {
            cout << "���ɴ�" << endl;
            continue;
        }
        cout << "dist: " << dist[v] << " ";
        cout << "path: ";
        Vertex * p = path[v];
        while(p!=nullptr)
        {
            cout << p->name << " ";
            p = path[p];
        }
        cout << endl;
    }
}


int main()
{
    Graph G;
    initGraphFromFile(G);

    // --------���Դ���--------

//    cout << "�������: " << G.vertexs.size() << endl;
//    cout << "�߸���: " << G.edges.size() << endl;
//    cout << "�������Ƶ������ӳ���С: " << G.vertexMap.size() << endl;
//    cout << "���㼯��: " << endl;
//    for(auto & v : G.vertexs)
//    {
//        cout << v->name << endl;
//    }
//    cout << "�߼���: " << endl;
//    for(auto & e : G.edges)
//    {
//        cout << e->start->name << " " << e->end->name << " " << e->weight << endl;
//    }
//    cout << "����ı߼���: " << endl;
//    for(auto & v : G.vertexs)
//    {
//        cout << v->name << ": ";
//        for(auto & e : v->edges)
//        {
//            cout << e->start->name << " " << e->end->name << " " << e->weight << " ";
//        }
//        cout << endl;
//    }

    // --------���Դ���--------
    cout<<"������Դ�㣺"<<endl;
    string start;
    cin>>start;
    for(auto & v : G.vertexs)
    {
        if(v->name==start)
        {
            bellmanFord(G,v);
            return 0;
        }
    }
}