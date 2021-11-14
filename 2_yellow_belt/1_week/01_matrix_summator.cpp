/*
Предисловие
Если вы не уверены, стоит ли вам сначала пройти наш первый курс,
или у вас достаточно знаний, чтобы начать с «Жёлтого пояса», попробуйте
решить эту задачу. Если вы не понимаете её условие или не можете быстро
решить, скорее всего, вам надо сначала пройти «Белый пояс».

Условие
В этой задаче вам надо разработать класс Matrix для представления
целочисленной матрицы. Более подробно, класс Matrix должен иметь:

	---> конструктор по умолчанию, который создаёт матрицу с нулём строк
	и нулём столбцов

	---> конструктор от двух целочисленных параметров: num_rows и num_cols,
	 — которые задают количество строк и столбцов матрицы соответственно

	---> метод Reset, принимающий два целочисленных параметра, которые задают
	новое количество строк и столбцов матрицы соответственно; метод Reset меняет
	размеры матрицы на заданные и обнуляет все её элементы

	---> константный метод At, который принимает номер строки и номер столбца
	(именно в этом порядке; нумерация строк и столбцов начинается с нуля) и
	 возвращает значение в соответствущей ячейке матрицы

	---> неконстантный метод At с такими же параметрами, но возвращающий ссылку
	на значение в соответствущей ячейке матрицы

	---> константные методы GetNumRows и GetNumColumns, которые возвращают
	количество строк и столбцов матрицы соответственно


Если количество строк или количество столбцов, переданное в конструктор класса Matrix
или метод Reset, оказалось отрицательным, то должно быть выброшено стандартное
исключение out_of_range.

Это же исключение должен бросать метод At, если переданная в него ячейка выходит
за границы матрицы.

Кроме того, для класса Matrix должны быть определены следующие операторы:

	---> оператор ввода из потока istream; формат ввода простой — сначала задаётся
	количество строк и столбцов (именно в этом порядке), а затем все элементы матрицы:
	сначала элемент первой строки и первого столбца, затем элемент первой строки и
	второго столбца и так далее

	---> оператор вывода в поток ostream; он должен выводить матрицу в том же формате,
	в каком её читает оператор ввода, — в первой строке количество строк и столбцов, во
	второй — элементы первой строки, в третьей — элементы второй строки и т.д.

	---> оператор проверки на равенство (==): он должен возвращать true, если сравниваемые
	матрицы имеют одинаковый размер и все их соответствующие элементы равны между собой, в
	противном случае он должен возвращать false.

	---> оператор сложения: он должен принимать две матрицы и возвращать новую матрицу,
	которая является их суммой; если переданные матрицы имеют разные размеры этот оператор
	должен выбрасывать стандартное исключение invalid_argument.

 * */


#include <iostream>
#include <vector>
#include <sstream>
#include <exception>
#include <string>
#include <stdexcept>
using namespace std;


class Matrix{

public:
	Matrix(){
		num_rows = 0;
		num_cols = 0;
	}

	Matrix(const int& num_rows, const int& num_cols) {
		Reset(num_rows, num_cols);
	}

	void Reset(int new_num_rows, int new_num_cols){
		if (new_num_rows < 0 || new_num_cols < 0){
			throw out_of_range("Input negative argument");
		}
		if (new_num_rows == 0 || new_num_cols == 0){
			new_num_rows = new_num_cols = 0;
		}
		num_rows = new_num_rows;
		num_cols = new_num_cols;
		matrix.assign(new_num_rows, vector<int>(new_num_cols));
	}

	int At(const int& pos_row, const int& pos_col) const{
		return matrix.at(pos_row).at(pos_col);
	}

	int& At(const int& pos_row, const int& pos_col) {
		return matrix.at(pos_row).at(pos_col);
	}

	int GetNumRows() const {
		return num_rows;
	}

	int GetNumColumns() const {
		return num_cols;
	}

private:

	vector<vector<int>> matrix;
	int num_rows;
	int num_cols;

};

istream& operator >> (istream& stream_in, Matrix& m){
	int rows, cols;
	stream_in >> rows >> cols;
	m.Reset(rows, cols);
	for (int i=0; i<rows; ++i){
		for (int j=0; j<cols; ++j){
			stream_in >> m.At(i, j);
		}
	}
	return stream_in;
}

ostream& operator << (ostream& stream_out, const Matrix& m){
	stream_out << m.GetNumRows() << ' ' << m.GetNumColumns() << endl;
	for (int i=0; i<m.GetNumRows(); ++i){
		for (int j=0; j<m.GetNumColumns(); ++j){
			stream_out << m.At(i, j) << ' ';
		}
		stream_out << endl;
	}
	return stream_out;
}


bool operator == (const Matrix& first, const Matrix& second){
	if (first.GetNumRows() != second.GetNumRows() && first.GetNumColumns() != second.GetNumColumns()){
		return false;
	}
	for (int i=0; i<first.GetNumRows(); ++i){
		for (int j=0; j<first.GetNumColumns(); ++j){
			if (first.At(i, j) != second.At(i, j)){
				return false;
			}
		}
	}
	return true;
}

Matrix operator + (const Matrix& first, const Matrix& second){
	if (first.GetNumRows() != second.GetNumRows() && first.GetNumColumns() != second.GetNumColumns()){
		throw invalid_argument("Matrix have different size");
	}
	Matrix new_matrix(first.GetNumRows(), first.GetNumColumns());
	for (int i=0; i<first.GetNumRows(); ++i){
		for (int j=0; j<first.GetNumColumns(); ++j){
			new_matrix.At(i, j) = first.At(i, j) + second.At(i, j);
		}
	}
	return new_matrix;
}

int main() {
	Matrix one;
	Matrix two;
	cin >> one >> two;
	cout << one + two << endl;
	return 0;
}
