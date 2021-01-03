#include <iostream>
#include <string>

using namespace std;

string add(string lhs, string rhs);
string subtract(string lhs, string rhs);
string multiply(string num1, string num2);

int main()
{
	string num1, num2;

	cout << "Enter Number 1: ";
	cin >> num1;
	cout << "Enter Number 2: ";
	cin >> num2;

	string num3 = multiply(num1, num2);

	cout << num3 << endl;

	return 0;
}

string add(string lhs, string rhs)
{
	int length = max(lhs.size(), rhs.size());
	int carry = 0;
	int sumCol = 0;
	string result;

	while (lhs.size() < length)
	{
		lhs.insert(0, "0");
	}


	while (rhs.size() < length)
	{
		rhs.insert(0, "0");
	}

	for (int i = length - 1; i >= 0; --i)
	{
		sumCol = (lhs[i] - '0') + (rhs[i] - '0') + carry;
		carry = sumCol / 10;
		result.insert(0, to_string(sumCol % 10));
	}

	if (carry)
	{
		result.insert(0, to_string(carry));
	}

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string subtract(string lhs, string rhs)
{
	int length = max(lhs.size(), rhs.size());
	int diff;
	string result;

	while (lhs.size() < length)
	{
		lhs.insert(0, "0");
	}
	
	while (rhs.size() < length)
	{
		rhs.insert(0, "0");
	}

	for (int i = length - 1; i >= 0; --i)
	{
		diff = (lhs[i] - '0') - (rhs[i] - '0');

		if (diff >= 0)
			result.insert(0, to_string(diff));
		else
		{
			int j = i - 1;

			while (j >= 0)
			{
				lhs[j] = ((lhs[j] - '0') - 1) % 10 + '0';

				if (lhs[j] != 9)
					break;
				else
					j--;
			}

			result.insert(0, to_string(diff + 10));
		}
	}

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}

string multiply(string num1, string num2)
{
	int length = max(num1.size(), num2.size());

	while (num1.size() < length)
		num1.insert(0, "0");

	while (num2.size() < length)
		num2.insert(0, "0");

	if (length == 1)
		return to_string((num1[0] - '0') * (num2[0] - '0'));

	string num1_l = num1.substr(0, length / 2);
	string num1_r = num1.substr(length / 2, length - length / 2);

	string num2_l = num2.substr(0, length / 2);
	string num2_r = num2.substr(length / 2, length - length / 2);

	string calc0 = multiply(num1_l, num2_l); // ac
	string calc1 = multiply(num1_r, num2_r); // bd
	string calc2 = multiply(add(num1_l, num1_r), add(num2_l, num2_r)); // (a + b) * (c + d) 
	string calc3 = subtract(calc2, add(calc0, calc1)); // calc2 - calc0 - calc1

	for (int i = 0; i < 2 * (length - length / 2); ++i)
		calc0.append("0");

	for (int i = 0; i < length - length / 2; ++i)
		calc3.append("0");

	string result = add(add(calc0, calc1), calc3);

	return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
}
