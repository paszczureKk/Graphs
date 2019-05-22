#include <iostream>

inline int pow(int n) {
	return n * n;
}

inline bool GetValue() {
	return (getchar() & 1U);
}

bool GetAnswer(int d, bool* t) {

}


int main() {

	int n = 0;
	int d = 0;
	int size = 1000;
	bool* t = (bool*)malloc(size * sizeof(bool));

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {

		scanf("%d", &d);
		int p = pow(d);

		while (p > size) {
			size *= 2;
			t = (bool*)realloc(t, size * sizeof(bool));
		}

		for (int j = 0; j < p ; j++) {
			t[j] = GetValue();
		}

		fputs(GetAnswer(d, t) ? "true" : "false", stdout);

	}

	delete t;

	return 0;
}