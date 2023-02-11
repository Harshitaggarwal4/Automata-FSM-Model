#include <bits/stdc++.h>
using namespace std;
#define int long long int
struct state
{
    int name;
    int rock;
    int paper;
    int scissor;
};
void state_copy(state &a, state &b)
{
    a.name = b.name;
    a.rock = b.rock;
    a.paper = b.paper;
    a.scissor = b.scissor;
}
int solve(vector<state> &input, vector<state> &output, int &count, vector<set<int>> &nodes, int play, int change)
{
    if (nodes[nodes.size() - 1].size() == 1)
    {
        int state_number = *nodes[nodes.size() - 1].begin();
        output[count].name = (input[state_number].name + 1) % 3;
        if (output[count].name == 0)
        {
            output[count].rock = input[state_number].rock;
            output[count].paper = input[state_number].rock;
            output[count].scissor = input[state_number].rock;
        }
        else if (output[count].name == 1)
        {
            output[count].rock = input[state_number].paper;
            output[count].paper = input[state_number].paper;
            output[count].scissor = input[state_number].paper;
        }
        else
        {
            output[count].rock = input[state_number].scissor;
            output[count].paper = input[state_number].scissor;
            output[count].scissor = input[state_number].scissor;
        }
        count++;
        return count - 1;
    }
    else if (nodes[nodes.size() - 1].size() == 0)
    {
        return 0;
    }
    for (int i = change; i < nodes.size() - 1; i++)
    {
        if (nodes[i] == nodes[nodes.size() - 1])
        {
            if (play == 2)
            {
                int state_number = *nodes[nodes.size() - 1].begin();
                output[count].name = (input[state_number].name + 1) % 3;
                if (output[count].name == 0)
                {
                    output[count].rock = input[state_number].rock;
                    output[count].paper = input[state_number].rock;
                    output[count].scissor = input[state_number].rock;
                }
                else if (output[count].name == 1)
                {
                    output[count].rock = input[state_number].paper;
                    output[count].paper = input[state_number].paper;
                    output[count].scissor = input[state_number].paper;
                }
                else
                {
                    output[count].rock = input[state_number].scissor;
                    output[count].paper = input[state_number].scissor;
                    output[count].scissor = input[state_number].scissor;
                }
                count++;
                return count - 1;
            }
            else
            {
                play++;
                change = nodes.size();
            }
        }
    }
    int here = count;
    output[count].name = play;
    count++;
    set<int> a, b, c;
    for (auto itr = nodes[nodes.size() - 1].begin(); itr != nodes[nodes.size() - 1].end(); itr++)
    {
        if (input[*itr].name == 0)
        {
            if (play == 0)
            {
                a.insert(input[*itr].rock);
            }
            else if (play == 1)
            {
                a.insert(input[*itr].paper);
            }
            else
            {
                a.insert(input[*itr].scissor);
            }
        }
        else if (input[*itr].name == 1)
        {
            if (play == 0)
            {
                b.insert(input[*itr].rock);
            }
            else if (play == 1)
            {
                b.insert(input[*itr].paper);
            }
            else
            {
                b.insert(input[*itr].scissor);
            }
        }
        else
        {
            if (play == 0)
            {
                c.insert(input[*itr].rock);
            }
            else if (play == 1)
            {
                c.insert(input[*itr].paper);
            }
            else
            {
                c.insert(input[*itr].scissor);
            }
        }
    }
    nodes.push_back(a);
    output[here].rock = solve(input, output, count, nodes, play, change);
    nodes.pop_back();
    nodes.push_back(b);
    output[here].paper = solve(input, output, count, nodes, play, change);
    nodes.pop_back();
    nodes.push_back(c);
    output[here].scissor = solve(input, output, count, nodes, play, change);
    nodes.pop_back();
    return here;
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<state> input(n);
    for (int i = 0; i < n; i++)
    {
        char a;
        cin >> a;
        if (a == 'R')
        {
            input[i].name = 0;
        }
        else if (a == 'P')
        {
            input[i].name = 1;
        }
        else
        {
            input[i].name = 2;
        }
        cin >> input[i].rock;
        input[i].rock--;
        cin >> input[i].paper;
        input[i].paper--;
        cin >> input[i].scissor;
        input[i].scissor--;
    }
    vector<state> output(1000);
    for (int i = 0; i < 1000; i++)
    {
        output[i].name = 0;
        output[i].rock = 0;
        output[i].paper = 0;
        output[i].scissor = 0;
    }
    for (int i = 0; i < n; i++)
    {
        output[i].name = (input[i].name + 1) % 3;
        if (input[i].name == 0)
        {
            if (output[i].name == 0)
            {
                output[i].rock = input[i].rock;
            }
            else if (output[i].name == 1)
            {
                output[i].rock = input[i].paper;
            }
            else
            {
                output[i].rock = input[i].scissor;
            }
        }
        else if (input[i].name == 1)
        {
            if (output[i].name == 0)
            {
                output[i].paper = input[i].rock;
            }
            else if (output[i].name == 1)
            {
                output[i].paper = input[i].paper;
            }
            else
            {
                output[i].paper = input[i].scissor;
            }
        }
        else
        {
            if (output[i].name == 0)
            {
                output[i].scissor = input[i].rock;
            }
            else if (output[i].name == 1)
            {
                output[i].scissor = input[i].paper;
            }
            else
            {
                output[i].scissor = input[i].scissor;
            }
        }
    }
    int count = n;
    vector<set<int>> nodes;
    set<int> harshit;
    for (int i = 0; i < n; i++)
    {
        harshit.insert(i);
    }
    nodes.push_back(harshit);
    solve(input, output, count, nodes, 0, 0);
    state temp;
    state_copy(temp, output[0]);
    state_copy(output[0], output[n]);
    state_copy(output[n], temp);
    for (int i = 0; i < count; i++)
    {
        if (output[i].rock == 0)
        {
            output[i].rock = n;
        }
        else if (output[i].rock == n)
        {
            output[i].rock = 0;
        }
        if (output[i].paper == 0)
        {
            output[i].paper = n;
        }
        else if (output[i].paper == n)
        {
            output[i].paper = 0;
        }
        if (output[i].scissor == 0)
        {
            output[i].scissor = n;
        }
        else if (output[i].scissor == n)
        {
            output[i].scissor = 0;
        }
    }
    cout << count << endl;
    for (int i = 0; i < count; i++)
    {
        if (output[i].name == 0)
        {
            cout << "R ";
        }
        else if (output[i].name == 1)
        {
            cout << "P ";
        }
        else
        {
            cout << "S ";
        }
        cout << output[i].rock + 1 << " ";
        cout << output[i].paper + 1 << " ";
        cout << output[i].scissor + 1 << endl;
    }
}