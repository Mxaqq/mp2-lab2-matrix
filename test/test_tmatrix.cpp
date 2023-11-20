#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    TDynamicMatrix<int> m(5);

    EXPECT_EQ(m.GetRows(), 5); 
    EXPECT_EQ(m.GetCols(), 5);
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    EXPECT_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1), std::invalid_argument);
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    EXPECT_THROW(TDynamicMatrix<int> m(-5), std::invalid_argument);
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(m);

    EXPECT_EQ(m1.GetRows(), 5);
    EXPECT_EQ(m1.GetCols(), 5);

   
    for (int i = 0; i < m.GetRows(); i++)
        for (int j = 0; j < m.GetCols(); j++)
            EXPECT_EQ(m(i, j), m1(i, j));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(5);
    for (int i = 0; i < m.GetSize(); ++i) {
        for (int j = 0; j < m.GetSize(); ++j) {
            m[i][j] = i * j; // or any other initialization logic
        }
    }

    TDynamicMatrix<int> m1 = m;

    EXPECT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1 = m;

    m1[0][0] = 10;

    EXPECT_NE(m1[0][0], m[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5);

    EXPECT_EQ(m.GetSize(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5);

    m[0][0] = 10;

    EXPECT_EQ(m[0][0], 10);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_THROW(m(-1, 1), std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(10);
    ASSERT_THROW(m(11, 1), std::out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(10);

    ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(10), m2(10);

    ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(10), m2(20);

    m1 = m2;

    EXPECT_EQ(m1.GetSize(), m2.GetSize());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(10), m2(20);

    ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(10), m2(10);

    
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(10);

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(10), m2(20);

    EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(10), m2(10), m3(10);

    ASSERT_NO_THROW(m3 = m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(10), m2(20);

    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(10), m2(10), m3(10);

    ASSERT_NO_THROW(m3 = m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(10), m2(20);

    ASSERT_ANY_THROW(m1 - m2);
}

