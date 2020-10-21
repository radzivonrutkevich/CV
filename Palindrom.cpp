#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main()
{
	vector <char> array;
	string result_str;
	char symbol;
	int temp = 0;

	while (fin >> symbol){array.push_back(symbol);}

	vector<vector<int>> matrix(array.size() + 1, vector<int>(array.size() + 1));

	for (int i = 1; i <= array.size(); i++)
	{
		for (int j = i; j <= array.size(); j++)
		{
			if (array[i - 1] == array[array.size() - j])
			{
				matrix[i][j] = matrix[i - 1][j - 1] + 1;
			}
			else
			{
				matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j]);
			}
		}
		for (int j = i + 1; j <= array.size(); j++)
		{
			if (array[j - 1] == array[array.size() - i])
			{
				matrix[j][i] = matrix[j - 1][i - 1] + 1;
			}
			else
			{
				matrix[j][i] = max(matrix[j][i - 1], matrix[j - 1][i]);
			}
		}
	}

	int counter = array.size();
	for (int i = array.size(); i > 0 && counter > 0 && temp < (matrix[array.size()][array.size()] + 1) / 2; ) {
		if (matrix[i][counter] != matrix[i][counter - 1] && matrix[i][counter] != matrix[i - 1][counter]) {
			result_str += array[i - 1];
			temp++;
			if (counter > 1) {
				counter--;
				while (matrix[i][counter] == matrix[i - 1][counter] && i > 1) {
					i--;
				}
				while (matrix[i][counter] == matrix[i][counter - 1] && counter > 1) {
					counter--;
				}
			}
			else {
				break;
			}
		}
		else {
			if (i > 1) {
				while (matrix[i][counter] == matrix[i - 1][counter] && i > 1) {
					i--;
				}
				while (matrix[i][counter] == matrix[i][counter - 1] && counter > 1) {
					counter--;
				}
			}
			else {
				counter--;
			}
		}
	}

	for (int i = temp; i < matrix[array.size()][array.size()]; i++)
	{
		result_str += result_str[matrix[array.size()][array.size()] - i - 1];
	}

	fout << matrix[array.size()][array.size()] << endl;
	fout << result_str;
}
