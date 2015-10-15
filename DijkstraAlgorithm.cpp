#include <iostream>
#include <cstdlib>
#define MAX 20

using namespace std;

void sortShortest(int d[5][5], int n);
int findPath(int d[5][5], int start, int end, int n);
void shortest(int i, int j);
int p[MAX][MAX];

int main() {
	
	int distance[5][5] = {{0, 3, 5, 3, 10},
						  {1, 0, 4, 2, 1},
						  {2, 7, 0, 2, 3},
						  {3, 4, 3, 0, 3},
						  {4, 6, 4, 5, 0}};
	int shortestDistance = 0;
						  
	sortShortest(distance, 5); //point to point is the shortest distance
	shortestDistance = findPath(distance, 0, 4, 5);
	cout << "distance travelled is " << distance[0][4];
	
	return 0;
}

void sortShortest(int d[][5], int n) {
	
	int k, i, j;
    for (k=0; k<n; k++) {
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                if ((d[i][k]+d[k][j]) < d[i][j]) { //if going through a place is less than going there directly
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = k; //to indicate which column j that you should go into instead for shortest path
                }
            }
        }
    }
//    for (i=0; i<n; i++) {
//    	for (j=0; j<n; j++) {
//    		cout << " " << d[i][j] << " ";
//    	}
//    	cout << "\n";
//    }
//    cout << "\n";
//    for (i=0; i<n; i++) {
//    	for (j=0; j<n; j++) {
//    		cout << " " << p[i][j] << " ";
//    	}
//    	cout << "\n";
//    }
	return;
}

int findPath(int d[5][5], int start, int end, int n) {
	
	int distance = 0;
    cout << "Path from " << start <<" to "<< end << ":";
    cout << "  " << start << "  ";
    shortest(start, end);
    cout << "  " << end << " \n";
	
	return distance;
}

void shortest(int i, int j) {
	int k=p[i][j];
	if (k>0) {
		shortest(i, k);
		cout << " " << k << " ";
		shortest(k, j);
	}
	return;
}


