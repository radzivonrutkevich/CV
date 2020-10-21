#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int main() {

	ifstream fin("maze.in");
	ofstream fout("maze.out");

	setlocale(LC_ALL, "Russian");
	
	int rows, cols;
	int counter = 0;

	queue <int> queuex;
	queue <int> queuey;

	fin >> rows >> cols;
	rows += 2;
	cols += 2;

	int** array = new int* [rows]();

	for (int i = 0; i < rows; i++) {
		array[i] = new int[cols] ();
	}

	int xstart, ystart, xend, yend;
	fin >> xstart >> ystart;
	fin >> xend >> yend;

	for (int j = 1; j < rows - 1 ; j++) {
		for (int i = 1; i < cols - 1; i++) {
			fin >> array[j][i];
		}
	}

	queuex.push(xstart);
	queuey.push(ystart);
	array[xstart][ystart] = 2;
	while (!queuex.empty()) {
		if (array[queuex.front()][queuey.front() + 1] == 1) {
			array[queuex.front()][queuey.front() + 1] = array[queuex.front()][queuey.front()] + 1;
			queuex.push(queuex.front());
			queuey.push(queuey.front() + 1);
		}
		if (array[queuex.front()][queuey.front() - 1] == 1) {
			array[queuex.front()][queuey.front() - 1] = array[queuex.front()][queuey.front()] + 1;
			queuex.push(queuex.front());
			queuey.push(queuey.front() - 1);
		}
		if (array[queuex.front() - 1][queuey.front()] == 1) {
			array[queuex.front() - 1][queuey.front()] = array[queuex.front()][queuey.front()] + 1;
			queuex.push(queuex.front() - 1);
			queuey.push(queuey.front());
		}
		if (((array[queuex.front() + 1][queuey.front()] == 1)) ) {
			array[queuex.front() + 1][queuey.front()] = array[queuex.front()][queuey.front()] + 1;
			queuex.push(queuex.front() + 1);
			queuey.push(queuey.front());
		}
		if (queuex.front() == xend && queuey.front() == yend) {
			counter = 1;
			break;
		}
		queuex.pop();
		queuey.pop();
	}

	if (counter == 0) {
		fout << -1;
	}
	else {
		vector <int> vecx;
		vector <int> vecy;
		int distance = array[xend][yend];
		fout << distance - 2 << endl;
		int tempx = xend;
		int tempy = yend;
		vecx.push_back(xend);
		vecy.push_back(yend);

		while (distance != 1)
		{
			if (array[tempx + 1][tempy] == distance) {
				vecx.push_back(tempx + 1);
				vecy.push_back(tempy);
					tempx += 1;
				continue;
			}
			if (array [tempx - 1][tempy] == distance) {
				vecx.push_back(tempx - 1);
				vecy.push_back(tempy);
				tempx -= 1;
				continue;
			}
			if (array[tempx][tempy + 1] == distance ) {
				vecx.push_back(tempx);
				vecy.push_back(tempy + 1);
					tempy += 1;
				continue;
			}
			if (array[tempx][tempy - 1] == distance ) {
				vecx.push_back(tempx);
				vecy.push_back(tempy - 1);
				tempy -= 1;
				continue;
			}
			--distance;
		}

		for(int i = vecx.size() - 1; i >= 0; i--){
			fout << vecx[i] << " " << vecy[i] << endl;
		}
		
	}

	for (int i = 0; i < rows; i++) {
		delete[] array[i];
	}
	delete[] array;
}
