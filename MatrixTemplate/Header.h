#pragma once
#include <iostream>
using namespace std;

/*MATRICE*/
template<typename T>
class Matrice {
protected:
	T** el;
	int lin, col;
public:
	/*constructor*/
	Matrice(int lin = 2, int col = 2);
	Matrice(const Matrice<T>&);
	/*destructor*/
	~Matrice();
	/*metode*/
	int NrLin() { return lin; }
	int NrCol() { return col; }
	Matrice<T> minor(int l, int c);/*calculeaza minorul corespunzator pentru liia l, coloana c*/
	T det();/*calculeaza valoarea determinantului matricei matrice*/
	Matrice<T> transp();/*calculeaza transpusa unei matrice*/
	Matrice<T> adj();/*calculeaza adjuncta unei matrice*/
	Matrice<T> inv();/*calculeaza inversa unei matrice*/
	/*supraincarcare operatori*/
	Matrice<T> operator+(const Matrice<T>&);/*calculeaza suma a doua matrice*/
	Matrice<T> operator-(const Matrice<T>&);/*calculeaza diferenta a doua matrice*/
	Matrice<T> operator*(const Matrice<T>&);/*calculeaza produsul a doua matrice*/
	Matrice<T> operator*(const T);/*calculeaza produsul unei matrice cu un scalar*/
	Matrice<T> operator-();/*schimba semnul elementelor*/
	Matrice<T> operator~();/*calculeaza adjuncta unei matrice*/
	Matrice<T> operator%(int n);/*calculeaza modulo pentru elemente*/

	Matrice<T>& operator=(const Matrice<T>&);
	T* operator[](int);
	template<typename T> friend istream& operator >> (istream& in, Matrice<T>&);
	template<typename T> friend ostream& operator << (ostream& out, const Matrice<T>&);
	template<typename T> friend class Vector;
};