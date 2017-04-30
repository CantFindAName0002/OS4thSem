#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Node{
    string P;
    int at,bt,ct,tat,wt,rt;
    Node(string str, int a,int b)
    {
        P = str;
        at = a;
        bt = b;
    }
};

struct G{
    string P;
    int t;
    G(string str, int time)
    {
        P = str;
        t = time;
    }
};

bool func(Node a, Node b)
{
    return a.at < b.at;
}

bool func2(Node a, Node b)
{
    return a.bt < b.bt;
}

vector <Node> V, V2;
vector <G> Gantt;
int Burst[100],m=-1;
void Insert(), SJF();


int main()
{
    while(1)
    {
        int choice;
        cout<<"Choose\n1. Enter a process\n2. SJF scheduling\n3. exit\n";
        cin>>choice;

        switch(choice)
        {
            case 1: Insert();break;
            case 2: SJF(); break;
            case 3: exit(0);
        }
    }
    return 0;
}
void Insert()
{
    string P;
    int arr, burst;
    cout<<"Enter process name, its arrival time and burst time respectively\n";
    cin>>P>>arr>>burst;

    Burst[++m] = burst;
    V.push_back(Node(P,arr,burst));
    sort(V.begin(),V.end(),func);

    int len = V.size();
    for(int i=0;i<len-1;i++)
    {
        cout<<"|"<<V[i].P<<"|"<<V[i].at<<"|"<<V[i].bt<<"| --> ";
    }

    cout<<"|"<<V[len-1].P<<"|"<<V[len-1].at<<"|"<<V[len-1].bt<<"|\n";

}

void SJF()
{
    int len = V.size(),time,timeavail;
    string name;
    for(int i = 0;i<len-1 ;i++)
    {
        time = V[i].at;
        timeavail = V[i+1].at - V[i].at;
        for(int j=0;j<=i;j++)
        {
            V2.push_back(Node(V[j].P,V[j].at,V[j].bt));
        }
        sort(V2.begin(),V2.end(),func2);
        int len2 = V2.size();

        for(int j=0;j<len2;j++)
        {
            if(V2[j].bt != 0)
            {
                name = V2[j].P;
                break;
            }
        }


        for(int j=0;j<len;j++)
        {
            if(name == V[j].P)
            {
                if(V[j].bt <= timeavail)
                {
                    V[j].bt = 0;
                    time += (timeavail - V[j].bt);
                    V[j].ct = time;
                    V[j].tat = V[j].ct - V[j].at;
                   // V[j].wt = V[j].tat - Burst[j];
                    Gantt.push_back(G(V[j].P, V[j].ct));
                }
                else
                {
                    V[j].bt -= timeavail;
                    time += timeavail;
                    Gantt.push_back(G(V[j].P, time));
                }
                break;
            }
        }

        V2.erase(V2.begin(),V2.end());
    }

    sort(V.begin(),V.end(),func2);

    len = V.size();
    for(int i = 0;i<len;i++)
    {
        if(V[i].bt != 0)
        {
            time += V[i].bt;
            V[i].ct = time;
            V[i].tat = V[i].ct - V[i].at;
          //  V[i].wt = V[i].tat - Burst[i];
            Gantt.push_back(G(V[i].P, V[i].ct));
        }
    }

    cout<<"\n\nGANTT CHART:\n\n";

    int leng = Gantt.size();
    for(int i=0;i<leng-1;i++)
    {
        cout<<Gantt[i].P<<"|"<<Gantt[i].t<<"| --> ";
    }
    cout<<Gantt[leng-1].P<<"|"<<Gantt[leng-1].t<<"|\n";

    len = V.size();

    sort(V.begin(),V.end(),func);
    cout<<"\n\nDETAILS OF PROCESSES:\n\nPname\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(int i=0;i<len;i++)
    {
        for(int j = 0;j<leng;j++)
        {
            if(V[i].P == Gantt[j].P)
            {
                if(j == 0)
                    V[i].rt = 0;
                else
                    V[i].rt = Gantt[j-1].t;

                break;
            }
        }
        cout<<V[i].P<<"\t"<<V[i].at<<"\t"<<Burst[i]<<"\t"<<V[i].ct<<"\t"<<V[i].tat<<"\t"<<V[i].tat-Burst[i]<<"\t"<<V[i].rt<<"\n";
    }

}
