// Original code copyright (C) 2022 Etay Meiri
// Modified by Filip Radovic in 2024
// Licensed under the GNU General Public License v3
// See LICENSE file in the project root for details.

#ifndef ARRAY2D_H
#define ARRAY2D_H
#include <cstdio>
#include <stdlib.h>

template <typename T>
class Array2D {
public:
    Array2D(){}

    Array2D(int cols, int rows) {
        InitArray2D(cols, rows);
    }

    void InitArray2D(int cols, int rows) {
        m_cols = cols;
        m_rows = rows;

        if(m_p) {
            free(m_p);
        }

        m_p = (T*)malloc(cols * rows * sizeof(T));
    }

    void InitArray2D(int Cols, int Rows, void* pData)
    {
        m_cols = Cols;
        m_rows = Rows;

        if (m_p) {
            free(m_p);
        }

        m_p = (T*)pData;
    }

    void InitArray2D(int Cols, int Rows, T InitVal)
    {
        InitArray2D(Cols, Rows);

        for (int i = 0 ; i < Cols * Rows ; i++) {
            m_p[i] = InitVal;
        }
    }

    void PrintFloat()
    {
        for (int y = 0 ; y < m_rows ; y++) {
            printf("%d: ", y);
            for (int x = 0 ; x < m_cols ; x++) {
                float f = (float)m_p[y * m_cols + x];
                printf("%.6f ", f);
            }
            printf("\n");
        }
    }

    void GetMinMax(T& Min, T& Max)
    {
        Max = Min = m_p[0];

        for (int i = 1 ; i < m_rows * m_cols ; i++) {
            if (m_p[i] < Min) {
                Min = m_p[i];
            }

            if (m_p[i] > Max) {
                Max = m_p[i];
            }
        }
    }


    void Normalize(T MinHeight, T MaxHeight)
    {
        T Min, Max;

        GetMinMax(Min, Max);

        if (Max <= Min) {
            return;
        }

        T MinMaxDelta = Max - Min;
        T MinMaxRange = MaxHeight - MinHeight;

        for (int i = 0 ; i < m_rows * m_cols; i++) {
            m_p[i] = ((m_p[i] - Min)/MinMaxDelta) * MinMaxRange + MinHeight;
        }
    }

    T* GetAddr(int col, int row) const {
        size_t ind = row * m_cols + col;
        return &m_p[ind];
    }

    const T& Get(int col, int row) const {
        return *GetAddr(col, row);
    }

    void Set(int Col, int Row, const T& Val)
    {
        *GetAddr(Col, Row) = Val;
    }

private:
    T* m_p = nullptr;
    unsigned int m_cols = 0;
    unsigned int m_rows = 0;};
#endif //ARRAY2D_H
