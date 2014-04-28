#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#pragma warning(disable:4996)

using namespace std;
int main()
{
#if _DEBUG
	ifstream file;
	file.open("homuraarsenal.txt");
	istream& in(file);
#endif

	int r, n, k;

#if _DEBUG
	in >> r;
#else
	scanf("%d", &r);
#endif

	while (r--)
	{
#if _DEBUG
		 in >> n >> k;
#else
		scanf("%d %d", &n, &k);
#endif

		vector<int> c(n);
		for (auto &e: c)
#if _DEBUG
			in >> e;
#else
			scanf("%d", &e);
#endif

		unordered_map<int, int> map;

		int count = 0;
		int hold = 0;

		int sIdx = 0;
		int eIdx = 0;

		while (eIdx < n)
		{
			if (map[c[eIdx]]++ == 0)
				hold++;

			while (hold > k && sIdx <= eIdx)
			{
				if (--map[c[sIdx]] == 0)
					hold--;
				sIdx++;
			}

			if (hold == k)
			{
				int cIdx = sIdx;

				unordered_map<int, int> cmap;
				while (cIdx <= eIdx)
				{
					count++;
					if (cmap[c[cIdx]] == 0)
						cmap[c[cIdx]] = map[c[cIdx]];

					if (--cmap[c[cIdx]] == 0)
					{
						cmap[c[cIdx]] = -1;
						break;
					}
					cIdx++;
				}
			}
				
			eIdx++;
		}

		cout << count << endl;
	}
}