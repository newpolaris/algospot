#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <map>

using namespace std;

struct node
{
	bool contain(node& n) const
	{
		return pow(x - n.x, 2) + pow(y - n.y, 2) < pow(r - n.r, 2);
	}

	int maxDist(vector<int>& list) const
	{
		if (child.size() == 0) return 0;

		vector<int> dist;
		for (int i = 0; i < child.size(); i++)
			dist.push_back(child[i]->maxDist(list) + 1);

		sort(dist.begin(), dist.end(), greater<int>());
		if (dist.size() > 1)
			list.push_back(dist[0] + dist[1]);
		
		return dist[0];
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

		vector<int> cont;
		for (int i = 0; i < child.size(); i++)
		{
			if (n->contain(*child[i]))
				cont.push_back(i);
		}

		if (cont.size() != 0)
		{
			for (int i = 0; i < cont.size(); i++)
				n->addChild(child[i]);

			for (int i = 0; i < cont.size(); i++)
				child.erase(child.begin() + cont[i]);

			return;
		}

		child.push_back(n);
	}

	int x, y, r;
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

		node* root = &nodes[0];
		for (int i = 1; i < nodes.size(); i++)
			root->addChild(&nodes[i]);

		vector<int> list;
		int dist = root->maxDist(list);
		sort(list.begin(), list.end(), greater<int>());

		if (list.size() > 0)
			dist = max(dist, list[0]);

		cout << dist << endl;
	}

	return 0;
}
