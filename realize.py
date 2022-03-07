#!/usr/bin/python3
import numpy as np

class Queue(list):
    def push(self,item):
        self.append(item)
    def pop(self):
        del self[0]
    def isempty(self):
        return not len(self)
    def front(self):
        return self[0]

class Node():
    id_number=0
    embarrassment=0
    current_path=''
    
graph=np.array([[False]*100]*100)
graph_1=np.array([[0]*100]*100)
result_path=''
result_embarrassment=0x3f
q=Queue()

def main():
    global result_path
    global result_embarrassment
    end=int(input('终点的编号，哦：'))
    path=int(input('节点之间一共有多少条路径，哦：'))
    for i in range(path):
        print('现在我们正在处理第',i+1,'条路径，哦',sep='')
        node_1=int(input('这条路的一端的节点的编号，哦：'))
        node_2=int(input('这条路的另一端的节点的编号，哦：'))
        people=int(input('这条路上有多少人，哦：'))
        graph[node_1][node_2]=True
        graph[node_2][node_1]=True
        graph_1[node_1][node_2]=people
        graph_1[node_2][node_2]=people
        if people==0:
            print('哇，这条路上竟然没有人呢，棒死了')
        print('-------------------------------------------')
    start=Node()
    start.id_number=1
    start.current_path='1'
    q.push(start)
    while not q.isempty():
        front=q.front()
        id_number=front.id_number
        current_path=front.current_path
        embarrassment=front.embarrassment
        if id_number==end:
            if embarrassment<result_embarrassment:
                result_embarrassment=embarrassment
                result_path=current_path
        available=[]
        for i in range(len(graph[id_number])):
            if graph[id_number][i]:
                if not str(i) in current_path:
                    available.append(i)
        possibility=[]
        for i in available:
            next_path=current_path+'->'+str(i)
            next_embarrassment=embarrassment+graph_1[id_number][i]
            next_id=i
            new_node=Node()
            new_node.current_path=next_path
            new_node.embarrassment=next_embarrassment
            new_node.id_number=next_id
            possibility.append(new_node)
        for i in range(len(possibility)):
            for j in range(1,len(possibility)):
                if possibility[i].embarrassment>possibility[j].embarrassment:
                    possibility[i],possibility[j]=possibility[j],possibility[i]
        for i in possibility:
            q.push(i)
        q.pop()
    print('哇，社死值最小的路径是',result_path,'呢，社死值是',result_embarrassment)
    
main()