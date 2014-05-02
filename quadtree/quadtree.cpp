#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

class QuadTree;

class Node
{
	Node(istream& stream);
	~Node();

	void traversal(ostream& ostr);
	void upside();

	char data;
	Node* child[4];

	friend class QuadTree;
};

Node::Node(istream& stream)
{
	stream >> data;

	for (int i = 0; i < 4; i++)
		if (data == 'x')
			child[i] = new Node(stream);
		else
			child[i] = nullptr;
}

Node::~Node()
{
	for (int i = 0; i < 4; i++)
		delete child[i];
}

void Node::upside()
{
	if (data == 'x')
	{
		swap(child[0], child[2]);
		swap(child[1], child[3]);

		for (int i = 0; i < 4; i++)
			child[i]->upside();
	}
}

void Node::traversal(ostream& ostr)
{
	ostr << data;
	if (data == 'x')
		for (int i = 0; i < 4; i++)
			child[i]->traversal(ostr);
}

class QuadTree
{
public:
	QuadTree(istream& stream);
	~QuadTree();
	void traversal(ostream& ostr);
	void upside();

	Node* root;
};

QuadTree::QuadTree(istream& stream)
{
	root = new Node(stream);
}

QuadTree::~QuadTree()
{
	delete root;
	root = nullptr;
}

void QuadTree::upside()
{
	root->upside();
}

void QuadTree::traversal(ostream& ostr)
{
	root->traversal(ostr);
}

void solve()
{
	QuadTree tree(cin);
	tree.upside();
	tree.traversal(cout);
	cout << endl;
}

int main()
{
	int numTest = 0;
	cin >> numTest;

	while (numTest--)
		solve();

	return 0;
}