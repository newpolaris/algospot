#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#pragma warning(disable:4996)

using namespace std;

inline void input(int& i)
{
#if _DEBUG
	static ifstream file("homuraarsenal.txt");
	static istream& in = file;
	in >> i;
#else
	scanf("%d", &i);
#endif
}

int main()
{
	int r, n, k;

	input(r);

	while (r--)
	{
		input(n);
		input(k);

		vector<int> c(n);
		for (auto &e: c)
			input(e);

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