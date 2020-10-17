#include <fstream>
#include <vector>
#include <stack>
#include <cstdlib>
using namespace std;

int main()
{

    ifstream fin("rect.in");
    ofstream fout("rect.out");

    int maxvaluex, maxvaluey, number;
    double line1, line2, line3, line4, tempx, tempy;
    int counter2 = 0, counter = 1, mv = 0, diff = 0;

    fin >> maxvaluex >> maxvaluey >> number;

    vector <int> vec1;
    vector <int> vec2;
    vector <int> veccheck{ 45,21,11,67,82 };

    for(int i = 0; i < number; i++)
    {
        fin >> line1 >> line2 >> line3 >> line4;

        if ((double)(maxvaluey * line1 / line4) > maxvaluex)
        {
            tempx = (maxvaluey - (maxvaluex * line4 / line1)) + maxvaluex;
            if (tempx != long(tempx))
            {
                vec1.push_back(tempx + 1);
            }
            else
            {
                vec1.push_back(tempx);
            }
        }
        else {
            tempx = maxvaluey * line1 / line4;
            if (tempx != long(tempx))
            {
                vec1.push_back(tempx + 1);
            }
            else
            {
                vec1.push_back(tempx);
            }
        }

        if ((maxvaluey * line3 / line2) > maxvaluex)
        {
            tempy = (maxvaluey - (maxvaluex * line2 / line3)) + maxvaluex;
            vec2.push_back(tempy);
        }
        else {
            tempy = maxvaluey * line3 / line2;
            vec2.push_back(tempy);
        }
    }

    int tempforsortveccheck = 0;
    for (int i = 0; i < veccheck.size() - 1; i++) {
        for (int j = 0; j < veccheck.size() - i - 1; j++) {
            if (veccheck[j] > veccheck[j + 1]) {
                tempforsortveccheck = veccheck[j];
                veccheck[j] = veccheck[j + 1];
                veccheck[j + 1] = tempforsortveccheck;
            }
        }
    }

    int tempforsortvec1 = 0;
    for (int i = 0; i < vec1.size() - 1; i++) {
        for (int j = 0; j < vec1.size() - i - 1; j++) {
            if (vec1[j] > vec1[j + 1]) {
                tempforsortvec1 = vec1[j];
                vec1[j] = vec1[j + 1];
                vec1[j + 1] = tempforsortvec1;
            }
        }
    }

    int tempforsortvec2 = 0;
    for (int i = 0; i < vec2.size() - 1; i++) {
        for (int j = 0; j < vec2.size() - i - 1; j++) {
            if (vec2[j] > vec2[j + 1]) {
                tempforsortvec2 = vec2[j];
                vec2[j] = vec2[j + 1];
                vec2[j + 1] = tempforsortvec2;
            }
        }
    }


    for (int i = 0; i < number - 1; i++)
    {
        if (vec1[i + 1] > vec2[counter2])
        {
            i--;
            counter--;
            counter2++;
        }
        else
        {
            counter++;
            if (counter > mv)
            {
                mv = counter;
                diff = vec1[i + 1];
            }
        }
    }

    /*Вывод*/
    if (diff > maxvaluex)
    {
        fout << mv << " " << maxvaluex << " " << -(diff - maxvaluex - maxvaluey);
    }
    else
    {
        fout << mv << " " << diff << " " << maxvaluey;
    }
}
