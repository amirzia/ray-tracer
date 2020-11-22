
#include <vector>
using namespace std;

class Vec3f {
    public:
        Vec3f(float);
        Vec3f(float, float, float);
        
        void print();
        Vec3f add(const Vec3f);
        Vec3f operator *(const float);

        float x_, y_, z_;
};

class Vec4f {
    public:
        Vec4f(float);
        Vec4f(float, float, float, float);
        
        void print();
        Vec4f operator +(const Vec4f);
        Vec4f operator *(const float);
        void operator =(const Vec4f);
        float get(const unsigned);

        float dot(const Vec4f);

        float x_, y_, z_, w_;
};

class Mat4f {
    public:
        Mat4f();
        Mat4f(float);
        
        void print();
        Mat4f operator +(const Mat4f);
        Mat4f operator *(const float);
        Mat4f operator *(const Mat4f);
        Vec4f operator *(const Vec4f);
        void operator =(const Mat4f);

        Vec4f getRow(const unsigned);
        Vec4f getCol(const unsigned);
        float get(const unsigned, const unsigned);

        void setRow(const unsigned, const Vec4f);
        void setCol(const unsigned, const Vec4f);
        void set(const unsigned, const unsigned, const float);

    private:
        vector< vector<float> > mat_;
};
