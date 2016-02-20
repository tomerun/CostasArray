#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

// #define NDEBUG
#include <cassert>

using namespace std;

template<int N>
class Solver {

private:
	array<int, N> ar;
	array<bool, N> used_elem = {};
	array<array<bool, 2 * N>, N> used_diff = {};
	int ans_count = 0;

	bool check() {
		for (int gap_y = 1; gap_y < N; ++gap_y) {
			array<bool, 2 * N + 1> visited = {};
			for (int i = 0; i + gap_y < N; ++i) {
				int gap_x = ar[i + gap_y] - ar[i];
				if (visited[gap_x + N]) return false;
				visited[gap_x + N] = true;
			}
		}
		return true;
	}

	void dfs(int depth) {
		if (depth == N) {
			if (check()) {
				output();
			}
			return;
		}
		for (int i = 0; i < N; ++i) {
			if (used_elem[i]) continue;

			bool conflict = false;
			for (int j = 1; j <= depth; ++j) {
				const int diff = ar[depth - j] - i;
				if (used_diff[j][diff + N]) {
					conflict = true;
					// revert used_diff
					for (int k = 1; k < j; ++k) {
						const int revert_diff = ar[depth - k] - i;
						used_diff[k][revert_diff + N] = false;
					}
					break;
				}
				used_diff[j][diff + N] = true;
			}
			if (conflict) continue;

			ar[depth] = i;
			used_elem[i] = true;
			dfs(depth + 1);
			used_elem[i] = false;
			for (int j = 1; j <= depth; ++j) {
				int diff = ar[depth - j] - i;
				used_diff[j][diff + N] = false;
			}
		}
	}

	void output() {
		// for (int i = 0; i < N; ++i) {
		// 	cout << ar[i] << " ";
		// }
		// cout << endl;
		++ans_count;
	}

public:
	int search() {
		dfs(0);
		return ans_count;
	}
};

template<int N>
void exec() {
	Solver<N> solver;
	cout << "ans_count:" << solver.search() << endl;
}


int main(int argc, char** argv) {
	int n = 10;
	if (argc > 1) {
		n = stoi(string(argv[1]));
	}
	if (n == 10) exec<10>();
	else if (n == 11) exec<11>();
	else if (n == 12) exec<12>();
	else if (n == 13) exec<13>();
	else if (n == 14) exec<14>();
	else cout << "specified N is not supported." << endl;
}
