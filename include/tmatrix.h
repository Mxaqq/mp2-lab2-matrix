// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
  }
  TDynamicVector(TDynamicVector&& v) sz(v.sz), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v)
      {
          delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v)
      {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }

      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz)
          return false;

      for (size_t i = 0; i < this->sz; ++i)
          if (this->pMem[i] != v.pMem[i]) return false;

      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = this->pMem[i] + val;

      return result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = this->pMem[i] - val;

      return result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = this->pMem[i] * val;

      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz != v.sz)
          throw invalid_argument("Vectors should be of the same size for addition");

      TDynamicVector<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = this->pMem[i] + v.pMem[i];

      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.sz)
          throw invalid_argument("Vectors should be of the same size for subtraction");

      TDynamicVector<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = this->pMem[i] - v.pMem[i];

      return result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (this->sz != v.sz)
          throw invalid_argument("Vectors should be of the same size for dot product!");

      T result{};
      for (size_t i = 0; i < this->sz; ++i)
          result += this->pMem[i] * v.pMem[i];

      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz)
          return false;

      for (size_t i = 0; i < this->sz; i++)
          if (!((*this)[i] == m[i]))
              return false;

      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = (*this)[i] * val;
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != this->sz) throw invalid_argument("Matrix columns and vector size must be equal for multiplication!");
      TDynamicVector<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          for (size_t j = 0; j < this->sz; ++j)
              result[i] += (*this)[i][j] * v[j];
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.sz != this->sz) throw invalid_argument("Matrices must be of the same size for addition");
      TDynamicMatrix<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = (*this)[i] + m[i];
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.sz != this->sz) throw invalid_argument("Matrices must be of the same size for subtraction");
      TDynamicMatrix<T> result(this->sz);
      for (size_t i = 0; i < this->sz; ++i)
          result[i] = (*this)[i] - m[i];
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (m.sz != this->sz) throw invalid_argument("Matrix dimensions must match for multiplication!");
      TDynamicMatrix<T> result(this->sz); 
          for (size_t j = 0; j < m.sz; ++j)
              for (size_t k = 0; k < this->sz; ++k)
                  result[i][j] += (*this)[i][k] * m[k][j]; 
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v[i] << "\n";
      return ostr;
  }
};

#endif
