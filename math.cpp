
#include <iostream>
#include "math.hpp"

using namespace std;

Vec3f::Vec3f(float f) {
    x_ = f;
    y_ = f;
    z_ = f;
}

Vec3f::Vec3f(float x, float y, float z) {
    x_ = x;
    y_ = y;
    z_ = z;
}

void Vec3f::print() {
    cout << x_ << " " << y_ << " " << z_ << endl;
}

Vec3f Vec3f::add(const Vec3f vec) {
    return Vec3f(vec.x_ + x_, vec.y_ + y_, vec.z_ + z_);
}

Vec3f Vec3f::operator *(const float val) {
    return Vec3f(x_ * val, y_ * val, z_ * val);
}

Vec4f::Vec4f(float f) {
    x_ = f;
    y_ = f;
    z_ = f;
    w_ = f;
}

Vec4f::Vec4f(float x, float y, float z, float w) {
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

void Vec4f::print() {
    cout << x_ << " " << y_ << " " << z_ << " " << w_ << endl;
}

Vec4f Vec4f::operator +(const Vec4f vec) {
    return Vec4f(vec.x_ + x_, vec.y_ + y_, vec.z_ + z_, vec.w_ + w_);
}

Vec4f Vec4f::operator *(const float f) {
    return Vec4f(x_ * f, y_ * f, z_ * f, w_ * f);
}

void Vec4f::operator =(const Vec4f vec) {
    x_ = vec.x_;
    y_ = vec.y_;
    z_ = vec.z_;
    w_ = vec.w_;
}

float Vec4f::dot(const Vec4f vec) {
    return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_ + w_ * vec.w_;
}

float Vec4f::get(const unsigned i) {
    switch(i) {
        case 0: return x_;
        case 1: return y_;
        case 2: return z_;
        case 3: return w_;
        default:
                return -1;
    }
}

Mat4f::Mat4f() {
    for (unsigned i = 0; i < 4; i++) {
        vector <float> row(4, 0);
        row[i] = 1.0;
        mat_.push_back(row);
    }
}

Mat4f::Mat4f(float x) {
    for (unsigned i = 0; i < 4; i++)
        mat_.push_back(vector<float> (4, x));
}

void Mat4f::print() {
    for (unsigned i = 0; i < 4; i++) {
        for (unsigned j = 0; j < 4; j++)
            cout << mat_[i][j] << "\t";
        cout << endl;
    }
}

Mat4f Mat4f::operator +(Mat4f mat) {
    Mat4f newMat;
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            newMat.set(i, j, get(i, j) + mat.get(i, j));
    return newMat;
}

Mat4f Mat4f:: operator *(const float val) {
    Mat4f newMat;
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            newMat.set(i, j, get(i, j) * val);
    return newMat;
}

Vec4f Mat4f::operator *(const Vec4f vec) {
    return Vec4f(getRow(0).dot(vec), getRow(1).dot(vec), getRow(2).dot(vec), getRow(3).dot(vec));
}

Mat4f Mat4f::operator *(Mat4f mat) {
    Mat4f newMat = Mat4f() * 0.0;
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            for (unsigned k = 0; k < 4; k++)
                newMat.set(i, j, newMat.get(i, j) + get(i, k) * mat.get(k, j));
    return newMat;
}

void Mat4f::operator =(Mat4f mat) {
    for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
            mat_[i][j] = mat.get(i, j);
}

Vec4f Mat4f::getRow(const unsigned i) {
    return Vec4f(mat_[i][0], mat_[i][1], mat_[i][2], mat_[i][3]);
}

Vec4f Mat4f::getCol(const unsigned j) {
    return Vec4f(mat_[0][j], mat_[1][j], mat_[2][j], mat_[3][j]);
}

float Mat4f::get(const unsigned i, const unsigned j) {
    return mat_[i][j];
}

void Mat4f::setRow(const unsigned i, Vec4f vec) {
    for (unsigned c = 0; c < 4; c++)
        set(i, c, vec.get(c));
}

void Mat4f::setCol(const unsigned j, Vec4f vec) {
    for (unsigned c = 0; c < 4; c++)
        set(c, j, vec.get(c));
}

void Mat4f::set(const unsigned i, const unsigned j, const float val) {
    mat_[i][j] = val;
}

