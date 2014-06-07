#include <iostream>
#include <string>
#pragma warning(disable:4996)

using namespace std;

int main()
{
	int n, m, i;
	cin >> n;

	while (n--)
	{
		string str;
		cin >> str;
		auto ch = str.c_str();
		i = 0;
		while (i < str.length())
		{
			if (ch[i] == '%') 
			{
				sscanf(ch+i+1, "%2x", &m);
				printf("%c", m);
				i += 3;
			}
			else putchar(str[i++]);
		}
		cout << endl;
	}

	return 0;
}