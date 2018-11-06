#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5;

/* For generating random value of flag */
bool random()
{
    if (rand() % 2 == 0)
        return true;
    else
        return false;
}

/* For generating random value */
int myrandom(int i) 
{ 
    return rand() % i; 
}

struct vertex
{
    int id;
    string hex_id, parent;
    bool flag;
    vertex() {}
    vertex(int _id, string _hex_id, string _parent, bool _flag)
    {
        id = id;
        hex_id = _hex_id;
        parent = _parent;
        flag = _flag; 
    }
};

vector<vertex> adj[MAX];
int subtree[MAX], vis[MAX], cntAncestors[MAX];
;
int cnt[MAX];

vector<int> ancestors[MAX];
vector<int> rec_stack;

int ct = 0;
vector<int> answer;

/* For printing Direct Acylic Graph randomly generated */
void printDAG()
{
    for (int i = 1; i < MAX; ++i)
    {
        printf("i \t %d] ", i);

        for (auto &it : adj[i])
        {
            cout << "->" << it.id;
        }
        printf("\n");
    }
}

/* Function for prinitng list of children of required id */
void list_id(int id)
{
    bool cond = false;
    for (int i = 1; i < MAX; ++i)
    {
        if (i == id)
        {
            for (auto &it : adj[i])
            {
                cout << "->" << it.id;
                cond = true;
            }
        }

        if (cond == true)
            break;
    }
}

/* Function for prinitng list of children with either true/false valued
   vertex */
void conditional_list(bool flag)
{
    for (int i = 1; i < MAX; ++i)
    {
        for (auto &it : adj[i])
        {
            if (it.flag == flag)
                cout << "->" << it.id;
        }
        printf("\n");
    }
}
void reach_child(int k) /* Progeny (Count) for all the nodes is computed 
                           with pre-processing in O(V)*/
{
    if (vis[k])
        return;
    vis[k] = 1;
    subtree[k] = 1;
    for (auto &it : adj[k])
    {
        reach_child(it.id);
        subtree[k] += subtree[it.id];
    }
}

void reach_child2(int k) /* Progeny (IDS) for kth node is stored in answer*/
{
    answer.push_back(k);
    for (auto &it : adj[k])
        reach_child(it.id);
}

/*void reach_parent(int k) /*Ancestors (Count) for all the nodes is computed 
                             with pre-processing in O(V)
{
	cntAncestors[k]=ct;
	ct++;
	for(auto &it:adj[k])
		reach_parent(it.id);
	ct--;
}

void reach_parent2(int k) Ancestors (IDS) for kth node is stored in answer
{
	while(parent[k])
	{
		k=parent[k];
		answer.push_back(k);
	}
}*/

int main()
{
    srand(time(NULL));

    vector<int> left;
    vector<int> right;

    for (int index = 1; index <= MAX; index++)
    {

        right.push_back(index);
    }

    int element = right.back();
    left.push_back(element);
    right.pop_back();

    while (right.size())
    {
        stringstream ss;
        ss << hex << element;

        string res = ss.str();
        string hex_id = "0x";
        hex_id.append(res);
        random_shuffle(right.begin(), right.end(), myrandom);

        int random_vertex = right.back();
        ss << hex << random_vertex;
        string res2 = ss.str();
        string parent = "0x";
        parent.append(res2);

        right.pop_back();
        bool flag = random();
        adj[element].push_back(vertex(random_vertex, hex_id, parent, flag));
        left.push_back(random_vertex);
        element = right.back();
    }

    int ele = rand() % MAX;
    int flag1 = random();

    char option;
    char request;

    reach_child2(ele);

    do
    {
        cout << "Enter option (h for help message)\n";
        cin >> option;

        switch (option)
        {
        case 'h':
            cout << "Here are your options:\n";
            cout << "p - print the Direct Acyclic Graph\n";
            cout << "c - count the children of vertex\n";
            cout << "l - print list of children of vertex with requested id\n";
            cout << "m - print list of children of vertex with true/false flags\n";
            cout << "h - print help message\n";
            exit(0);
            break;
        case 'p':
            printDAG();
            break;
        case 'c':
            cout << answer[ele];
            break;
        case 'l':
            list_id(ele);
            break;
        case 'm':
            conditional_list(flag1);
            break;
        default:
            cout << "Error : option not avaliable\n";
        }
        cout << "\n Want to continue?(y/n)\n";
        cin >> request;
    } while (request == 'y');
    return 0;
}
