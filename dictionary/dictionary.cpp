#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

istream& in = cin;

bool isCycle;

vector<int> solution;
vector<bool> used;
vector<bool> S;
vector<vector<int>> aj;

void dfs(int v)
{
	used[v] = S[v] = 1;
	for (auto &e : aj[v])
	{
		if (!used[e]) dfs(e);
		else if (S[e] == 1)
			isCycle = 1;
	}
	
	solution.push_back(v);
	S[v] = 0;
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

			int Len = min(p.size(), c.size());
			for (int l = 0; l < Len; l++)
			{
				int P = p[l] - 'a';
				int C = c[l] - 'a';

				if (P != C)
				{
					aj[P].push_back(C);
					break;
				}
			}
		}

		used = vector<bool>(26, false);
		S = vector<bool>(26, false);

		for (int i = 0; i < 26; i++)
			if (!used[i]) dfs(i);

		if (isCycle)
			cout << "INVALID HYPOTHESIS" << endl;
		else
		{
			for (auto e = solution.rbegin(); e != solution.rend(); ++e)
				cout << (char)(*e + 'a');
			cout << endl;
		}
	}

	return 0;
}