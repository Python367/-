#include<bits/stdc++.h>
using namespace std;

struct Node{
    int id_number;
    int embarrassment;
    string path;
    int arr_length;
};

int input(string notification=""){
    int content;
    cout<<notification;
    cin>>content;
    return content;
}

bool cmp(Node a,Node b){
    return a.embarrassment<b.embarrassment;
}

string result_path="";
int result_embarrassment=0x3f;
queue<Node> q;
bool graph[10005][10005];
int graph_1[10005][10005];
int node_1,node_2;
int people;
int destination;
int paths;

int main(){
    memset(graph,0,sizeof(graph));
    memset(graph_1,0,sizeof(graph_1));
    paths=input("节点之间一共有多少条路径：");
    destination=input("输入目的地：");
    for(int i=0;i<paths;i++){
        cout<<"我们现在正在处理第"<<i+1<<"条路径"<<endl;
        node_1=input("这条路的一端的节点的编号：");
        node_2=input("这条路的另一端的节点的编号：");
        people=input("这条路上有多少人：");
        graph[node_1][node_2]=graph[node_2][node_1]=1;
        graph_1[node_1][node_2]=graph_1[node_2][node_1]=people;
        cout<<"--------------------------------------------------"<<endl;
    }
    Node start;
    start.id_number=1;
    start.embarrassment=0;
    start.path="1";
    start.arr_length=1;
    q.push(start);
    while(!q.empty()){
        Node front=q.front();
        int id_number=front.id_number;
        int embarrassment=front.embarrassment;
        int length=front.arr_length;
        string path=front.path;
        if(id_number==destination){
            if(embarrassment<result_embarrassment){
                result_embarrassment=embarrassment;
                result_path=path;
            }
        }
        int available[1005];
        Node next_ones[1005];
        int index_n=0;
        int index_a=0;
        for(int i=1;i<=destination;i++){
            if(graph[id_number][i]){
                bool flag=true;
                for(int j=0;j<length;j++){
                    if(path[j]==i+'0'){
                        flag=false;
                        break;
                    }
                }
                if(flag){
                    available[index_a++]=i;
                }
            }
        }
        for(int i=0;i<index_a;i++){
            string next_path=path+"->"+to_string(available[i]);
            int next_embarrassment=embarrassment+graph_1[available[i]][id_number];
            int next_length=length+1;
            int next_id_number=available[i];
            Node new_one;
            new_one.id_number=next_id_number;
            new_one.arr_length=next_length;
            new_one.embarrassment=next_embarrassment;
            new_one.path=next_path;
            next_ones[index_n++]=new_one;
        }
        sort(next_ones,next_ones+index_n,cmp);
        for(int i=0;i<index_n;i++){
            q.push(next_ones[i]);
        }
        q.pop();
    }
    cout<<"社死值最小的路径是"<<result_path<<endl;
    return 0;
}
