#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

#ifdef _DEBUG
ifstream fin("../wordchain/wordchain.txt");
istream& in = fin;
#else
istream& in = cin;
#endif

typedef vector<pair<int, int>> L;
typedef vector<L> AL;
typedef queue<string> ELM;

vector<int> seq;

void getEulercircuit(const AL& aj, vector<bool>& used, int v)
{
	for (auto &e : aj[v])
	{
		if (!used[e.second])
		{
			used[e.second] = true;
			getEulercircuit(aj, used, e.first);
		}
	}
	seq.push_back(v);
}

int main()
{
	int C, N;

	in >> C;
	while (C--)
	{
		in >> N;
		vector<string> str(N);
		for (auto &e : str)
			in >> e;

		AL aj(26, L());
		vector<vector<ELM>> am(26, vector<ELM>(26));

		for (int i = 0; i < N; i++)
		{
			int st = str[i].front() - 'a';
			int ed = str[i].back() - 'a';
			aj[st].push_back({ ed, i });

			am[st][ed].push(str[i]);
		}


		vector<int> in(26, 0);
		vector<int> ot(26, 0);

		for (int i = 0; i < aj.size(); i++)
			ot[i] += aj[i].size();

		for (auto &e : aj)
			for (auto &f : e)
				in[f.first]++;
		
		bool suc = true;
		vector<int> odd;
		for (int i = 0; i < 26; i++)
			if ((ot[i] + in[i]) % 2)
				odd.push_back(i);
			else if (ot[i] != in[i])
				suc = false;

		if (odd.size() != 0 && odd.size() != 2)
			suc = false;

		if (odd.size() == 2)
			if (ot[odd[0]] + ot[odd[1]] != in[odd[0]] + in[odd[1]])
				suc = false;

		if (!suc)
		{
			cout << "IMPOSSIBLE" << endl;
			continue;
		}

		int startNode = -1;
		int endNode = -1;

		if (odd.size() == 2)
		{
			if (ot[odd[0]] > in[odd[0]])
			{
				startNode = odd[0];
				endNode = odd[1];
			}
			else
			{
				startNode = odd[1];
				endNode = odd[0];
			}
		}
		else
		{
			for (int i = 0; i < 26; i++)
			{
				if (aj[i].size() > 0)
				{
					startNode = i;
					break;
				}
			}
		}


		seq.clear();

		vector<bool> used(N, false);
		getEulercircuit(aj, used, startNode);

		if (seq.size() != N+1) cout << "IMPOSSIBLE" << endl;
		else
		{
			reverse(seq.begin(), seq.end());
			for (int i = 1; i < seq.size(); i++)
			{
				cout << am[seq[i - 1]][seq[i]].front() << " ";
				am[seq[i - 1]][seq[i]].pop();
			}
			cout << endl;
		}
	}

	return 0;
}