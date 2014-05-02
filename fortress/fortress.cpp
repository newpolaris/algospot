#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node
{
	bool contain(node& n) const
	{
		return pow(x - n.x, 2) + pow(y - n.y, 2) < pow(r - n.r, 2);
	}

	int maxdist(int& m)
	{
		if (child.size() == 0)
			return 0;

		int m1 = 0, m2 = 0;
		for (auto &i : child)
		{
			m2 = max(m2, i->maxdist(m) + 1);
			if (m2 > m1) 
				swap(m1, m2);
		}
		m = max(m, m1 + m2);

		return m1;
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

	int x, y, r;
	vector<node*> child;
};

int main()
{
	int n, c;
	istream& in = cin;
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

		int m = 0;
		root->maxdist(m);
		cout << m << endl;
	}

	return 0;
}
