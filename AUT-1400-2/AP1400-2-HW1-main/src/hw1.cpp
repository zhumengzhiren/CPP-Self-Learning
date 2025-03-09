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
        // Notify to avoid segmentation fault by checking the size of the matrix before accessing the elements
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
        // Check if the matrices are empty, return an empty matrix
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

    double determinant(const Matrix& matrix) {
        // Check if the matrix is empty, return 1 for the determinant of an empty matrix
        if (matrix.empty())
            return 1;
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Check if the matrix is square
        if (rows != cols)
            throw std::logic_error("non-square matrix");
        // Base case for 1x1 matrix
        if (rows == 1)
            return matrix[0][0];
        // Base case for 2x2 matrix
        if (rows == 2)
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        // Initialize the determinant value
        double det = 0;
        // Iterate over the first row of the matrix
        for (size_t i = 0; i < cols; ++i) {
            // Calculate the minor matrix for the current element
            Matrix m = minor(matrix, 0, i);
            // Calculate the determinant of the minor matrix
            double minor_det = determinant(m);
            // Add the product of the element and the determinant of the minor matrix
            det += (i % 2 == 0 ? 1 : -1) * matrix[0][i] * minor_det;
        }
        return det;
    }

    Matrix inverse(const Matrix& matrix) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Check if the matrix is square
        if (rows != cols)
            throw std::logic_error("non-square matrix");
        // Calculate the determinant of the input matrix
        double det = determinant(matrix);
        // Check if the determinant is zero
        if (det == 0)
            throw std::logic_error("matrix is singular, cannot be inverted");
        size_t n = rows;
        Matrix adj(n, Vector(n));
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                Matrix m = minor(matrix, i, j);
                double minor_det = determinant(m);
                adj[j][i] = (i + j) % 2 == 0 ? minor_det : -minor_det;
            }
        }
        return multiply(adj, 1 / det);
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, size_t axis) {
        // Check if the matrices are empty
        if (matrix1.empty() && matrix2.empty())
            return Matrix();
        // Get the number of rows and columns for both matrices
        size_t rows1 = matrix1.size();
        size_t cols1 = (rows1 > 0) ? matrix1[0].size() : 0;
        size_t rows2 = matrix2.size();
        size_t cols2 = (rows2 > 0) ? matrix2[0].size() : 0;
        // Check if the matrices are empty
        if (rows1 == 0 && rows2 == 0)
            return Matrix();
        // Check if the dimensions of the matrices are the same along the specified axis
        if (axis == 0 && cols1 != cols2)
            throw std::logic_error("matrices with different number of columns cannot be concatenated along axis 0");
        if (axis == 1 && rows1 != rows2)
            throw std::logic_error("matrices with different number of rows cannot be concatenated along axis 1");
        // Initialize the result matrix
        Matrix result;
        // Concatenate along the rows (axis 0)
        if (axis == 0) {
            result = matrix1;
            result.insert(result.end(), matrix2.begin(), matrix2.end());
        }
        // Concatenate along the columns (axis 1)
        else if (axis == 1) {
            for (size_t i = 0; i < rows1; ++i) {
                Vector row = matrix1[i];
                row.insert(row.end(), matrix2[i].begin(), matrix2[i].end());
                result.push_back(row);
            }
        }
        return result;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Check if the row indices are within the bounds of the matrix
        if (r1 >= rows || r2 >= rows)
            throw std::out_of_range("r1 or r2 index out of range");
        // Initialize the result matrix with the same size as the input matrix
        Matrix result = matrix;
        // Swap the rows
        swap(result[r1], result[r2]);
        return result;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Check if the row index is within the bounds of the matrix
        if (r >= rows)
            throw std::out_of_range("r index out of range");
        // Initialize the result matrix with the same size as the input matrix
        Matrix result = matrix;
        // Multiply the specified row by the constant
        for (size_t j = 0; j < cols; ++j)
            result[r][j] *= c;
        return result;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Check if the row indices are within the bounds of the matrix
        if (r1 >= rows || r2 >= rows)
            throw std::out_of_range("r1 or r2 index out of range");
        // Initialize the result matrix with the same size as the input matrix
        Matrix result = matrix;
        // Add the product of the specified row and constant to another row
        for (size_t j = 0; j < cols; ++j)
            result[r2][j] += c * result[r1][j];
        return result;
    }

    Matrix upper_triangular(const Matrix& matrix) {
        // Check if the matrix is empty
        if (matrix.empty())
            return Matrix();
        // Check if the matrix is square
        if (matrix.size() != matrix[0].size())
            throw std::logic_error("non-square matrix");
        // Get the number of rows and columns of the input matrix
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        // Initialize the result matrix with the same size as the input matrix
        Matrix result = matrix;
        // Use nested loops to iterate over the rows and columns of the input matrix
        for (size_t i = 0; i < rows; ++i) {
            size_t pivot = i;
            // Find the pivot element in the current column
            while (pivot < rows && result[pivot][i] == 0)
                ++pivot;
            // Check if the pivot element is zero
            if (pivot == rows)
                continue;
            // Swap the rows to move the pivot element to the current row
            result = ero_swap(result, i, pivot);
            // Eliminate the elements below the pivot element
            for (size_t j = i + 1; j < rows; ++j) {
                double factor = result[j][i] / result[i][i];
                result = ero_sum(result, i, -factor, j);
            }
        }
        return result;
    }
}
