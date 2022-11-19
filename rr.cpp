#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct node
{
    string name;
    int app_id;
    vector<string> next;
    vector<string> deps;
};

struct app
{
    int id;
    int at;
    string type;
    string head;
    unordered_map<string, node *> ptr;
    unordered_set<string> fin;
};
vector<app> apps;

bool subtask_priority(node *a, node *b)
{
    if (apps[a->app_id].type != apps[b->app_id].type)
        return apps[a->app_id].type < apps[b->app_id].type;
    if (apps[a->app_id].at != apps[b->app_id].at)
        return apps[a->app_id].at < apps[b->app_id].at;
    return a->name < b->name;
}

void solution()
{
    int a, c;
    cin >> a >> c;
    unordered_map<string, vector<int>> etc;
    apps.resize(a);

    // constructing each app
    for (int i = 0; i < a; ++i)
    {
        apps[i].id = i + 1;
        cin >> apps[i].type >> apps[i].at;
        int nodes;
        cin >> nodes;

        // constructing each node
        for (int j = 0; j < nodes; ++j)
        {
            string name;
            cin >> name;
            if (j == 0)
                apps[i].head = name;

            if (apps[i].ptr.find(name) == apps[i].ptr.end())
            {
                apps[i].ptr[name] = new node();
                apps[i].ptr[name]->name = name;
                apps[i].ptr[name]->app_id = i;
            }

            // handling children relations
            int chil;
            cin >> chil;
            for (int k = 0; k < chil; ++k)
            {
                string nxt;
                cin >> nxt;
                if (apps[i].ptr.find(nxt) == apps[i].ptr.end())
                {
                    apps[i].ptr[nxt] = new node();
                    apps[i].ptr[nxt]->name = nxt;
                    apps[i].ptr[nxt]->app_id = i;
                }
                apps[i].ptr[nxt]->deps.push_back(name);
                apps[i].ptr[name]->next.push_back(nxt);
            }

            // computation times for current node
            vector<int> ct(c);
            for (int l = 0; l < c; ++l)
                cin >> ct[l];
            etc[name] = ct;
        }
    }

    // Allot each subtask to a computer using round robin algorithm
    vector<vector<node*>> cloud(c);
    unordered_set<string> alloted_subtask;
    for (int i = 0; i < a; ++i)
    {
        int cur_cloud = 0;
        queue<node *> q;
        q.push(apps[i].ptr[apps[i].head]);
        while (!q.empty())
        {
            node *n = q.front();
            q.pop();
            for (int j = 0; j < n->next.size(); ++j)
                if (alloted_subtask.find(apps[i].ptr[n->next[j]]->name) == alloted_subtask.end())
                {
                    q.push(apps[i].ptr[n->next[j]]);
                    alloted_subtask.insert(apps[i].ptr[n->next[j]]->name);
                }
            cloud[cur_cloud].push_back(n);
            cur_cloud = (cur_cloud + 1) % c;
        }
    }

    // Assign time slots of task execution according to different priorities
    for (auto &i : cloud)
        sort(i.begin(), i.end(), subtask_priority);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    solution();

#ifdef LOCAL_DEFINE
    cerr << "━━━━━━━━━━━━━━━━━" << '\n';
    cerr << "Time : " << (float)clock() / CLOCKS_PER_SEC << "s" << '\n';
#endif

    return 0;
}
