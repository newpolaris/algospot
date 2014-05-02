#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <random>

#pragma warning(disable:4996)

using namespace std;

int main()
{
	int c, n;

#ifdef _DEBUG
	ifstream fin("../nerd2.txt");
	istream& in = fin;
#else
	// cin.sync_with_stdio(false);
	// istream& in = cin;
#endif

	scanf("%d", &c);
	// in >> c;

	typedef pair<int, int> NERD;
	while (c--)
	{
		scanf("%d", &n);
		// in >> n;
		vector<NERD> p(n);

		// std::default_random_engine eng(std::random_device{}());
		// std::uniform_int_distribution<> dist(0,100000);

		for (auto &e : p)
			scanf("%d %d", &e.first, &e.second);
		// { e.first = dist(eng); e.second = dist(eng); }
			// in >> e.first >> e.second;
	
		int total = 0;
		multimap<int, int> map;

		for (int i = 0; i < n; i++)
		{
			auto key = p[i].first;
			map.insert({ key, p[i].second });
			auto itlow = map.lower_bound(0);
			auto itup = map.upper_bound(key);

			for (auto it = itlow; it != itup;)
			{
				if (it->second < p[i].second)
					it = map.erase(it);
				else ++it;
			}

			total += map.size();
		}
		cout << total << endl;

		// cout << chrono::duration_cast<chrono::milliseconds> (std::chrono::high_resolution_clock::now() - start).count() << endl;
	}

	return 0;
}