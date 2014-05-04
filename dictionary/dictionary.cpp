#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

using namespace std;

#ifdef _DEBUG
ifstream fin("../dictionary/dictionary.txt");
istream& in = fin;
#else
istream& in = cin;
#endif

bool isCycle;

vector<int> solution;
vector<bool> used;
set<int> stack;
vector<vector<int>> aj;

void dfs(int v)
{
	used[v] = true;
	stack.insert(v);
	for (auto &e : aj[v])
	{
		if (!used[e]) dfs(e);
		else if (stack.find(e) != stack.end())
		{
			isCycle = true;
			break;
		}
	}
	
	solution.push_back(v);
	stack.erase(v);
}

int main()
{
	cin.sync_with_stdio(false);
	int C, N;

	in >> C;

	while (C--)
	{
		in >> N;

		solution.clear();
		isCycle = false;
		aj = vector<vector<int>>(26, vector<int>());

		vector<string> str(N);
		for (auto &e : str)
			in >> e;

		for (int i = 1; i < N; i++)
		{
			string& p = str[i-1];
			string& c = str[i];

			int idx = 0;
			while (true)
			{
				if (p.size() <= idx || c.size() <= idx) break;

				int P = p[idx] - 'a';
				int C = c[idx] - 'a';

				if (P != C)
				{
					aj[P].push_back(C);
					break;
				}
				idx++;
			}
		}

		used = vector<bool>(26, false);

		for (int i = 0; i < 26; i++)
		{
			if (!used[i]) dfs(i);
			if (isCycle) break;
		}

		if (isCycle)
		{
			cout << "INVALID HYPOTHESIS" << endl;
			continue;
		}

		for (auto e = solution.rbegin(); e != solution.rend(); ++e)
			cout << (char)(*e + 'a');
		cout << endl;
	}

	return 0;
}