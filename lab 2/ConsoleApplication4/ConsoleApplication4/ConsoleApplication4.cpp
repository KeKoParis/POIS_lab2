#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

void quick_sort(int* a, int begin, int end)
{
	int left, right;
	double x;
	int f;
	left = begin;
	right = end;
	x = a[(left + right) / 2];
	do {
		while (a[left] > x)  left++;
		while (x > a[right]) right--;
		if (left <= right) {
			f = a[left];
			a[left] = a[right];
			a[right] = f;
			left++;
			right--;
		}
	} while (left <= right);


	if (begin < right) quick_sort(a, begin, right);
	if (left < end) quick_sort(a, left, end);
}


int num_bridges;
int n;
int br_roads[200000][2];

const int max_num_vertex = 20000;
vector<int> g[max_num_vertex];
bool used[max_num_vertex];
int timer, tin[max_num_vertex], fup[max_num_vertex];

void dfs(int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i = 0; i < g[v].size(); ++i) {

		int to = g[v][i];

		if (to == p) {

			continue;

		}
		if (used[to]) {

			fup[v] = min(fup[v], tin[to]);

		}
		else {

			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);

			if (fup[to] > tin[v]) {

				num_bridges++;
				br_roads[num_bridges - 1][0] = v;
				br_roads[num_bridges - 1][1] = to;
			}
		}
	}
}

void find_bridges() {

	num_bridges = 0;
	timer = 0;

	for (int i = 0; i < n; ++i) {

		used[i] = false;

	}
	for (int i = 0; i < n; ++i) {

		if (!used[i]) {

			dfs(i);

		}

	}

}

int main()
{
	FILE* in;
	in = fopen("bridges.in", "r");

	int num_roads;
	
	fscanf(in, "%d", &n);
	fscanf(in, "%d", &num_roads);

	int fnum, snum;
	int** roads = new int* [num_roads];

	for (int i = 0; i < num_roads; i++) {

		roads[i] = new int[2];
		
		fscanf(in, "%d", &fnum);
		fscanf(in, "%d", &snum);
		g[fnum].push_back(snum);
		g[snum].push_back(fnum);
		
		roads[i][0] = fnum;
		roads[i][1] = snum;
	}

	fclose(in);

	find_bridges();

	
	
	int* arr = new int[num_bridges];

	

	for (int i = 0; i < num_bridges; i++) {

		for (int j = 0; j < num_roads; j++) {

			if (br_roads[i][0] == roads[j][0]) {

				if (br_roads[i][1] == roads[j][1]) {

					arr[i] = j + 1;
					break;

				}

			}

			if (br_roads[i][1] == roads[j][0]) {

				if (br_roads[i][0] == roads[j][1]) {

					arr[i] = j + 1;
					break;
				}

			}
		}

	}
	
	delete[] roads;
	


	quick_sort(arr, 0, num_bridges - 1);
	

	FILE* out;
	out = fopen("bridges.out", "w");

	fprintf(out, "%d%s", num_bridges, "\n");

	for (int i = num_bridges - 1; i >= 0; i--) {

		fprintf(out, "%d%s", arr[i], " ");

	}

	fclose(out);

	return 0;
}