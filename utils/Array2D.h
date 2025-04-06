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

        /* Sets the class attributes and allocates space for the data buffer. */

        m_cols = cols;
        m_rows = rows;

        if(m_dataPointer) {
            free(m_dataPointer);
        }

        m_dataPointer = (T*)malloc(cols * rows * sizeof(T));

    }

    void InitArray2D(int Cols, int Rows, void* pData) {

        /* Sets the class attributes. */

        m_cols = Cols;
        m_rows = Rows;

        if (m_dataPointer) {
            free(m_dataPointer);
        }

        m_dataPointer = (T*)pData;

    }

    void InitArray2D(int Cols, int Rows, T InitVal) {

        /* Sets the class attributes and allocates space for the data buffer.
         * Initializes the data buffer with the 'InitVal'. */

        InitArray2D(Cols, Rows);

        for (int i = 0 ; i < Cols * Rows ; i++) {
            m_dataPointer[i] = InitVal;
        }

    }

    void PrintFloat() {

        /* Prints out the float values of the data buffer. */

        for (int y = 0 ; y < m_rows ; y++) {
            printf("%d: ", y);
            for (int x = 0 ; x < m_cols ; x++) {
                float f = (float)m_dataPointer[y * m_cols + x];
                printf("%.6f ", f);
            }
            printf("\n");
        }
    }

    void GetMinMax(T& Min, T& Max) {
        /* Stores the minimum and maximum values in the 'Min' and 'Max' respectively. */
        Max = Min = m_dataPointer[0];

        for (int i = 1 ; i < m_rows * m_cols ; i++) {
            if (m_dataPointer[i] < Min) {
                Min = m_dataPointer[i];
            }

            if (m_dataPointer[i] > Max) {
                Max = m_dataPointer[i];
            }
        }
    }


    void Normalize(T MinHeight, T MaxHeight){
        /* Height interpolation. */
        T Min, Max;

        GetMinMax(Min, Max);

        if (Max <= Min) {
            return;
        }

        T MinMaxDelta = Max - Min;
        T MinMaxRange = MaxHeight - MinHeight;

        for (int i = 0 ; i < m_rows * m_cols; i++) {
            m_dataPointer[i] = ((m_dataPointer[i] - Min)/MinMaxDelta) * MinMaxRange + MinHeight;
        }
    }

    T* GetAddr(int col, int row) const {
        /* Returns the pointer to the memory location in the buffer beginning from col, row.*/
        size_t ind = row * m_cols + col;
        return &m_dataPointer[ind];
    }

    const T& Get(int col, int row) const {
        /* Returns the contents of the memory location in the buffer beginning at col, row.*/
        return *GetAddr(col, row);
    }

    void Set(int Col, int Row, const T& Val) {
        /* Writes 'Val' at the col, row memory location in the buffer. */
        *GetAddr(Col, Row) = Val;
    }

private:

    T* m_dataPointer = nullptr;
    unsigned int m_cols = 0;
    unsigned int m_rows = 0;

};

#endif //ARRAY2D_H
