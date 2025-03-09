#include "hw1.h"


namespace algebra {
    Matrix zeros(size_t n, size_t m) {
        // Construct over a constructor
        return Matrix(n, Vector(m, 0));
    }

    Matrix ones(size_t n, size_t m) {
        return Matrix(n, Vector(m, 1));
    }

    Matrix random(size_t n, size_t m, double min, double max) {
        // Omitted the brackets for the if statement since it has only one line
        if (min >= max)
            throw std::logic_error("min cannot be greater than max");
        // Random number generator
        std::random_device rd;
        // Mersenne Twister engine with a seed from random device
        std::mt19937 gen(rd());
        // Generate random numbers between min and max
        std::uniform_real_distribution<double> dis(min, max);
        // initialize the matrix with vector constructor
        Matrix matrix(n, Vector(m));
        // auto keyword is used to avoid the long type name
        // use colon to avoid copying the elements, like go slices
        for (auto& row : matrix)
            for (auto& elem : row)
                elem = dis(gen);
        return matrix;
    }

    void show(const Matrix& matrix) {
        if (matrix.empty()) {
            std::cout << std::endl;
            return;
        }
        // Get the number of columns using size
        size_t cols = matrix[0].size();
        // Set the precision to 3 decimal points
        for (const auto& row : matrix) {
            // Use ostringstream to format the output
            std::ostringstream oss;
            for (size_t i = 0; i < row.size(); ++i) {
                // When i is not 0, add a space
                if (i != 0) oss << ' ';
                // Set the precision to 3 decimal points
                oss << std::fixed << std::setprecision(3) << row[i];
            }
            // Print the formatted string
            std::cout << oss.str() << '\n';
        }
    }

    Matrix multiply(const Matrix& matrix, double c) {
        if (matrix.empty())
            return Matrix();
        // Initialize the matrix with the same size as the input matrix
        Matrix result(matrix.size(), Vector(matrix[0].size()));
        // Use range-based for loop to iterate over the matrix
        for (size_t i = 0; i < matrix.size(); ++i)
            for (size_t j = 0; j < matrix[i].size(); ++j)
                // Multiply each element by c
                result[i][j] = matrix[i][j] * c;
        return result;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        // Get the number of rows and columns for both matrices, add check for empty matrices to avoid undefined behavior
        size_t rows1 = matrix1.size();
        size_t cols1 = (rows1 > 0) ? matrix1[0].size() : 0;
        size_t rows2 = matrix2.size();
        size_t cols2 = (rows2 > 0) ? matrix2[0].size() : 0;
        // Check if the number of columns in the first matrix is equal to the number of rows in the second matrix
        if (cols1 != rows2)
            throw std::logic_error("matrices with wrong dimensions cannot be multiplied");
        // Initialize the result matrix with the size of the first matrix's rows and the second matrix's columns
        Matrix result(rows1, Vector(cols2, 0));
        // Use nested loops to iterate over the rows and columns of the result matrix
        for (size_t i = 0; i < rows1; ++i)
            for (size_t j = 0; j < cols2; ++j)
                // Use another loop to calculate the dot product of the corresponding row in the first matrix and column in the second matrix
                for (size_t k = 0; k < cols1; ++k)
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
        return result;
    }

    Matrix sum(const Matrix& matrix, double c) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Initialize the result matrix with the same size as the input matrix
        Matrix result(matrix.size(), Vector(matrix[0].size()));
        
        // Use range-based for loop to iterate over the matrix
        for (size_t i = 0; i < matrix.size(); ++i)
            for (size_t j = 0; j < matrix[i].size(); ++j)
                // Add c to each element
                result[i][j] = matrix[i][j] + c;
        return result;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        // Get the number of rows and columns for both matrices, add check for empty matrices to avoid undefined behavior
        size_t rows1 = matrix1.size();
        size_t cols1 = (rows1 > 0) ? matrix1[0].size() : 0;
        size_t rows2 = matrix2.size();
        size_t cols2 = (rows2 > 0) ? matrix2[0].size() : 0;
        // Check if the dimensions of the matrices are the same
        if (rows1 != rows2 || cols1 != cols2)
            throw std::logic_error("matrices with different dimensions cannot be summed");
        // Check if the matrices are empty
        if (rows1 == 0 || cols1 == 0 || rows2 == 0 || cols2 == 0)
            return Matrix();
        // Initialize the result matrix with the same size as the input matrices
        Matrix result(rows1, Vector(cols1));
        // Use nested loops to iterate over the rows and columns of the result matrix
        for (size_t i = 0; i < rows1; ++i)
            for (size_t j = 0; j < cols1; ++j)
                // Add the corresponding elements from both matrices
                result[i][j] = matrix1[i][j] + matrix2[i][j];
        return result;
    }

    Matrix transpose(const Matrix& matrix) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Initialize the result matrix with the size of the input matrix's columns and rows
        Matrix result(cols, Vector(rows));
        // Use nested loops to iterate over the rows and columns of the input matrix
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                // Transpose the elements by swapping the row and column indices
                result[j][i] = matrix[i][j];
        return result;
    }

    Matrix minor(const Matrix& matrix, size_t row, size_t col) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Check if the row and column indices are within the bounds of the matrix
        if (row >= rows || col >= cols)
            throw std::out_of_range("row or col index out of range");
        // Initialize the result matrix with the size of the input matrix's rows and columns
        Matrix result(rows - 1, Vector(cols - 1));
        // Use nested loops to iterate over the rows and columns of the input matrix
        for (size_t i = 0, r = 0; i < rows; ++i) {
            // Skip the specified row
            if (i == row)
                continue;
            for (size_t j = 0, c = 0; j < cols; ++j) {
                // Skip the specified column
                if (j == col)
                    continue;
                // Copy the element to the result matrix
                result[r][c] = matrix[i][j];
                ++c;
            }
            ++r;
        }
        return result;
    }
}

// main 函数示例
// int main() {
//     using namespace algebra;

//     // 测试 zeros 函数
//     Matrix mat1 = zeros(2, 3);
//     std::cout << "zeros(2,3):\n";
//     show(mat1);
//     std::cout << std::endl;

//     // 测试 random 函数（生成 2x3 矩阵，数值范围 [0, 1]）
//     Matrix mat2 = random(2, 3, 0.0, 1.0);
//     std::cout << "random(2,3, 0.0, 1.0):\n";
//     show(mat2);
//     std::cout << std::endl;

//     // 测试单行矩阵
//     Matrix mat3 = zeros(1, 4);
//     mat3[0][0] = 3.1415;
//     mat3[0][1] = 2.71828;
//     std::cout << "单行矩阵:\n";
//     show(mat3);
//     std::cout << std::endl;

//     // 测试空矩阵
//     Matrix mat4 = zeros(0, 5);
//     std::cout << "空矩阵 (0x5):\n";
//     show(mat4);

//     return 0;
// }

