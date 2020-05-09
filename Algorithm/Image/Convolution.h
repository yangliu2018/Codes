#pragma once

template <size_t M, size_t N, class T>
void Convolution(T x[M], T y[N], T z[M + N - 1]) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            z[i + j] 
        }
    }
}

template <size_t M1, size_t N1, size_t M2, size_t N2, class T>
void Convolution(T x[M1][N1], T y[M2][N2], T z[M1 + M2 - 1][N1 + N2 - 1]) {
    for (size_t row = 0; row < M1 + M2 - 1; ++row) {
        for (size_t col = 0; col < M1 + M2 - 1; ++col) {

        }
    }
}