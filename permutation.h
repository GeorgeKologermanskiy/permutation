#include <iostream>

class Permutation {
private:
	int *a;
	int n;
	void swapIndex(int i, int j);
	void reverseSuffix(int i);
	int findSamePrefix(const Permutation & b)const;
public:
	Permutation();
	Permutation(const int n);
	Permutation(const int n, int arr[]);
	Permutation(const Permutation & c);
	~Permutation();
	const int& operator[](int index)const;
	Permutation next()const;
	Permutation previous()const;
	Permutation& operator++();
	Permutation operator++(int);
	Permutation& operator--();
	Permutation operator--(int);
	bool operator < (const Permutation & b)const;
	bool operator > (const Permutation & b)const;
	bool operator == (const Permutation & b)const;
	bool operator != (const Permutation & b)const;
	bool operator <= (const Permutation & b)const;
	bool operator >= (const Permutation & b)const;
	Permutation& operator=(const Permutation & b);
	friend Permutation& operator*=(Permutation & le, const Permutation & b);
	Permutation inverse()const;
	void operator()(int *arr)const;
	bool isOdd()const;
	bool isEven()const;
	Permutation pow(int degree)const;
	friend std::ostream& operator << (std::ostream& in, const Permutation & x);
};

void Permutation::swapIndex(int i, int j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}

void Permutation::reverseSuffix(int i) {
	for (int j = i; j < n - 1 - j + i; j++)
		swapIndex(j, n - 1 - j + i);
}

int Permutation::findSamePrefix(const Permutation & b)const {
	int i; for (i = 0; i < n && i < b.n && a[i] == b[i]; i++);
	return i;
}

Permutation::Permutation() {}

Permutation::Permutation(const int n) :n(n) {
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = i;
}

Permutation::Permutation(const int n, int arr[]) : n(n) {
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = arr[i];
}

Permutation::Permutation(const Permutation & c) : n(c.n) {
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = c[i];
}

Permutation::~Permutation() {
	delete[] a;
}

const int& Permutation::operator[](int index)const {
	return a[index];
}

Permutation Permutation::next()const {
	Permutation ret(*this);
	if (n == 1)return ret;
	int j; for (j = n - 2;; j--) {
		if (ret[j] < ret[j + 1])
			break;
		if (j == 0) {
			return ret;
		}
	}
	int l; for (l = n - 1; ret[l] < ret[j]; l--);
	ret.swapIndex(j, l);
	ret.reverseSuffix(j + 1);
	return ret;
}

Permutation Permutation::previous()const {
	Permutation ret(*this);
	if (n == 1) {
		return ret;
	}
	int j; for (j = n - 2;; j--) {
		if (ret[j] > ret[j + 1])break;
		if (j == 0) {
			return ret;
		}
	}
	int l; for (l = n - 1; ret[l] > ret[j]; l--);
	ret.swapIndex(j, l);
	ret.reverseSuffix(j + 1);
	return ret;
}

Permutation& Permutation::operator++() {//++i
	Permutation add = next();
	for (int i = 0; i < n; i++)
		a[i] = add[i];
	return *this;
}

Permutation Permutation::operator++(int) {//i++
	Permutation Old = Permutation(*this);
	++*this;
	return Old;
}

Permutation& Permutation::operator--() {//--i
	Permutation add = previous();
	for (int i = 0; i < n; i++)
		a[i] = add[i];
	return *this;
}

Permutation Permutation::operator--(int) {//i--
	Permutation Old = Permutation(*this);
	--*this;
	return Old;
}

bool Permutation::operator < (const Permutation & b)const {
	int i = findSamePrefix(b);
	if (i == b.n && i == n)return false;
	if (i == b.n)return false;
	if (i == n)return true;
	return (a[i] < b[i]);
}

bool Permutation::operator > (const Permutation & b)const {
	int i = findSamePrefix(b);
	if (i == n && i == b.n)return false;
	if (i == n)return false;
	if (i == b.n)return true;
	return (a[i] > b[i]);
}

bool Permutation::operator == (const Permutation & b)const {
	int i = findSamePrefix(b);
	return (i == n && i == b.n);
}

bool Permutation::operator != (const Permutation & b)const {
	int i = findSamePrefix(b);
	return (i != n || i != b.n);
}

bool Permutation::operator <= (const Permutation & b)const {
	int i = findSamePrefix(b);
	if (i == n && i == b.n)return true;
	if (i == n)return true;
	if (i == b.n)return false;
	return (a[i] < b[i]);
}

bool Permutation::operator >= (const Permutation & b)const {
	int i = findSamePrefix(b);
	if (i == b.n && i == n)return true;
	if (i == b.n)return true;
	if (i == n)return false;
	return (a[i] > b[i]);
}

Permutation& Permutation::operator=(const Permutation & b) {
	if (this == &b)return *this;
	n = b.n;
	delete[] a;
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = b[i];
	return *this;
}

Permutation Permutation::inverse()const {
	Permutation ret(n);
	for (int i = 0; i < n; i++) {
		ret.a[a[i]] = i;
	}
	return ret;
}

void Permutation::operator()(int *arr)const {
	int *buffer = new int[n];
	for (int i = 0; i < n; i++)
		buffer[a[i]] = arr[i];
	for (int i = 0; i < n; i++)
		arr[i] = buffer[i];
	delete[] buffer;
}

Permutation& operator*=(Permutation & le, const Permutation & b) {
	int *buffer = new int[le.n];
	for (int i = 0; i < le.n; i++)
		buffer[i] = le[b[i]];
	for (int i = 0; i < le.n; i++)
		le.a[i] = buffer[i];
	delete[] buffer;
	return le;
}

Permutation operator*(const Permutation & a, const Permutation & b) {
	Permutation aa = Permutation(a);
	return (aa *= b);
}

bool Permutation::isOdd()const {
	Permutation T(*this);
	int* pos = new int[n];
	for (int i = 0; i < n; i++)
		pos[T[i]] = i;
	int Changes = 0;
	for (int i = 0; i < n; i++) {
		if (pos[i] != i) {
			pos[T[i]] = pos[i];
			T.swapIndex(i, pos[i]);
			Changes++;
		}
	}
	delete[] pos;
	return (Changes % 2 == 1);
}

bool Permutation::isEven()const {
	return (!isOdd());
}

Permutation Permutation::pow(const int degree)const {
	if (degree == 0)
		return n;
	if (degree < 0) {
		return (inverse().pow(-degree));
	}
	Permutation ret(n);
	int *ind = new int[n];
	bool *u = new bool[n];
	for (int i = 0; i < n; i++) {
		ind[i] = u[i] = 0;
	}
	for (int i = 0; i < n; i++)if (!u[i]) {
		int cycleSize = 0;
		int idx = i;
		do {
			u[idx] = 1;
			ind[cycleSize] = idx;
			idx = a[idx];
			cycleSize++;
		} while (!u[idx]);
		int rotate = (degree - 1) % cycleSize;
		for (int j = 0; j < cycleSize; j++) {
			ret.a[ind[(j - rotate + cycleSize + cycleSize) % cycleSize]] = a[ind[j]];
		}
	}
	delete[] u;
	delete[] ind;
	return ret;
}

std::ostream& operator << (std::ostream& in, const Permutation & x) {
	for (int i = 0; i < x.n; i++)
		in << x[i] << (i == x.n - 1 ? "" : " ");
	return in;
}