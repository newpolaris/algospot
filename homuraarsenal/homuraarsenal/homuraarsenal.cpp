#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;
int main()
{
#if _DEBUG
	ifstream file;
	file.open("homuraarsenal.txt");
	istream& in(file);
#else
	cin.sync_with_stdio(false);
	istream& in(cin);
#endif

	int r, n, k;
	in >> r;

	while (r--)
	{
		in >> n >> k;

		vector<int> c(n);
		for (auto &e: c)
			in >> e;

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
				count++;
				
			eIdx++;
		}

		cout << count << endl;
	}
}