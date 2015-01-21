/*
ID: zhangwt1
PROG: transform
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;

struct Coordinate
{
    int x;
    int y;
};

Coordinate to_coord(int i, int j, int dim)
{
    if (dim%2 == 0)
    {
        int offset = dim-1;
        return Coordinate{j*2-offset, -i*2+offset};
    }
    else
    {
        int offset = (dim-1)/2;
        return Coordinate{j-offset, -i+offset};
    }
}

Coordinate to_ij(int x, int y, int dim)
{
    if(dim%2 == 0)
    {
        int offset = dim-1;
        return Coordinate{(-y+offset)/2, (x+offset)/2};
    }
    else
    {
        int offset = (dim-1)/2;
        return Coordinate{-y+offset, x+offset};
    }
}

Coordinate trans_90(int x, int y)
{
    return Coordinate{y, -x};
}

Coordinate trans_180(int x, int y)
{
    return Coordinate{-x, -y};
}

Coordinate trans_270(int x, int y)
{
    return Coordinate{-y, x};
}

Coordinate trans_reflection(int x, int y)
{
    return Coordinate{-x, y};
}

Coordinate trans_reflection_90(int x, int y)
{
    Coordinate c = trans_reflection(x, y);
    return trans_90(c.x, c.y);
}

Coordinate trans_reflection_180(int x, int y)
{
    Coordinate c = trans_reflection(x, y);
    return trans_180(c.x, c.y);
}

Coordinate trans_reflection_270(int x, int y)
{
    Coordinate c = trans_reflection(x, y);
    return trans_270(c.x, c.y);
}

Coordinate trans_notrans(int x, int y)
{
    return Coordinate{x, y};
}

typedef Coordinate (*trans_func)(int x, int y);

class Matrix
{
    public:
        Matrix(int dim) : dim(dim) {this->m = new char [dim*dim];}
        ~Matrix() {delete[] this->m;}
        void read_matrix(ifstream& fin);
        void put(int i, int j, char v) {this->m[i*this->dim+j] = v;}
        char get(int i, int j) const {return this->m[i*this->dim+j];}
        bool transed_matrix(Matrix& other, trans_func func);
    private:
        int dim;
        char* m;
};

inline void Matrix::read_matrix(ifstream& fin)
{
    char c;
    for (int i = 0; i != this->dim; ++i)
    {
        for (int j = 0; j != this->dim; ++j)
        {
            fin >> c;
            this->put(i, j, c);
        }
    }
}

inline bool Matrix::transed_matrix(Matrix& other, trans_func func)
{
    for (int i = 0; i != this->dim; ++i)
    {
        for (int j = 0; j != this->dim; ++j)
        {
            Coordinate c = to_coord(i, j, this->dim);
            Coordinate tc = (*func)(c.x, c.y);
            Coordinate ij = to_ij(tc.x, tc.y, this->dim);

#ifdef DEBUG
            cout << this->get(i, j) << " ";
            cout << "(" << i << "," << j << ") -> "
                << "(" << c.x << "," << c.y << ") -> "
                << "(" << tc.x << "," << tc.y << ") -> "
                << "(" << ij.x << "," << ij.y << ") ";
            cout << other.get(ij.x, ij.y) << endl;
#endif

            if (this->get(i, j) != other.get(ij.x, ij.y))
            {
#ifdef DEBUG
                cout << endl;
#endif
                return false;
            }
        }
    }
#ifdef DEBUG
    cout << endl;
#endif
    return true;
}

int main()
{
    ifstream fin{"transform.in"};
    ofstream fout{"transform.out"};

    int N;
    fin >> N;

    Matrix m{N}, tm{N};
    m.read_matrix(fin);
    tm.read_matrix(fin);

    if (m.transed_matrix(tm, trans_90))
    {
        fout << "1" << endl;
        return 0;
    }
    if (m.transed_matrix(tm, trans_180))
    {
        fout << "2" << endl;
        return 0;
    }
    if (m.transed_matrix(tm, trans_270))
    {
        fout << "3" << endl;
        return 0;
    }
    if (m.transed_matrix(tm, trans_reflection))
    {
        fout << "4" << endl;
        return 0;
    }
    if (m.transed_matrix(tm, trans_reflection_90)
            || m.transed_matrix(tm, trans_reflection_180)
            || m.transed_matrix(tm, trans_reflection_270))
    {
        fout << "5" << endl;
        return 0;
    }
    if (m.transed_matrix(tm, trans_notrans))
    {
        fout << "6" << endl;
        return 0;
    }

    fout << "7" << endl;
    return 0;
}

