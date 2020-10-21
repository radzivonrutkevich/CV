#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int Count_com(vector <int> value)
{
	int x = 0;
	vector <int> dp(value.size());
	dp[0] = value[0];
	if (value.size() > 1) {
		dp[1] = -1;
	}
	if (value.size() > 2) {
		dp[2] = dp[0] + value[2];
	}
	for (int i = 3; i < dp.size(); i++)
	{

		dp[i] = max(dp[i - 2], dp[i - 3]) + value[i];

	}
	x = dp[dp.size() - 1];
	return x;
}


int main()
{
	int all_steps = 0;
	int temp_value = 0;;
	vector <int> array;

	fin >> all_steps;

	for (int i = 0; i < all_steps; i++) {
		fin >> temp_value;
		array.push_back(temp_value);
	}

	fout << Count_com(array) ;


}
