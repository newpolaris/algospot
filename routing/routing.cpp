#include <iostream>
#include <functional>
#include <vector>
#include <iomanip>
#include <queue>
#include <limits>

using namespace std;

typedef pair<double, int> Node;
typedef vector<vector<Node>> AJ;

int main()
{
	cin.sync_with_stdio(false);

	int c, n, m;
	cin >> c;

	while (c--)
	{
		cin >> n >> m;
		AJ aj(n, vector<Node>());
		
		int a, b;
		double noise;

		for (int i = 0; i < m; i++)
		{
			cin >> a >> b >> noise;
			aj[a].push_back({noise, b});
			aj[b].push_back({noise, a});
		}

		vector<double> v(n, numeric_limits<double>::infinity());
		priority_queue<Node, vector<Node>, greater<Node>> Q;

		Q.push({1.0, 0});
		v[0] = 1.0;

		while (!Q.empty())
		{
			int minI = Q.top().second;
			Q.pop();

			if (v[minI] < 0)
				continue;

			if (minI == n - 1)
				break;

			for (auto &e : aj[minI])
			{
				double noise = v[minI] * e.first;
				int k = e.second;
				if (v[k] > noise)
				{
					v[k] = noise;
					Q.push({noise, k});
				}
			}
			v[minI] = -1;
		}

		cout << fixed;
		cout << setprecision(10) << v[n - 1] << endl;
	}
	return 0;
}