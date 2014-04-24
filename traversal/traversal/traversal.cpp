#include <iostream>
#include <algorithm>

using namespace std;

int pre[100] = {0,};
int  in[100] = {0,};

void traversal(int st, int ed, int root)
{
	if (st > ed) return; 
	
	int center = distance(&in[st], find(&in[st], &in[ed], pre[root])) + st;	

	traversal(st, center-1, root+1);
	traversal(center+1, ed, root+1+center-st);

	cout << in[center] << " ";
}

int main()
{
	int c, n;
	cin >> c;

	while (c--) {
		cin >> n;
		for (int i = 0; i < n; i++) cin >> pre[i];
		for (int i = 0; i < n; i++) cin >> in[i];

		traversal(0, n-1, 0);

		cout << endl;
	}

	return 0;
}