/**
 * Author: Sashko
 * Date: 2024-03-18
 * License: CC0
 * Source: cp-algorithms
 * Description: Creates suffix automaton
 * Time: O(|alphabet| * \sum |s_i|)
 * Status: -
 */

const int K = 26;

struct Vertex {
    int next[K];
    bool output = false;
    int p = -1;
    char pch;
    int link = -1;
    int ans_link = -1;
    int go[K];

    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};

vector<Vertex> t(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].output = true;
}

int go(int v, char ch);

int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int go(int v, char ch) {
    int c = ch - 'a';
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
} 

int get_ans_link(int v)
{
    if(v == 0)
    return 0;
    if(t[v].ans_link == -1)
    {
        if(t[get_link(v)].output)
        {
            t[v].ans_link = get_link(v);
        }
        else
        t[v].ans_link = get_ans_link(get_link(v));
    }
    return t[v].ans_link;
}

// returns all strings from dictionary that is suffix of given state 
vector<string> get_ans(int v)
{
    vector<string>ans;
    if(t[v].output)
    {
        string cur = "";
        int v1 = v;
        while(v1)
        {
            cur += t[v1].pch;
            v1 = t[v1].p;
        }
        reverse(cur.begin(), cur.end());
        ans.push_back(cur);
    }
    v = get_ans_link(v);
    while(v)
    {
        string cur = "";
        int v1 = v;
        while(v1)
        {
            cur += t[v1].pch;
            v1 = t[v1].p;
        }
        reverse(cur.begin(), cur.end());
        ans.push_back(cur);
        v = get_ans_link(v);
    }
    return ans;
}
