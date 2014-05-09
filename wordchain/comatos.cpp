#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <stack>

using namespace std;

int main()
{
	int C, N;

	cin >> C;
	while (C--)
	{
		cin >> N;

		stack<pair<int, string*>> aj[26];
		int in[26] = { 0 }, ot[26] = { 0 };

		vector<string> str(N);
		for (auto &e : str)
		{
			cin >> e;
			int st = e.front() - 'a';
			int ed = e.back() - 'a';
			ot[st]++;
			in[ed]++;
			aj[st].push({ ed, &e });
		}

		int s = -1;
		for (int i = 0; i < 26; i++)
			if (ot[i] != 0 && (s == -1 || in[i]+1 == ot[i]))
				s = i;

		vector<string*> sol;

		function<void(int)> eulercircuit = [&](int v)
		{
			while (!aj[v].empty())
			{
				auto k = aj[v].top();
				aj[v].pop();

				eulercircuit(k.first);
				sol.push_back(k.second);
				N--;
			}
		};

		eulercircuit(s);

		stringstream out;

		if (N == 0)
		{
			reverse(sol.begin(), sol.end());
			for (auto &e : sol)
				out << *e << " ";
			cout << out.str() << endl;
		}
		else
		{
			cout << "IMPOSSIBLE" << endl;
		}
	}

	return 0;
}
