#include <iostream>

using namespace std;

int main()
{
	int fibo[101];
	fibo[0] = fibo[1] = 1;
	for (int i = 2; i < 101; i++)
		fibo[i] = (fibo[i - 1] + fibo[i - 2]) % 1000000007;

	int m, n;
	cin >> m;
	while (m--)
	{
		cin >> n;
		cout << fibo[n] << endl;
	}
	return 0;
}