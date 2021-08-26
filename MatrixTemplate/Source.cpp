#include "Header.h"
/*MATRICE*/
template<typename T>
Matrice<T>::Matrice(int lin, int col) {
	this->lin = lin;
	this->col = col;
	el = new T * [lin];
	for (int i = 0; i < lin; i++) {
		el[i] = new T[col];
		for (int j = 0; j < col; j++)
			el[i][j] = 0;
	}
}
template<typename T>
Matrice<T>::Matrice(const Matrice& M) {
	lin = M.lin;
	col = M.col;
	el = new T * [M.lin];
	for (int i = 0; i < M.lin; i++) {
		el[i] = new T[M.col];
		for (int j = 0; j < M.col; j++)
			el[i][j] = M.el[i][j];
	}
}
template<typename T>
Matrice<T>::~Matrice() {
	for (int i = 0; i < lin; i++) {
		delete[] el[i];
	}
	delete[] el;
}
template<typename T>
Matrice<T> Matrice<T>::minor(int l, int c) {
	Matrice R(lin - 1, col - 1);
	for (int i = 0; i < lin - 1; i++) {
		for (int j = 0; j < col - 1; j++) {
			if (i < l) {
				if (j < c)
					R[i][j] = el[i][j];
				else
					R[i][j] = el[i][j + 1];
			}
			else {
				if (j < c)
					R[i][j] = el[i + 1][j];
				else
					R[i][j] = el[i + 1][j + 1];
			}
		}
	}
	return R;
}
template<typename T>
T Matrice<T>::det() {
	if (lin != col || lin <= 1) return el[0][0];
	T S = 0;
	for (int i = 0; i < lin; i++) {
		S += el[0][i] * (i % 2 ? -1 : 1) * minor(0, i).det();
	}
	return S;
}
template<typename T>
Matrice<T> Matrice<T>::transp() {
	Matrice R(col, lin);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			R[i][j] = el[j][i];
	return R;
}
template<typename T>
Matrice<T> Matrice<T>::adj() {
	Matrice<T> R(col, lin);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			R[i][j] = minor(j, i).det() * ((i + j) % 2 ? -1 : 1);//!ordinea este importanta
	return R;
}
template<typename T>
Matrice<T> Matrice<T>::inv() {
	Matrice<T> R(col, lin);
	T d = det();
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			R[i][j] = minor(j, i).det() * ((i + j) % 2 ? -1 : 1) / d;
	return R;
}
template<typename T>
Matrice<T> Matrice<T>::operator+(const Matrice<T>& M) {
	Matrice R(lin, col);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			R[i][j] = el[i][j] + M.el[i][j];
	return R;
}
template<typename T>
Matrice<T> Matrice<T>::operator-(const Matrice<T>& M) {
	Matrice R(lin, col);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			R[i][j] = el[i][j] - M.el[i][j];
	return R;
}
template<typename T>
Matrice<T> Matrice<T>::operator*(const Matrice<T>& M) {
	Matrice R(lin, M.col);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < M.col; j++) {
			R[i][j] = 0;
			for (int k = 0; k < col; k++)
				R[i][j] += el[i][k] * M.el[k][j];
		}
	return R;
}
template<typename T>
Matrice<T> Matrice<T>::operator*(const T t) {
	Matrice R(lin, col);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++) {
			R[i][j] = t * el[i][j];
		}
	return R;
}
template<typename T>
Matrice<T> Matrice<T>::operator-() {
	Matrice R(lin, col);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++) {
			R[i][j] = -el[i][j];
		}
	return R;
}
template<typename T>
T* Matrice<T>::operator[](int index) {
	if (index >= 0 && index < lin)
		return el[index];
	return 0;
}
template<typename T>
Matrice<T> Matrice<T>::operator~() {
	return adj();
}
template<typename T>
Matrice<T> Matrice<T>::operator%(int n) {
	Matrice<T> R(lin, col);
	for (int i = 0; i < lin; i++)
		for (int j = 0; j < col; j++)
			R[i][j] = el[i][j] % n;
	return R;
}
template<typename T>
Matrice<T>& Matrice<T>::operator=(const Matrice<T>& M) {
	if (this != &M) {
		for (int i = 0; i < lin; i++) {
			delete[] el[i];
		}
		delete[] el;
		lin = M.lin;
		col = M.col;
		el = new T * [lin];
		for (int i = 0; i < lin; i++) {
			el[i] = new T[col];
			for (int j = 0; j < col; j++)
				el[i][j] = M.el[i][j];
		}
	}
	return *this;
}
template<typename T>
istream& operator >> (istream& in, Matrice<T>& M) {
	for (int i = 0; i < M.lin; i++) {
		delete[] M.el[i];
	}
	delete[] M.el;
	in >> M.lin >> M.col;
	M.el = new T * [M.lin];
	for (int i = 0; i < M.lin; i++) {
		M.el[i] = new T[M.col];
	}
	for (int i = 0; i < M.lin; i++) {
		for (int j = 0; j < M.col; j++)
			in >> M.el[i][j];
	}
	return in;
}
template<typename T>
ostream& operator << (ostream& out, const Matrice<T>& M) {
	for (int i = 0; i < M.lin; i++) {
		for (int j = 0; j < M.col; j++)
			cout << M.el[i][j] << " ";
		cout << endl;
	}
	return out;
}