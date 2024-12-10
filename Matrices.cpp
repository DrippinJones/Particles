#include <iostream>
#include <iomanip>
#include <cmath>
#include "Matrices.h"
using namespace std;


//using namespace Matrices;


namespace Matrices {

	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;

		a.resize(rows);

		for (int i = 0; i < rows; i++)
		{
			a[i].resize(cols);
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				a.at(i).at(j) = 0;

				//cout << a.at(i).at(j) << " ";
			}
			//cout << endl;
		}

	}


	Matrix operator+(const Matrix& a, const Matrix& b)
	{

		Matrix localMatrix(a.getRows(), a.getCols());

		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				localMatrix(i, j) = a(i, j) + b(i, j);
			}

		}
		return localMatrix;
	}

	///Matrix multiply.  See description.
	///usage:  c = a * b;
	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		Matrix c(a.getRows(), b.getCols());

		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		for (int k = 0; k < b.getCols(); k++)
		{
			for (int i = 0; i < a.getRows(); i++)
			{
				c(i, k) = 0;
				for (int j = 0; j < a.getCols(); j++)
				{
					c(i, k) += a(i, j) * b(j, k);

				}

			}

		}

		return c;

	}

	///Matrix comparison.  See description.
	///usage:  a == b
	bool operator==(const Matrix& a, const Matrix& b)
	{

		if (a.getRows() != b.getRows())
		{
			return false;
		}
		else if (a.getCols() != b.getCols())
		{
			return false;
		}


		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) > 0.001)
				{
					return false;
				}
			}
		}

		return true;
	}

	///Matrix comparison.  See description.
	///usage:  a != b
	bool operator!=(const Matrix& a, const Matrix& b)
	{

		if (a.getRows() != b.getRows())
		{
			return true;
		}
		else if (a.getCols() != b.getCols())
		{
			return true;
		}

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (abs(a(i, j) - b(i, j)) > 0.001)
				{
					return true;
				}
			}
		}

		return false;
	}

	///Output matrix.
	///Separate columns by ' ' and rows by '\n'
	ostream& operator<<(ostream& os, const Matrix& a)
	{
		//os << "a:" << '\n' << setw(10);

		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(10) << a(i, j) << " ";
			}

			os << endl;
		}


		return os;
	}


	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
		a[0][0] = cos(theta);

		a[0][1] = -sin(theta);
		
		a[1][0] = sin(theta);
		
		a[1][1] = cos(theta);
		
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
		a[0][0] = scale;

		a[0][1] = 0;

		a[1][0] = 0;

		a[1][1] = scale;
	
	}
	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < nCols; j++)
			{
				if (i == 0)
				{
					a[i][j] = xShift;
				}
				else
				{
					a[i][j] = yShift;
				}
			}
		}
	}
}

