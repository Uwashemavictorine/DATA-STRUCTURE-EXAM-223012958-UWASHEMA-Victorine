#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

double** allocMat(int rows, int cols) {
    double** M = new double*[rows];
    M[0] = new double[rows * cols];
    for (int i = 1; i < rows; ++i)
        M[i] = M[0] + i * cols;
    return M;
}

void freeMat(double** M) {
    delete[] M[0];
    delete[] M;
}


class MatrixOp {
public:
    
    virtual double** execute(double** A, double** B,
        int r1, int c1, int r2, int c2,
        int &out_r, int &out_c) = 0;
    virtual ~MatrixOp() = default;
};

class AddOp : public MatrixOp {
public:
    double** execute(double** A, double** B,
        int r1, int c1, int r2, int c2,
        int &out_r, int &out_c) override
    {
        assert(r1 == r2 && c1 == c2);
        out_r = r1; out_c = c1;
        double** C = allocMat(out_r, out_c);
        for (int i = 0; i < out_r; ++i)
            for (int j = 0; j < out_c; ++j)
                *(*(C + i) + j) = *(*(A + i) + j) + *(*(B + i) + j);
        return C;
    }
};

class MulOp : public MatrixOp {
public:
    double** execute(double** A, double** B,
        int r1, int c1, int r2, int c2,
        int &out_r, int &out_c) override
    {
        assert(c1 == r2);
        out_r = r1; out_c = c2;
        double** C = allocMat(out_r, out_c);
        for (int i = 0; i < out_r; ++i)
            for (int j = 0; j < out_c; ++j) {
                double sum = 0;
                for (int k = 0; k < c1; ++k)
                    sum += *(*(A + i) + k) * *(*(B + k) + j);
                *(*(C + i) + j) = sum;
            }
        return C;
    }
};

class TransposeOp : public MatrixOp {
public:
    double** execute(double** A, double** /*B*/,
        int r1, int c1, int /*r2*/, int /*c2*/,
        int &out_r, int &out_c) override
    {
        out_r = c1; out_c = r1;
        double** T = allocMat(out_r, out_c);
        for (int i = 0; i < r1; ++i)
            for (int j = 0; j < c1; ++j)
                *(*(T + j) + i) = *(*(A + i) + j);
        return T;
    }
};

void printMat(double** M, int r, int c, const string& name) {
    cout << name << " (" << r << "×" << c << "):\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j)
            cout << setw(8) << *(*(M + i) + j);
        cout << "\n";
    }
    cout << "\n";
}

int main(){
    int r1 = 2, c1 = 3, r2 = 3, c2 = 2;
    double** A = allocMat(r1, c1);
    double** B = allocMat(r2, c2);

    for (int i = 0; i < r1*c1; ++i)
        A[0][i] = i + 1;

    for (int i = 0; i < r2*c2; ++i)
        B[0][i] = 7 + i;

    printMat(A, r1, c1, "A");
    printMat(B, r2, c2, "B");

    MatrixOp* opsArr[] = { new AddOp(), new MulOp(), new TransposeOp() };
    int nOps = sizeof(opsArr)/sizeof(opsArr[0]);

    for (int i = 0; i < nOps; ++i) {
        int orows, ocols;
        double** R = opsArr[i]->execute(A, B, r1, c1, r2, c2, orows, ocols);
        printMat(R, orows, ocols, "Result op#" + to_string(i));
        freeMat(R);
    }

    for (auto p : opsArr) delete p;
    freeMat(A);
    freeMat(B);

    return 0;
}
