#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n;
	cin >> n;

	while (n--)
	{
		string str;
		cin >> str;

		int i = 0;
		while (str.length() - i > 2)
		{
			if (str[i] == '%' && str[i + 1] == '2')
			{
				switch (str[i + 2])
				{
				case '0': putchar(' '); break;
				case '1': putchar('!'); break;
				case '4': putchar('$'); break;
				case '5': putchar('%'); break;
				case '8': putchar('('); break;
				case '9': putchar(')'); break;
				case 'a': putchar('*'); break;
				default:
					putchar(str[i]);
					putchar(str[i + 1]);
					putchar(str[i + 2]);
					break;
				}
				i += 3;
			}
			else
			{
				putchar(str[i]);
				i++;
			}
		}
		while (i < str.length())
			putchar(str[i++]);
		cout << endl;
	}

	return 0;
}