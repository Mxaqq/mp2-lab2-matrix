// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------
#include <cstdlib>
#include <ctime>
#include <chrono>
void displayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Vector Operations\n";
    std::cout << "2. Matrix Operations\n";
    std::cout << "3. Exit\n";
}

void performVectorOperations() {
    
    TDynamicVector<double> vector1(3);
    TDynamicVector<double> vector2(3);

    for (int i = 0; i < vector1.GetSize(); i++) {
        vector1[i] = rand() % 10;  
        vector2[i] = rand() % 10;
    }

    
    TDynamicVector<double> vectorSum = vector1 + vector2;
    TDynamicVector<double> vectorDifference = vector1 - vector2;
    TDynamicVector<double> vectorScalarProduct = vector1 * 2.0;
    double dotProduct = vector1 * vector2;

   
    std::cout << "Vector1: " << vector1 << std::endl;
    std::cout << "Vector2: " << vector2 << std::endl;
    std::cout << "Vector Sum: " << vectorSum << std::endl;
    std::cout << "Vector Difference: " << vectorDifference << std::endl;
    std::cout << "Vector Scalar Product: " << vectorScalarProduct << std::endl;
    std::cout << "Dot Product: " << dotProduct << std::endl;
}

void performMatrixOperations() {
    
    TDynamicMatrix<double> matrix1(5);
    TDynamicMatrix<double> matrix2(5);

  
    for (int i = 0; i < matrix1.GetRows(); i++) {
        for (int j = 0; j < matrix1.GetCols(); j++) {
            matrix1(i, j) = rand() % 10; 
            matrix2(i, j) = rand() % 10;
        }
    }

  
    TDynamicMatrix<double> matrixSum = matrix1 + matrix2;
    TDynamicMatrix<double> matrixDifference = matrix1 - matrix2;
    TDynamicMatrix<double> matrixScalarProduct = matrix1 * 2.0;
    auto start = std::chrono::high_resolution_clock::now(); 
    TDynamicMatrix<double> matrixProduct = matrix1 * matrix2;
    auto end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double, std::milli> duration = end - start;

   
    std::cout << "Matrix1: " << matrix1 << std::endl;
    std::cout << "Matrix2: " << matrix2 << std::endl;
    std::cout << "Matrix Sum: " << matrixSum << std::endl;
    std::cout << "Matrix Difference: " << matrixDifference << std::endl;
    std::cout << "Matrix Scalar Product: " << matrixScalarProduct << std::endl;
    std::cout << "Matrix Product: " << matrixProduct << std::endl;
    std::cout << "Matrix Multiplication Time: " << duration.count() << " milliseconds" << std::endl;
}
    
int main() {
    srand(time(0));  

    bool exit = false;
    while (!exit) {
        displayMenu();

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            performVectorOperations();
            break;
        case 2:
            performMatrixOperations();
            break;
        case 3:
            exit = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << std::endl;
    }

    return 0;
}
//---------------------------------------------------------------------------
