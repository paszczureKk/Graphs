
#include <iostream>
#include <string>
#include <vector>

void debugprint(bool* matrix, int d) {
	for (int i = 0; i < d * d; i++) {
		if (i % d == 0) {
			std::cout << std::endl;
		}
		if (matrix[i] == true) {
			std::cout << '1';
		}
		else {
			std::cout << '0';
		}
	}

	std::cout << std::endl << std::endl;
}

bool LookForCycle(int d, bool* matrix) {

	int* temp = (int*)malloc(d * sizeof(int));

	for (int i = 0; i < d; i++) {
		temp[i] = 0;
	}

	for (int i = 0; i < d; i++) {
		if (matrix[i * d + i] == true) {
			
			if (temp[i] == 0) {
				temp[i] = 1;
			}

			for (int j = 0; j < d; j++) {
				if (i == j) {
					continue;
				}

				if (matrix[i * d + j] == true && temp[j] == 0) {
					temp[j] = temp[i] % 2 + 1;
				}

				if (matrix[i * d + j] == true && temp[j] == temp[i]) {
					free(temp);
					return true;
				}
			}
		}
	}

	free(temp);
	return false;

}

bool GetSingleAnswer(int d, int d2, int sum, int max, bool* matrix) {

	if (sum == d2 * (d2 - 1)) {
		return true;
	}
	else {
		if (max > 2) {
			return false;
		}
		else {
			if (max == 2) {
				//return LookForCycle(d, matrix);
				if (sum == 2 * d2) {
					if (d2 % 2 == 0) {
						return false;
					}
					else {
						return true;
					}
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		}
	}

}

bool GetAnswer(int d, std::string input, bool* t, bool* matrix) {

	bool answer = true;

	std::vector<int> queue;

	for (int i = 0; i < d; i++) {
		t[i] = false;
	}

	for (int i = 0; i < d; i++) {

		if (t[i] == true) {
			continue;
		}

		for (int j = 0; j < d * d; j++) {
			matrix[j] = false;
		}

		int d2 = 1;
		int sum = 0;
		int max = 0;

		queue.push_back(i);
		matrix[i] = true;
		t[i * d + i] = true;

		while (queue.empty() == false) {

			int temp = 0;

			int m = queue[queue.size() - 1];
			queue.pop_back();
			
			for (int j = 0; j < d; j++) {

				if (j == m) {
					continue;
				}

				if (input[m * d + j] == '1') {
					if (t[j] == false) {
						queue.push_back(j);
						d2++;
						t[j] = true;
						matrix[j * d + j] = true;
					}

					matrix[m * d + j] = true;
					matrix[j * d + m] = true;
					temp++;
					sum++;

				}
			}

			if (temp > max) {
				max = temp;
			}

		}

		answer = answer && GetSingleAnswer(d, d2, sum, max, matrix);

	}

	return answer;

}


int main() {

	int n = 0;
	int d = 0;
	std::string input;
	bool t[65536];
	bool matrix[65536];

	std::cin >> n;

	for (int i = 0; i < n; i++) {

		std::cin >> d;
		std::cin >> input;

		std::cout << (GetAnswer(d, input, t, matrix) ? "True" : "False") << std::endl;

	}

	system("pause");
	return 0;
}