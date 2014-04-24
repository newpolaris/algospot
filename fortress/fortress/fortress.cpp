#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <map>

using namespace std;

struct node;
typedef shared_ptr<node> Node;

struct node
{
public:
	node(int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}

	bool contain(Node& n) const
	{
		int d = (x - n->x)*(x - n->x) + (y - n->y)*(y - n->y);
		return d <= (r - n->r)*(r - n->r);
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

	void addChild(Node n)
	{
		vector<int> inside;
		for (int i = 0; i < child.size(); i++)
		{
			if (child[i]->contain(n))
			{
				child[i]->addChild(n);
				return;
			}
		}

		vector<int> cont;
		for (int i = 0; i < child.size(); i++)
		{
			if (n->contain(child[i]))
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

		child.push_back(Node(n));
	}

	int x, y, r;
	vector<Node> child;
};

struct tree
{
	void addChild(node* n)
	{
		if (root != nullptr)
			root->addChild(Node(n));
		else
			root.reset(n);
	}

	int maxDist()
	{
		vector<int> list;
		int dist = root->maxDist(list);
		sort(list.begin(), list.end(), greater<int>());

		if (list.size() > 0)
			dist = max(dist, list[0]);

		return dist;
	}

	Node root;
};

int main()
{
	int n;
#if 1
	istream& in = cin;
#else
	ifstream f;
	f.open("fortress.txt");
	istream& in = f;
#endif
	in >> n;

	while (n--)
	{
		int c;
		in >> c;

		tree t;
		
		for (int i = 0; i < c; i++)
		{
			int x, y, r;
			in >> x >> y >> r;

			t.addChild(new node(x, y, r));
		}

		cout << t.maxDist() << endl;
	}

	return 0;
}
