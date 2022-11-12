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

void solution()
{
    int a, c;
    // cout << "Enter no. of apps and clouds: ";
    cin >> a >> c;
    unordered_map<string, vector<int>> etc;
    vector<app> apps(a);

    // constructing each app
    for (int i = 0; i < a; ++i)
    {
        apps[i].id = i + 1;
        // cout << "Enter clound type and arrival time of cloud " << i + 1 << ": ";
        cin >> apps[i].type >> apps[i].at;
        int nodes;
        // cout << "Enter number of nodes in this app: ";
        cin >> nodes;

        // constructing each node
        for (int j = 0; j < nodes; ++j)
        {
            string name;
            // cout << "Name of subtask: ";
            cin >> name;
            if (j == 0)
                apps[i].head = name;

            node *n = nullptr;
            if (apps[i].ptr.find(name) == apps[i].ptr.end())
                apps[i].ptr[name] = new node();

            // handling children relations
            int chil;
            // cout << "No. of subtasks dependent on " << name << ": ";
            cin >> chil;
            for (int k = 0; k < chil; ++k)
            {
                string nxt;
                // cout << "Next node " << k << ": ";
                cin >> nxt;
                if (apps[i].ptr.find(nxt) == apps[i].ptr.end())
                {
                    apps[i].ptr[nxt] = new node();
                    apps[i].ptr[nxt]->name = nxt;
                }
                apps[i].ptr[nxt]->deps.push_back(name);
                apps[i].ptr[name]->next.push_back(nxt);
                // cout << *apps[i].ptr[name]->next.begin();
            }

            // computation times for current node
            vector<int> ct(c);
            // cout << "Computation times of " << name << ": ";
            for (int l = 0; l < c; ++l)
                cin >> ct[l];
            etc[name] = ct;
        }
    }

    // cout << apps[0].head << '\n';
    vector<vector<string>> cloud(c);
    int cur_cloud = 0;
    for (int i = 0; i < a; ++i) {
        queue<node*> q;
        q.push(apps[i].ptr[apps[i].head]);
        while (!q.empty()) {
            node* n = q.front();
            q.pop();
            // cout << n->name << ' ' << c << '\n';
            for (int j = 0; j < n->next.size(); ++j)
                q.push(apps[i].ptr[n->deps[j]]);
                // cout << apps[i].ptr[n->deps[j]]->name << '\n';
            cloud[cur_cloud].push_back(n->name);
            cur_cloud = (cur_cloud + 1) % c;
        }
    }
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
