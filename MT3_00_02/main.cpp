#include "Novice.h"

struct Matrix4x4 {
    float m[4][4];
};

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
        }
    }
    return result;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m1.m[i][j] - m2.m[i][j];
        }
    }
    return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result = {};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }

    return result;
}



Matrix4x4 Transpose(const Matrix4x4& m) {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m.m[j][i];
        }
    }
    return result;
}

Matrix4x4 MakeIdentity4x4() {
    Matrix4x4 result = {};
    for (int i = 0; i < 4; i++) {
        result.m[i][i] = 1.0f;
    }
    return result;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
    //代入
    float m00 = m.m[0][0], m01 = m.m[0][1], m02 = m.m[0][2], m03 = m.m[0][3];
    float m10 = m.m[1][0], m11 = m.m[1][1], m12 = m.m[1][2], m13 = m.m[1][3];
    float m20 = m.m[2][0], m21 = m.m[2][1], m22 = m.m[2][2], m23 = m.m[2][3];
    float m30 = m.m[3][0], m31 = m.m[3][1], m32 = m.m[3][2], m33 = m.m[3][3];

    float det = m00 * (m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31)) -
        m01 * (m10 * (m22 * m33 - m23 * m32) - m12 * (m20 * m33 - m23 * m30) + m13 * (m20 * m32 - m22 * m30)) +
        m02 * (m10 * (m21 * m33 - m23 * m31) - m11 * (m20 * m33 - m23 * m30) + m13 * (m20 * m31 - m21 * m30)) -
        m03 * (m10 * (m21 * m32 - m22 * m31) - m11 * (m20 * m32 - m22 * m30) + m12 * (m20 * m31 - m21 * m30));


    float invDet = 1.0f / det;

    Matrix4x4 result;
    result.m[0][0] = (m11 * (m22 * m33 - m23 * m32) - m12 * (m21 * m33 - m23 * m31) + m13 * (m21 * m32 - m22 * m31)) * invDet;
    result.m[0][1] = -(m01 * (m22 * m33 - m23 * m32) - m02 * (m21 * m33 - m23 * m31) + m03 * (m21 * m32 - m22 * m31)) * invDet;
    result.m[0][2] = (m01 * (m12 * m33 - m13 * m32) - m02 * (m11 * m33 - m13 * m31) + m03 * (m11 * m32 - m12 * m31)) * invDet;
    result.m[0][3] = -(m01 * (m12 * m23 - m13 * m22) - m02 * (m11 * m23 - m13 * m21) + m03 * (m11 * m22 - m12 * m21)) * invDet;

    result.m[1][0] = -(m10 * (m22 * m33 - m23 * m32) - m12 * (m20 * m33 - m23 * m30) + m13 * (m20 * m32 - m22 * m30)) * invDet;
    result.m[1][1] = (m00 * (m22 * m33 - m23 * m32) - m02 * (m20 * m33 - m23 * m30) + m03 * (m20 * m32 - m22 * m30)) * invDet;
    result.m[1][2] = -(m00 * (m12 * m33 - m13 * m32) - m02 * (m10 * m33 - m13 * m30) + m03 * (m10 * m32 - m12 * m30)) * invDet;
    result.m[1][3] = (m00 * (m12 * m23 - m13 * m22) - m02 * (m10 * m23 - m13 * m20) + m03 * (m10 * m22 - m12 * m20)) * invDet;

    result.m[2][0] = (m10 * (m21 * m33 - m23 * m31) - m11 * (m20 * m33 - m23 * m30) + m13 * (m20 * m31 - m21 * m30)) * invDet;
    result.m[2][1] = -(m00 * (m21 * m33 - m23 * m31) - m01 * (m20 * m33 - m23 * m30) + m03 * (m20 * m31 - m21 * m30)) * invDet;
    result.m[2][2] = (m00 * (m11 * m33 - m13 * m31) - m01 * (m10 * m33 - m13 * m30) + m03 * (m10 * m31 - m11 * m30)) * invDet;
    result.m[2][3] = -(m00 * (m11 * m23 - m13 * m21) - m01 * (m10 * m23 - m13 * m20) + m03 * (m10 * m21 - m11 * m20)) * invDet;

    result.m[3][0] = -(m10 * (m21 * m32 - m22 * m31) - m11 * (m20 * m32 - m22 * m30) + m12 * (m20 * m31 - m21 * m30)) * invDet;
    result.m[3][1] = (m00 * (m21 * m32 - m22 * m31) - m01 * (m20 * m32 - m22 * m30) + m02 * (m20 * m31 - m21 * m30)) * invDet;
    result.m[3][2] = -(m00 * (m11 * m32 - m12 * m31) - m01 * (m10 * m32 - m12 * m30) + m02 * (m10 * m31 - m11 * m30)) * invDet;
    result.m[3][3] = (m00 * (m11 * m22 - m12 * m21) - m01 * (m10 * m22 - m12 * m20) + m02 * (m10 * m21 - m11 * m20)) * invDet;

    return result;
}



const int kColumnWidth = 60;
const int kRowHeight = 20;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    Novice::ScreenPrintf(x, y, label);
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 4; column++) {
            Novice::ScreenPrintf(x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]);
        }
    }
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ライブラリの初期化
    Novice::Initialize("Matrix4x4 Operations", 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Matrix4x4 m1 = {
        3.2f, 0.7f, 9.6f, 4.4f,
        5.5f, 1.3f, 7.8f, 2.1f,
        6.9f, 8.0f, 2.6f, 1.0f,
        0.5f, 7.2f, 5.1f, 3.3f
    };

    Matrix4x4 m2 = {
        4.1f, 6.5f, 3.3f, 2.2f,
        8.8f, 0.6f, 9.9f, 7.7f,
        1.1f, 5.5f, 6.6f, 0.0f,
        3.3f, 9.9f, 8.8f, 2.2f
    };

    Matrix4x4 resultAdd = Add(m1, m2);
    Matrix4x4 resultSubtract = Subtract(m1, m2);
    Matrix4x4 resultMultiply = Multiply(m1, m2);
    Matrix4x4 inverseM1 = Inverse(m1);
    Matrix4x4 inverseM2 = Inverse(m2);
    Matrix4x4 transposeM1 = Transpose(m1);
    Matrix4x4 transposeM2 = Transpose(m2);
    Matrix4x4 identity = MakeIdentity4x4();

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // 描画処理
        MatrixScreenPrintf(0, 0, resultAdd, "Add");
        MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
        MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
        MatrixScreenPrintf(0, kRowHeight * 5 * 3, inverseM1, "Inverse M1");
        MatrixScreenPrintf(0, kRowHeight * 5 * 4, inverseM2, "Inverse M2");
        MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "Transpose M1");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight *5, transposeM2, "Transpose M2");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight *5* 2, identity, "Identity");

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
