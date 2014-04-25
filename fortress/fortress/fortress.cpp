#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <map>
#include <unordered_map>

using namespace std;

struct node
{
	node() { x = y = r = d = 0; }
	bool contain(node& n) const
	{
		return pow(x - n.x, 2) + pow(y - n.y, 2) < pow(r - n.r, 2);
	}

	int depth() 
	{
		if (d == 0)
			for (auto &i : child)
				d = max(d, i->depth()+1);

		return d;
	}

	int dist() 
	{
		int m1 = 0, m2 = 0;
		for (auto &i : child)
		{
			m2 = max(m2, i->depth() + 1);
			if (m2 > m1) 
				swap(m1, m2);
		}
		return m1 + m2;
	}

	int maxdist()
	{
		int m = dist();
		for (auto &i : child)
			m = max(m, i->maxdist());
		return m;
			
	}

	void addChild(node* n)
	{
		vector<int> inside;
		for (auto &i: child)
		{
			if (i->contain(*n))
			{
				i->addChild(n);
				return;
			}
		}

		child.push_back(n);
	}

	int x, y, r, d;
	vector<node*> child;
};

int main()
{
	int n, c;
#if 0
	istream& in = cin;
#else
	ifstream f;
	f.open("fortress.txt");
	istream& in = f;
#endif
	in >> n;

	while (n--)
	{
		in >> c;

		vector<node> nodes(c);
		for (auto &e : nodes)
			in >> e.x >> e.y >> e.r;

		sort(nodes.begin(), nodes.end(), 
			[](const node& a, const node& b)
				{ return a.r > b.r; });

		node* root = &nodes[0];
		for (int i = 1; i < nodes.size(); i++)
			root->addChild(&nodes[i]);

		cout << root->maxdist() << endl;
	}

	return 0;
}
