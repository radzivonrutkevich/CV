#include <iostream> 
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
	int matrix_size = 0, minimum = INT_MAX;

	fin >> matrix_size;

	vector<int> matrix_n(matrix_size + 1);
	vector<int> matrix_m(matrix_size + 1);

	for (int i = 1; i <= matrix_size; i++) {
		fin >> matrix_n[i] >> matrix_m[i];
	}

	vector<vector<int>> res_matrix(matrix_size + 1, vector<int>(matrix_size + 1));

	for (int i = 0; i < matrix_size; i++) {
		res_matrix[i][i + 1] = matrix_n[i] * matrix_m[i] * matrix_m[i + 1];
	}

	int temp = 0;
	for (int i = matrix_size - 2; i > 0; i--) {
		for (int j = i + 2; j <= matrix_size; j++) {
			minimum = INT_MAX;
			temp = i;
			while (temp != j) {
				minimum = min(minimum, (res_matrix[i][temp] + res_matrix[temp + 1][j] + (matrix_n[i] * matrix_m[temp]) * (matrix_m[j])));
				temp++;
			}
			res_matrix[i][j] = minimum;
		}
	}

	fout << res_matrix[1][matrix_size];
}
