#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <functional>
#include <unordered_set>

#pragma warning(disable:4996)

using namespace std;

inline void input(int& i)
{
	/*
#if _DEBUG
	static ifstream file("homuraarsenal.txt");
	static istream& in = file;
	in >> i;
#else
	scanf("%d", &i);
#endif
	*/
}

int main()
{
	int r, n, k;

	const size_t elements = 1000000;
	vector<int> c(elements);    

	uniform_int_distribution<int> distribution(1, 1000);
	mt19937 engine; // Mersenne twister MT19937
	auto generator = bind(distribution, engine);
	generate_n(c.begin(), elements, generator); 

	// input(r);
	r = 1;
	n = elements;
	k = 200;

	while (r--)
	{
		// input(n);
		// input(k);

		// vector<int> c(n);
		// for (auto &e: c)
		//	input(e);

		int count = 0;

		int sI = 0;
		while (sI < n)
		{
			unordered_set<int> map(k);

			int hold = 0;
			int cc = 1;
			int partial = 1;
			int nextsI = 0;
			int eI = 0;

			for (eI = sI; eI < n; eI++)
			{
				int key = c[eI];

				if (map.count(key) == 0)
				{
					map.insert(key);
					partial *= cc;
					cc = 1;
					hold++;
					if (map.size() == 2)
						nextsI = eI;
				}
				else
				{
					cc++;
				}
			
				if (hold > k)
				{
					count += partial;
					break;
				}
			}

			if (eI == n)
			{
				if (hold == k)
					count += partial;
				break;
			}

			sI = nextsI;
		}

		cout << count << endl;
	}
}