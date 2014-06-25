#ifndef _grey243_20_144_HPP_
#define _grey243_20_144_HPP_


// This is an automatically generated file from gen.py.
#include "common.hpp"


namespace grey243_20_144 {
template <typename Scalar>
void FastMatmul(Matrix<Scalar>& A, Matrix<Scalar>& B, Matrix<Scalar>& C, int numsteps, double x=1e-8) {
    // Base case for recursion
    if (numsteps == 0) {
        Gemm(A, B, C);
        return;
    }

    int A_x_step = A.m() / 2;
    int A_y_step = A.n() / 4;
    Matrix<Scalar> A11(A.data() + 0 * A_x_step + 0 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    Matrix<Scalar> A12(A.data() + 0 * A_x_step + 1 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    Matrix<Scalar> A13(A.data() + 0 * A_x_step + 2 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    Matrix<Scalar> A14(A.data() + 0 * A_x_step + 3 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    Matrix<Scalar> A21(A.data() + 1 * A_x_step + 0 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    Matrix<Scalar> A22(A.data() + 1 * A_x_step + 1 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    Matrix<Scalar> A23(A.data() + 1 * A_x_step + 2 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    Matrix<Scalar> A24(A.data() + 1 * A_x_step + 3 * A_y_step * A.stride(), A.stride(), A_x_step, A_y_step);
    int B_x_step = B.m() / 4;
    int B_y_step = B.n() / 3;
    Matrix<Scalar> B11(B.data() + 0 * B_x_step + 0 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B12(B.data() + 0 * B_x_step + 1 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B13(B.data() + 0 * B_x_step + 2 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B21(B.data() + 1 * B_x_step + 0 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B22(B.data() + 1 * B_x_step + 1 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B23(B.data() + 1 * B_x_step + 2 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B31(B.data() + 2 * B_x_step + 0 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B32(B.data() + 2 * B_x_step + 1 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B33(B.data() + 2 * B_x_step + 2 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B41(B.data() + 3 * B_x_step + 0 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B42(B.data() + 3 * B_x_step + 1 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    Matrix<Scalar> B43(B.data() + 3 * B_x_step + 2 * B_y_step * B.stride(), B.stride(), B_x_step, B_y_step);
    int C_x_step = C.m() / 2;
    int C_y_step = C.n() / 3;
    Matrix<Scalar> C11(C.data() + 0 * C_x_step + 0 * C_y_step * C.stride(), C.stride(), C_x_step, C_y_step);
    Matrix<Scalar> C12(C.data() + 0 * C_x_step + 1 * C_y_step * C.stride(), C.stride(), C_x_step, C_y_step);
    Matrix<Scalar> C13(C.data() + 0 * C_x_step + 2 * C_y_step * C.stride(), C.stride(), C_x_step, C_y_step);
    Matrix<Scalar> C21(C.data() + 1 * C_x_step + 0 * C_y_step * C.stride(), C.stride(), C_x_step, C_y_step);
    Matrix<Scalar> C22(C.data() + 1 * C_x_step + 1 * C_y_step * C.stride(), C.stride(), C_x_step, C_y_step);
    Matrix<Scalar> C23(C.data() + 1 * C_x_step + 2 * C_y_step * C.stride(), C.stride(), C_x_step, C_y_step);


    // These are the intermediate matrices.
    // We define them here so that they can be used
    // inside the lambda functions for Cilk.
    Matrix<Scalar> M1(C_x_step, C_y_step);
    Matrix<Scalar> M2(C_x_step, C_y_step);
    Matrix<Scalar> M3(C_x_step, C_y_step);
    Matrix<Scalar> M4(C_x_step, C_y_step);
    Matrix<Scalar> M5(C_x_step, C_y_step);
    Matrix<Scalar> M6(C_x_step, C_y_step);
    Matrix<Scalar> M7(C_x_step, C_y_step);
    Matrix<Scalar> M8(C_x_step, C_y_step);
    Matrix<Scalar> M9(C_x_step, C_y_step);
    Matrix<Scalar> M10(C_x_step, C_y_step);
    Matrix<Scalar> M11(C_x_step, C_y_step);
    Matrix<Scalar> M12(C_x_step, C_y_step);
    Matrix<Scalar> M13(C_x_step, C_y_step);
    Matrix<Scalar> M14(C_x_step, C_y_step);
    Matrix<Scalar> M15(C_x_step, C_y_step);
    Matrix<Scalar> M16(C_x_step, C_y_step);
    Matrix<Scalar> M17(C_x_step, C_y_step);
    Matrix<Scalar> M18(C_x_step, C_y_step);
    Matrix<Scalar> M19(C_x_step, C_y_step);
    Matrix<Scalar> M20(C_x_step, C_y_step);


#ifdef _OPEN_MP_
    #pragma omp parallel
    {
    #pragma omp single
        {
#endif
    // M1 = (-1.0 * A11 + -1.0 * A12 + -1.0 * A21 + -1.0 * A22) * (1.0 * B11)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M1A(A11.m(), A11.n());
    Add(A11, A12, A21, A22, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M1A);
    FastMatmul(M1A, B11, M1, numsteps - 1, x);
    M1A.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M2 = (-1.0 * A22 + -1.0 * A23) * (1.0 * B21 + 1.0 * B22)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M2A(A11.m(), A11.n());
    Add(A22, A23, Scalar(-1.0), Scalar(-1.0), M2A);
    Matrix<Scalar> M2B(B11.m(), B11.n());
    Add(B21, B22, Scalar(1.0), Scalar(1.0), M2B);
    FastMatmul(M2A, M2B, M2, numsteps - 1, x);
    M2A.deallocate();
    M2B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M3 = (-1.0 * A11) * (1.0 * B11 + 1.0 * B12 + 1.0 * B13)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M3A(A11.m(), A11.n());
    Add(A11, Scalar(-1.0), M3A);
    Matrix<Scalar> M3B(B11.m(), B11.n());
    Add(B11, B12, B13, Scalar(1.0), Scalar(1.0), Scalar(1.0), M3B);
    FastMatmul(M3A, M3B, M3, numsteps - 1, x);
    M3A.deallocate();
    M3B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M4 = (-1.0 * A14 + -1.0 * A21 + -1.0 * A24) * (-1.0 * B11 + -1.0 * B12 + -1.0 * B43)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M4A(A11.m(), A11.n());
    Add(A14, A21, A24, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M4A);
    Matrix<Scalar> M4B(B11.m(), B11.n());
    Add(B11, B12, B43, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M4B);
    FastMatmul(M4A, M4B, M4, numsteps - 1, x);
    M4A.deallocate();
    M4B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M5 = (1.0 * A21 + 1.0 * A24) * (-1.0 * B43)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M5A(A11.m(), A11.n());
    Add(A21, A24, Scalar(1.0), Scalar(1.0), M5A);
    Matrix<Scalar> M5B(B11.m(), B11.n());
    Add(B43, Scalar(-1.0), M5B);
    FastMatmul(M5A, M5B, M5, numsteps - 1, x);
    M5A.deallocate();
    M5B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M6 = (-1.0 * A14 + 1.0 * A23) * (1.0 * B32 + 1.0 * B33 + -1.0 * B41)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M6A(A11.m(), A11.n());
    Add(A14, A23, Scalar(-1.0), Scalar(1.0), M6A);
    Matrix<Scalar> M6B(B11.m(), B11.n());
    Add(B32, B33, B41, Scalar(1.0), Scalar(1.0), Scalar(-1.0), M6B);
    FastMatmul(M6A, M6B, M6, numsteps - 1, x);
    M6A.deallocate();
    M6B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M7 = (-1.0 * A12 + -1.0 * A22) * (1.0 * B11 + -1.0 * B21)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M7A(A11.m(), A11.n());
    Add(A12, A22, Scalar(-1.0), Scalar(-1.0), M7A);
    Matrix<Scalar> M7B(B11.m(), B11.n());
    Add(B11, B21, Scalar(1.0), Scalar(-1.0), M7B);
    FastMatmul(M7A, M7B, M7, numsteps - 1, x);
    M7A.deallocate();
    M7B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M8 = (1.0 * A12 + 1.0 * A13) * (1.0 * B33)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M8A(A11.m(), A11.n());
    Add(A12, A13, Scalar(1.0), Scalar(1.0), M8A);
    FastMatmul(M8A, B33, M8, numsteps - 1, x);
    M8A.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M9 = (-1.0 * A23) * (1.0 * B21 + 1.0 * B22 + -1.0 * B31 + 1.0 * B33 + 1.0 * B41)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M9A(A11.m(), A11.n());
    Add(A23, Scalar(-1.0), M9A);
    Matrix<Scalar> M9B(B11.m(), B11.n());
    Add(B21, B22, B31, B33, B41, Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), M9B);
    FastMatmul(M9A, M9B, M9, numsteps - 1, x);
    M9A.deallocate();
    M9B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M10 = (1.0 * A14 + 1.0 * A24) * (-1.0 * B11 + -1.0 * B12 + -1.0 * B41 + 1.0 * B42)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M10A(A11.m(), A11.n());
    Add(A14, A24, Scalar(1.0), Scalar(1.0), M10A);
    Matrix<Scalar> M10B(B11.m(), B11.n());
    Add(B11, B12, B41, B42, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), M10B);
    FastMatmul(M10A, M10B, M10, numsteps - 1, x);
    M10A.deallocate();
    M10B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M11 = (-1.0 * A14) * (-1.0 * B32 + -1.0 * B33 + 1.0 * B42 + 1.0 * B43)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M11A(A11.m(), A11.n());
    Add(A14, Scalar(-1.0), M11A);
    Matrix<Scalar> M11B(B11.m(), B11.n());
    Add(B32, B33, B42, B43, Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), M11B);
    FastMatmul(M11A, M11B, M11, numsteps - 1, x);
    M11A.deallocate();
    M11B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M12 = (1.0 * A12 + -1.0 * A23) * (-1.0 * B21 + -1.0 * B22 + -1.0 * B33)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M12A(A11.m(), A11.n());
    Add(A12, A23, Scalar(1.0), Scalar(-1.0), M12A);
    Matrix<Scalar> M12B(B11.m(), B11.n());
    Add(B21, B22, B33, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M12B);
    FastMatmul(M12A, M12B, M12, numsteps - 1, x);
    M12A.deallocate();
    M12B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M13 = (1.0 * A23 + 1.0 * A24) * (1.0 * B41)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M13A(A11.m(), A11.n());
    Add(A23, A24, Scalar(1.0), Scalar(1.0), M13A);
    FastMatmul(M13A, B41, M13, numsteps - 1, x);
    M13A.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M14 = (1.0 * A13 + 1.0 * A23) * (-1.0 * B31 + 1.0 * B32 + 1.0 * B33)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M14A(A11.m(), A11.n());
    Add(A13, A23, Scalar(1.0), Scalar(1.0), M14A);
    Matrix<Scalar> M14B(B11.m(), B11.n());
    Add(B31, B32, B33, Scalar(-1.0), Scalar(1.0), Scalar(1.0), M14B);
    FastMatmul(M14A, M14B, M14, numsteps - 1, x);
    M14A.deallocate();
    M14B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M15 = (1.0 * A21) * (-1.0 * B11 + 1.0 * B13 + -1.0 * B22 + -1.0 * B23 + -1.0 * B43)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M15B(B11.m(), B11.n());
    Add(B11, B13, B22, B23, B43, Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M15B);
    FastMatmul(A21, M15B, M15, numsteps - 1, x);
    M15B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M16 = (-1.0 * A13 + -1.0 * A14) * (1.0 * B32 + 1.0 * B33)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M16A(A11.m(), A11.n());
    Add(A13, A14, Scalar(-1.0), Scalar(-1.0), M16A);
    Matrix<Scalar> M16B(B11.m(), B11.n());
    Add(B32, B33, Scalar(1.0), Scalar(1.0), M16B);
    FastMatmul(M16A, M16B, M16, numsteps - 1, x);
    M16A.deallocate();
    M16B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M17 = (1.0 * A12) * (-1.0 * B23 + 1.0 * B33)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M17B(B11.m(), B11.n());
    Add(B23, B33, Scalar(-1.0), Scalar(1.0), M17B);
    FastMatmul(A12, M17B, M17, numsteps - 1, x);
    M17B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M18 = (1.0 * A12 + 1.0 * A21 + 1.0 * A22) * (-1.0 * B11 + -1.0 * B22 + -1.0 * B23)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M18A(A11.m(), A11.n());
    Add(A12, A21, A22, Scalar(1.0), Scalar(1.0), Scalar(1.0), M18A);
    Matrix<Scalar> M18B(B11.m(), B11.n());
    Add(B11, B22, B23, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M18B);
    FastMatmul(M18A, M18B, M18, numsteps - 1, x);
    M18A.deallocate();
    M18B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M19 = (-1.0 * A11 + -1.0 * A14 + -1.0 * A21 + -1.0 * A24) * (1.0 * B11 + 1.0 * B12)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M19A(A11.m(), A11.n());
    Add(A11, A14, A21, A24, Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), M19A);
    Matrix<Scalar> M19B(B11.m(), B11.n());
    Add(B11, B12, Scalar(1.0), Scalar(1.0), M19B);
    FastMatmul(M19A, M19B, M19, numsteps - 1, x);
    M19A.deallocate();
    M19B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

    // M20 = (-1.0 * A21 + -1.0 * A22) * (1.0 * B22 + 1.0 * B23)
#ifdef _CILK_
    cilk_spawn [&] {
#elif defined _OPEN_MP_
# pragma omp task
    {
#endif
    Matrix<Scalar> M20A(A11.m(), A11.n());
    Add(A21, A22, Scalar(-1.0), Scalar(-1.0), M20A);
    Matrix<Scalar> M20B(B11.m(), B11.n());
    Add(B22, B23, Scalar(1.0), Scalar(1.0), M20B);
    FastMatmul(M20A, M20B, M20, numsteps - 1, x);
    M20A.deallocate();
    M20B.deallocate();
#ifdef _CILK_
    }();
#elif defined _OPEN_MP_
    }
#endif

#ifdef _CILK_
    cilk_sync;
#elif defined _OPEN_MP_
        }  // End omp single region
    }  // End omp parallel region
#endif
    Add(M1, M6, M9, M12, M14, M16, M17, M18, M20, Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(-1.0), C11);
    Add(M1, M4, M5, M8, M11, M16, M17, M18, M19, M20, Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(-1.0), Scalar(1.0), C12);
    Add(M3, M4, M5, M8, M17, M19, Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), C13);
    Add(M7, M9, M12, M13, M17, M18, M20, Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), C21);
    Add(M2, M4, M5, M6, M7, M10, M11, M12, M13, M17, M18, M20, Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), Scalar(-1.0), Scalar(1.0), Scalar(-1.0), C22);
    Add(M2, M5, M7, M12, M15, M17, M18, Scalar(1.0), Scalar(-1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(1.0), Scalar(-1.0), C23);
}

}

#endif  // _grey243_20_144_HPP_