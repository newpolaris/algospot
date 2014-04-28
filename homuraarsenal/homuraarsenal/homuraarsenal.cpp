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

		for (int sI = 0; sI < n; sI++)
		{
			map.clear();
			int numType = 0;
			for (int el = sI; el < n; el++)
			{
				int num = c[el];
				if (map[num]++ == 0)
					numType++;

				if (numType == k)
					count++;
				else if (numType > k)
					break;
			}
		}

		cout << count << endl;
	}
}