#pragma once
#include <utils/Types.h>

#include <xtr1common>
#include <cmath>

#undef near
#undef far
#undef min
#undef max

namespace utils {
    template <typename T> T radians(T degrees) { return degrees * T(0.0174533); }
    template <typename T> T degrees(T radians) { return radians * T(57.2958); }
    template <typename T> T min(const T& a, const T& b) { return a < b ? a : b; }
    template <typename T> T max(const T& a, const T& b) { return a > b ? a : b; }
    template <typename T> T clamp(const T& a, const T& minVal, const T& maxVal) { return max(min(a, maxVal), minVal); }
    template <typename T> T lerp(const T& a, const T& b, f32 t) { return a + ((b - a) * t); }

    #pragma pack(push, 1)

    template <typename T> class mat2;
    template <typename T> class mat3;
    template <typename T> class mat4;

    template <typename T>
    class vec2 {
        public:
            static_assert(
                std::is_integral_v<std::remove_reference_t<T>> || std::is_floating_point_v<std::remove_reference_t<T>>,
                "vec2 expects template T to be integral or floating point type"
            );

            vec2() requires !std::is_reference_v<T> : x(T(0)), y(T(0)) {}
            vec2(T _x, T _y) : x(_x), y(_y) {}

            template <typename R>
            vec2(const vec2<R>& rhs) : x(rhs.x), y(rhs.y) {}

            template <typename R> vec2<T> operator+(const vec2<R>& rhs) const { return vec2<T>(x + rhs.x, y + rhs.y); }
            template <typename R> vec2<T> operator-(const vec2<R>& rhs) const { return vec2<T>(x - rhs.x, y - rhs.y); }
            template <typename R> vec2<T> operator/(const vec2<R>& rhs) const { return vec2<T>(x / rhs.x, y / rhs.y); }
            template <typename R> vec2<T> operator*(const vec2<R>& rhs) const { return vec2<T>(x * rhs.x, y * rhs.y); }
            template <typename R> vec2<T>& operator+=(const vec2<R>& rhs) { return x += rhs.x; y += rhs.y; return *this; }
            template <typename R> vec2<T>& operator-=(const vec2<R>& rhs) { return x -= rhs.x; y -= rhs.y; return *this; }
            template <typename R> vec2<T>& operator/=(const vec2<R>& rhs) { return x /= rhs.x; y /= rhs.y; return *this; }
            template <typename R> vec2<T>& operator*=(const vec2<R>& rhs) { return x *= rhs.x; y *= rhs.y; return *this; }
            vec2<T> operator+(T rhs) const { return vec2<T>(x + rhs, y + rhs); }
            vec2<T> operator-(T rhs) const { return vec2<T>(x - rhs, y - rhs); }
            vec2<T> operator/(T rhs) const { return vec2<T>(x / rhs, y / rhs); }
            vec2<T> operator*(T rhs) const { return vec2<T>(x * rhs, y * rhs); }
            vec2<T>& operator+=(T rhs) { x += rhs; y += rhs; return *this; }
            vec2<T>& operator-=(T rhs) { x -= rhs; y -= rhs; return *this; }
            vec2<T>& operator/=(T rhs) { x /= rhs; y /= rhs; return *this; }
            vec2<T>& operator*=(T rhs) { x *= rhs; y *= rhs; return *this; }
            vec2<T> operator-() const { return vec2<T>(-x, -y); }
            T operator[](u8 axis) const { return (&x)[axis]; }
            T& operator[](u8 axis) { return (&x)[axis]; }

            T magnitudeSq() const { return x * x + y * y; }
            T magnitude() const { return std::sqrt(x * x + y * y); }
            vec2<T> normalized() const { return *this * (T(1) / std::sqrt(x * x + y * y)); }
            void normalize() { T im = (T(1) / std::sqrt(x * x + y * y)); x *= im; y *= im; }
            template <typename R> T dot(const vec2<R>& rhs) { return x * rhs.x + y * rhs.y; }

            T x, y;
    };

    template <typename T>
    class vec3 {
        public:
            static_assert(
                std::is_integral_v<std::remove_reference_t<T>> || std::is_floating_point_v<std::remove_reference_t<T>>,
                "vec3 expects template T to be integral or floating point type"
            );

            vec3() requires !std::is_reference_v<T> : x(T(0)), y(T(0)), z(T(0)) {}
            vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

            template <typename R>
            vec3(const vec3<R>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

            template <typename R> vec3<T> operator+(const vec3<R>& rhs) const { return vec3<T>(x + rhs.x, y + rhs.y, z + rhs.z); }
            template <typename R> vec3<T> operator-(const vec3<R>& rhs) const { return vec3<T>(x - rhs.x, y - rhs.y, z - rhs.z); }
            template <typename R> vec3<T> operator/(const vec3<R>& rhs) const { return vec3<T>(x / rhs.x, y / rhs.y, z / rhs.z); }
            template <typename R> vec3<T> operator*(const vec3<R>& rhs) const { return vec3<T>(x * rhs.x, y * rhs.y, z * rhs.z); }
            template <typename R> vec3<T>& operator+=(const vec3<R>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
            template <typename R> vec3<T>& operator-=(const vec3<R>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
            template <typename R> vec3<T>& operator/=(const vec3<R>& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }
            template <typename R> vec3<T>& operator*=(const vec3<R>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
            vec3<T> operator+(T rhs) const { return vec3<T>(x + rhs, y + rhs, z + rhs); }
            vec3<T> operator-(T rhs) const { return vec3<T>(x - rhs, y - rhs, z - rhs); }
            vec3<T> operator/(T rhs) const { return vec3<T>(x / rhs, y / rhs, z / rhs); }
            vec3<T> operator*(T rhs) const { return vec3<T>(x * rhs, y * rhs, z * rhs); }
            vec3<T>& operator+=(T rhs) { x += rhs; y += rhs; z += rhs; return *this; }
            vec3<T>& operator-=(T rhs) { x -= rhs; y -= rhs; z -= rhs; return *this; }
            vec3<T>& operator/=(T rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }
            vec3<T>& operator*=(T rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
            vec3<T> operator-() const { return vec3<T>(-x, -y, -z); }
            T operator[](u8 axis) const { return (&x)[axis]; }
            T& operator[](u8 axis) { return (&x)[axis]; }

            T magnitudeSq() const { return x * x + y * y + z * z; }
            T magnitude() const { return std::sqrt(x * x + y * y + z * z); }
            vec3<T> normalized() const { return *this * (T(1) / std::sqrt(x * x + y * y + z * z)); }
            void normalize() { T im = (T(1) / std::sqrt(x * x + y * y + z * z)); x *= im; y *= im; z *= im; }
            template <typename R> T dot(const vec3<R>& rhs) { return x * rhs.x + y * rhs.y + z * rhs.z; }
            template <typename R> vec3<T> cross(const vec3<R>& rhs) const {
                return vec3<T>(
                    y * rhs.z - z * rhs.y,
                    z * rhs.x - x * rhs.z,
                    x * rhs.y - y * rhs.x
                );
            }

            vec2<T&> xy()       { return vec2<T&>(x, y); }
            vec2<T>  xy() const { return vec2<T >(x, y); }
            vec2<T&> xz()       { return vec2<T&>(x, z); }
            vec2<T>  xz() const { return vec2<T >(x, z); }
            vec2<T&> yx()       { return vec2<T&>(y, x); }
            vec2<T>  yx() const { return vec2<T >(y, x); }
            vec2<T&> yz()       { return vec2<T&>(y, z); }
            vec2<T>  yz() const { return vec2<T >(y, z); }
            vec2<T&> zx()       { return vec2<T&>(z, x); }
            vec2<T>  zx() const { return vec2<T >(z, x); }
            vec2<T&> zy()       { return vec2<T&>(z, y); }
            vec2<T>  zy() const { return vec2<T >(z, y); }

            T x, y, z;
    };

    template <typename T>
    class vec4 {
        public:
            static_assert(
                std::is_integral_v<std::remove_reference_t<T>> || std::is_floating_point_v<std::remove_reference_t<T>>,
                "vec4 expects template T to be integral or floating point type"
            );

            vec4() requires !std::is_reference_v<T> : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
            vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

            template <typename R>
            vec4(const vec3<R>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(T(0)) {}

            template <typename R>
            vec4(const vec4<R>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}

            template <typename R> vec4<T> operator+(const vec4<R>& rhs) const { return vec4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
            template <typename R> vec4<T> operator-(const vec4<R>& rhs) const { return vec4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
            template <typename R> vec4<T> operator/(const vec4<R>& rhs) const { return vec4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w); }
            template <typename R> vec4<T> operator*(const vec4<R>& rhs) const { return vec4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
            template <typename R> vec4<T> operator+(const vec3<R>& rhs) const { return vec4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w); }
            template <typename R> vec4<T> operator-(const vec3<R>& rhs) const { return vec4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w); }
            template <typename R> vec4<T> operator/(const vec3<R>& rhs) const { return vec4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w); }
            template <typename R> vec4<T> operator*(const vec3<R>& rhs) const { return vec4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w); }
            template <typename R> vec4<T> operator+=(const vec4<R>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }
            template <typename R> vec4<T> operator-=(const vec4<R>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }
            template <typename R> vec4<T> operator/=(const vec4<R>& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; w /= rhs.w; return *this; }
            template <typename R> vec4<T> operator*=(const vec4<R>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this; }
            template <typename R> vec4<T> operator+=(const vec3<R>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
            template <typename R> vec4<T> operator-=(const vec3<R>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
            template <typename R> vec4<T> operator/=(const vec3<R>& rhs) { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }
            template <typename R> vec4<T> operator*=(const vec3<R>& rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
            vec4<T> operator+(T rhs) const { return vec4<T>(x + rhs, y + rhs, z + rhs, w + rhs); }
            vec4<T> operator-(T rhs) const { return vec4<T>(x - rhs, y - rhs, z - rhs, w - rhs); }
            vec4<T> operator/(T rhs) const { return vec4<T>(x / rhs, y / rhs, z / rhs, w / rhs); }
            vec4<T> operator*(T rhs) const { return vec4<T>(x * rhs, y * rhs, z * rhs, w * rhs); }
            vec4<T> operator+=(T rhs) { x += rhs; y += rhs; z += rhs; w += rhs; return *this; }
            vec4<T> operator-=(T rhs) { x -= rhs; y -= rhs; z -= rhs; w -= rhs; return *this; }
            vec4<T> operator/=(T rhs) { x /= rhs; y /= rhs; z /= rhs; w /= rhs; return *this; }
            vec4<T> operator*=(T rhs) { x *= rhs; y *= rhs; z *= rhs; w *= rhs; return *this; }
            vec4<T> operator-() const { return vec4<T>(-x, -y, -z, -w); }
            T operator[](u8 axis) const { return (&x)[axis]; }
            T& operator[](u8 axis) { return (&x)[axis]; }
            operator vec3<T&>() { return vec3<T&>(x, y, z); }
            operator vec3<T>() const { return vec3<T>(x, y, z); }

            T magnitudeSq() const { return x * x + y * y + z * z + w * w; }
            T magnitude() const { return std::sqrt(x * x + y * y + z * z + w * w); }
            vec4<T> normalized() const { return *this * (T(1) / std::sqrt(x * x + y * y + z * z + w * w)); }
            void normalize() { T im = (T(1) / std::sqrt(x * x + y * y + z * z)); x *= im; y *= im; z *= im; w *= im; }
            template <typename R> T dot(const vec4<R>& rhs) { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }

            vec2<T&> xy()       { return vec2<T&>(x, y); }
            vec2<T>  xy() const { return vec2<T >(x, y); }
            vec2<T&> xz()       { return vec2<T&>(x, z); }
            vec2<T>  xz() const { return vec2<T >(x, z); }
            vec2<T&> yx()       { return vec2<T&>(y, x); }
            vec2<T>  yx() const { return vec2<T >(y, x); }
            vec2<T&> yz()       { return vec2<T&>(y, z); }
            vec2<T>  yz() const { return vec2<T >(y, z); }
            vec2<T&> zx()       { return vec2<T&>(z, x); }
            vec2<T>  zx() const { return vec2<T >(z, x); }
            vec2<T&> zy()       { return vec2<T&>(z, y); }
            vec2<T>  zy() const { return vec2<T >(z, y); }
            vec3<T&> xyz()       { return vec3<T&>(x, y, z); }
            vec3<T>  xyz() const { return vec3<T >(x, y, z); }

            T x, y, z, w;
    };

    template <typename T>
    class quat {
        public:
            static_assert(std::is_floating_point_v<T>, "quat expects template T to be floating point type");
            quat() : angle(T(0)) {}
            quat(T ax, T ay, T az, T _angle) : axis(ax, ay, az), angle(_angle) {}

            template <typename R>
            quat<T> operator*(const quat<R>& rhs) const {
                return quat<T>(
                    (angle * rhs.axis.x + rhs.angle * axis.x + axis.y * rhs.axis.z) - axis.z * rhs.axis.y,
                    (angle * rhs.axis.y + rhs.angle * axis.y + axis.z * rhs.axis.x) - axis.x * rhs.axis.z,
                    (angle * rhs.axis.z + rhs.angle * axis.z + axis.x * rhs.axis.y) - axis.y * rhs.axis.x,
                    ((angle * rhs.angle - axis.x * rhs.axis.x) - axis.y * rhs.axis.y) - axis.z * rhs.axis.z
                );
            }
            template <typename R> quat<T>& operator*=(const quat<R>& rhs) { return *this = *this * rhs; }
            template <typename R> T dot(const quat<R>& rhs) const { return axis.dot(rhs.axis) + angle * rhs.angle; }
            template <typename R> vec3<T> operator*(const vec3<R>& rhs) {
                vec3<T> result = axis * (axis.dot(rhs) * T(2.0));
                result += rhs * (((angle * angle) * T(2.0)) - T(1.0));
                result += axis.cross(rhs) * (angle * T(2.0));
                
                return result;
            }

            static quat<T> FromAxisAngle(const vec3<T>& axis, T angle) {
                T ha = angle * T(0.5);
                T s = std::sin(angle * T(0.5));
                return quat<T>(
                    axis.x * s,
                    axis.y * s,
                    axis.z * s,
                    std::cos(angle * T(0.5))
                );
            }

            static quat<T> FromMatrix(const mat3<T>& mat);

            vec3<T> axis;
            T angle;
    };

    template <typename T>
    class mat2 {
        public:
            static_assert(std::is_floating_point_v<T>, "mat2 expects template T to be floating point type");
            mat2() : x(vec2<T>(T(1), T(0))), y(vec2<T>(T(0), T(1))) {}
            mat2(T xx, T xy, T yx, T yy) : x(vec2<T>(xx, xy)), y(vec2<T>(yx, yy)) {}
            mat2(const vec2<T>& _x, const vec2<T>& _y) : x(_x), y(_y) {}
            template <typename R> mat2(const mat2<R>& rhs) : x(rhs.x), y(rhs.y) {}
            template <typename R> mat2<T> operator* (const mat2<R>& rhs) const {
                return mat2<T>(
                    x.x * rhs.x.x + x.y * rhs.y.x,
                    x.x * rhs.x.y + x.y * rhs.y.y,

                    y.x * rhs.x.x + y.y * rhs.y.x,
                    y.x * rhs.x.y + y.y * rhs.y.y
                );
            }
            template <typename R> mat2<T>& operator*= (const mat2<R>& rhs) { return *this = *this * rhs; }
            template <typename R> mat2<T>& operator= (const mat2<R>& rhs) { x = rhs.x; y = rhs.y; return *this; }
            vec2<T>& operator[](u8 axis) { return (&x)[axis]; }
            const vec2<T>& operator[](u8 axis) const { return (&x)[axis]; }
            mat2<T> transposed() const {
                return mat2<T>(
                    x.x, y.x,
                    x.y, y.y
                );
            }
            void transpose() {
                T xy = x.y;
                x.y = y.x;
                y.x = xy;
            }

            vec2<T> x, y;
    };

    template <typename T>
    class mat3 {
        public:
            static_assert(std::is_floating_point_v<T>, "mat3 expects template T to be floating point type");
            mat3() : x(vec3<T>(T(1), T(0), T(0))), y(vec3<T>(T(0), T(1), T(0))), z(vec3<T>(T(0), T(0), T(1))) {}
            mat3(T xx, T xy, T xz, T yx, T yy, T yz, T zx, T zy, T zz) : x(vec3<T>(xx, xy, xz)), y(vec3<T>(yx, yy, yz)), z(vec3<T>(zx, zy, zz)) {}
            mat3(const vec3<T>& _x, const vec3<T>& _y, const vec3<T>& _z) : x(_x), y(_y), z(_z) {}
            template <typename R> mat3(const mat3<R>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
            template <typename R> mat3(const quat<R>& rhs) {
                T ax = rhs.axis.x * T(1.414214);
                T ay = rhs.axis.y * T(1.414214);
                T az = rhs.axis.z * T(1.414214);
                T ang = rhs.angle * T(1.414214);
                x.x = T(1.0) - (ay * ay + az * az);
                x.y = ax * ay + az * ang;
                x.z = ax * az - ay * ang;
                y.x = ax * ay - az * ang;
                y.y = T(1.0) - (az * az + ax * ax);
                y.z = ay * az + ax * ang;
                z.x = ax * az + ay * ang;
                z.y = ay * az - ax * ang;
                z.z = T(1.0) - (ay * ay + ax * ax);
            }
            template <typename R> mat3<T> operator* (const mat3<R>& rhs) const {
                return mat3<T>(
                    x.x * rhs.x.x + x.y * rhs.y.x + x.z * rhs.z.x,
                    x.x * rhs.x.y + x.y * rhs.y.y + x.z * rhs.z.y,
                    x.x * rhs.x.z + x.y * rhs.y.z + x.z * rhs.z.z,
                    
                    y.x * rhs.x.x + y.y * rhs.y.x + y.z * rhs.z.x,
                    y.x * rhs.x.y + y.y * rhs.y.y + y.z * rhs.z.y,
                    y.x * rhs.x.z + y.y * rhs.y.z + y.z * rhs.z.z,
                    
                    z.x * rhs.x.x + z.y * rhs.y.x + z.z * rhs.z.x,
                    z.x * rhs.x.y + z.y * rhs.y.y + z.z * rhs.z.y,
                    z.x * rhs.x.z + z.y * rhs.y.z + z.z * rhs.z.z
                );
            }
            template <typename R> vec3<T> operator* (const vec3<R>& rhs) const {
                return vec3<T>(
                    x.x * rhs.x + y.x * rhs.y + z.x * rhs.z,
                    x.y * rhs.x + y.y * rhs.y + z.y * rhs.z,
                    x.z * rhs.x + y.z * rhs.y + z.z * rhs.z
                );
            }
            template <typename R> mat3<T> operator*= (const mat3<R>& rhs) { return *this = *this * rhs; }
            template <typename R> mat3<T>& operator= (const mat3<R>& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
            vec3<T>& operator[](u8 axis) { return (&x)[axis]; }
            const vec3<T>& operator[](u8 axis) const { return (&x)[axis]; }
            mat3<T> transposed() const {
                return mat3<T>(
                    x.x, y.x, z.x,
                    x.y, y.y, z.y,
                    x.z, y.z, z.z
                );
            }
            void transpose() {
                T xy = x.y;
                T xz = x.z;
                T yz = y.z;
                
                x.y = y.x;
                x.z = z.x;
                y.z = z.y;

                y.x = xy;
                z.x = xz;
                z.y = yz;
            }
            static mat3<T> Rotation(const vec3<T>& axis, T angle) {
                return mat3<T>(quat<T>::FromAxisAngle(axis, angle));
            }
            static mat3<T> Scale(const vec3<T>& scale) {
                return mat3<T>(
                    scale.x, T(0.0), T(0.0),
                    T(0.0), scale.y, T(0.0),
                    T(0.0), T(0.0), scale.z
                );
            }
            static mat3<T> Scale(T scale) {
                return mat3<T>(
                    scale, T(0.0), T(0.0),
                    T(0.0), scale, T(0.0),
                    T(0.0), T(0.0), scale
                );
            }
            
            vec3<T> x, y, z;
    };

    template <typename T>
    class mat4 {
        public:
            static_assert(std::is_floating_point_v<T>, "mat2 expects template T to be floating point type");
            mat4() : x(vec4<T>(T(1), T(0), T(0), T(0))), y(vec4<T>(T(0), T(1), T(0), T(0))), z(vec4<T>(T(0), T(0), T(1), T(0))), w(vec4<T>(T(0), T(0), T(0), T(1))) {}
            mat4(
                T xx, T xy, T xz, T xw,
                T yx, T yy, T yz, T yw,
                T zx, T zy, T zz, T zw,
                T wx, T wy, T wz, T ww
            ) : x(vec4<T>(xx, xy, xz, xw)), y(vec4<T>(yx, yy, yz, yw)), z(vec4<T>(zx, zy, zz, zw)), w(vec4<T>(wx, wy, wz, ww)) {}
            mat4(
                const vec4<T>& _x,
                const vec4<T>& _y,
                const vec4<T>& _z,
                const vec4<T>& _w
            ) : x(_x), y(_y), z(_z), w(_w) {}
            template <typename R> mat4(const mat4<R>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
            template <typename R> mat4(const mat3<R>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z), w(vec4<T>(T(0), T(0), T(0), T(1))) {}
            template <typename R> mat4(const quat<R>& rhs) {
                T ax = rhs.axis.x * T(1.414214);
                T ay = rhs.axis.y * T(1.414214);
                T az = rhs.axis.z * T(1.414214);
                T ang = rhs.angle * T(1.414214);
                x.x = T(1.0) - (ay * ay + az * az);
                x.y = ax * ay + az * ang;
                x.z = ax * az - ay * ang;
                x.w = T(0.0);
                y.x = ax * ay - az * ang;
                y.y = T(1.0) - (az * az + ax * ax);
                y.z = ay * az + ax * ang;
                y.w = T(0.0);
                z.x = ax * az + ay * ang;
                z.y = ay * az - ax * ang;
                z.z = T(1.0) - (ay * ay + ax * ax);
                z.w = T(0.0);
                w = vec4<T>(T(0.0), T(0.0), T(0.0), T(1.0));
            }
            template <typename R> vec3<T> operator* (const vec3<R>& rhs) const {
                return vec3<T>(
                    x.x * rhs.x + y.x * rhs.y + z.x * rhs.z + w.x,
                    x.y * rhs.x + y.y * rhs.y + z.y * rhs.z + w.y,
                    x.z * rhs.x + y.z * rhs.y + z.z * rhs.z + w.z
                );
            }
            template <typename R> mat4<T> operator* (const mat4<R>& rhs) const {
                return mat4<T>(
                    x.x * rhs.x.x + x.y * rhs.y.x + x.z * rhs.z.x + x.w * rhs.w.x,
                    x.x * rhs.x.y + x.y * rhs.y.y + x.z * rhs.z.y + x.w * rhs.w.y,
                    x.x * rhs.x.z + x.y * rhs.y.z + x.z * rhs.z.z + x.w * rhs.w.z,
                    x.x * rhs.x.w + x.y * rhs.y.w + x.z * rhs.z.w + x.w * rhs.w.w,
                    
                    y.x * rhs.x.x + y.y * rhs.y.x + y.z * rhs.z.x + y.w * rhs.w.x,
                    y.x * rhs.x.y + y.y * rhs.y.y + y.z * rhs.z.y + y.w * rhs.w.y,
                    y.x * rhs.x.z + y.y * rhs.y.z + y.z * rhs.z.z + y.w * rhs.w.z,
                    y.x * rhs.x.w + y.y * rhs.y.w + y.z * rhs.z.w + y.w * rhs.w.w,
                    
                    z.x * rhs.x.x + z.y * rhs.y.x + z.z * rhs.z.x + z.w * rhs.w.x,
                    z.x * rhs.x.y + z.y * rhs.y.y + z.z * rhs.z.y + z.w * rhs.w.y,
                    z.x * rhs.x.z + z.y * rhs.y.z + z.z * rhs.z.z + z.w * rhs.w.z,
                    z.x * rhs.x.w + z.y * rhs.y.w + z.z * rhs.z.w + z.w * rhs.w.w,
                    
                    w.x * rhs.x.x + w.y * rhs.y.x + w.z * rhs.z.x + w.w * rhs.w.x,
                    w.x * rhs.x.y + w.y * rhs.y.y + w.z * rhs.z.y + w.w * rhs.w.y,
                    w.x * rhs.x.z + w.y * rhs.y.z + w.z * rhs.z.z + w.w * rhs.w.z,
                    w.x * rhs.x.w + w.y * rhs.y.w + w.z * rhs.z.w + w.w * rhs.w.w
                );
            }
            template <typename R> mat4<T> operator* (const mat3<R>& rhs) const {
                return mat4<T>(
                    x.x * rhs.x.x + x.y * rhs.y.x + x.z * rhs.z.x,
                    x.x * rhs.x.y + x.y * rhs.y.y + x.z * rhs.z.y,
                    x.x * rhs.x.z + x.y * rhs.y.z + x.z * rhs.z.z,
                    x.w,
                    
                    y.x * rhs.x.x + y.y * rhs.y.x + y.z * rhs.z.x,
                    y.x * rhs.x.y + y.y * rhs.y.y + y.z * rhs.z.y,
                    y.x * rhs.x.z + y.y * rhs.y.z + y.z * rhs.z.z,
                    y.w,
                    
                    z.x * rhs.x.x + z.y * rhs.y.x + z.z * rhs.z.x,
                    z.x * rhs.x.y + z.y * rhs.y.y + z.z * rhs.z.y,
                    z.x * rhs.x.z + z.y * rhs.y.z + z.z * rhs.z.z,
                    z.w,

                    w.x, w.y, w.z, w.w
                );
            }
            template <typename R> mat4<T> operator*= (const mat4<R>& rhs) { return *this = *this * rhs; }
            template <typename R> mat4<T> operator*= (const mat3<R>& rhs) { return *this = *this * rhs; }
            template <typename R> mat4<T>& operator= (const mat4<R>& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; w = rhs.w; return *this; }
            vec4<T>& operator[](u8 axis) { return (&x)[axis]; }
            const vec4<T>& operator[](u8 axis) const { return (&x)[axis]; }
            mat4<T> transposed() const {
                return mat4<T>(
                    x.x, y.x, z.x, w.x,
                    x.y, y.y, z.y, w.y,
                    x.z, y.z, z.z, w.z,
                    x.w, y.w, z.w, w.w
                );
            }
            void transpose() {
                T xy = x.y;
                T xz = x.z;
                T xw = x.w;
                T yz = y.z;
                T yw = y.x;
                T zw = z.w;
                
                x.y = y.x;
                x.z = z.x;
                x.w = w.x;
                y.z = z.y;
                y.w = w.y;
                z.w = w.z;

                y.x = xy;
                z.x = xz;
                z.y = yz;
                w.x = xw;
                w.y = yw;
                w.z = zw;
            }
            mat3<T> basis() const {
                return mat3<T>(
                    x.x, x.y, x.z,
                    y.x, y.y, y.z,
                    z.x, z.y, z.z
                );
            }
            static mat4<T> Translation(const vec3<T>& trans) {
                return mat4<T>(
                    T(1.0) , T(0.0) , T(0.0) , T(0.0),
                    T(0.0) , T(1.0) , T(0.0) , T(0.0),
                    T(0.0) , T(0.0) , T(1.0) , T(0.0),
                    trans.x, trans.y, trans.z, T(1.0)
                );
            }
            static mat4<T> Rotation(const vec3<T>& axis, T angle) {
                return mat4<T>(quat<T>::FromAxisAngle(axis, angle));
            }
            static mat4<T> Scale(const vec3<T>& scale) {
                return mat4<T>(
                    scale.x, T(0.0), T(0.0), T(0.0),
                    T(0.0), scale.y, T(0.0), T(0.0),
                    T(0.0), T(0.0), scale.z, T(0.0),
                    T(0.0), T(0.0), T(0.0) , T(1.0)
                );
            }
            static mat4<T> Scale(T scale) {
                return mat4<T>(
                    scale, T(0.0), T(0.0) , T(0.0),
                    T(0.0), scale, T(0.0) , T(0.0),
                    T(0.0), T(0.0), scale , T(0.0),
                    T(0.0), T(0.0), T(0.0), T(1.0)
                );
            }
            static mat4<T> LookAt(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up) {
                vec3<T> f = (center - eye).normalized();
                vec3<T> s = f.cross(up).normalized();
                vec3<T> u = s.cross(f);

                return mat4<T>(
                    vec4<T>(s.x, u.x, -f.x, T(0.0)),
                    vec4<T>(s.y, u.y, -f.y, T(0.0)),
                    vec4<T>(s.z, u.z, -f.z, T(0.0)),
                    vec4<T>(-s.dot(eye), -u.dot(eye), f.dot(eye), T(1.0))
                );
            }
            static mat4<T> Perspective(T fov, T aspect, T near, T far) {
                mat4<T> out;
                out.x.x = out.y.y = out.z.z = out.w.w = T(0.0);

                T a = T(1.0) / std::tan(fov * T(0.5));
                T b = a * aspect;

                out.x.x = a;
                out.y.y = b;
                out.z.z = (far + near) / (near - far);
                out.z.w = T(-1.0);
                out.w.z = (T(2.0) * near * far) / (near - far);

                return out;
            }
            
            vec4<T> x, y, z, w;
    };

    template <typename T>
    quat<T> quat<T>::FromMatrix(const mat3<T>& m) {
        auto getMinParamIdx = [](f32 a, f32 b, f32 c, f32 d) {
            u8 idx = 0;
            f32 min = a;
            
            if (b < min) {
                idx = 1;
                min = b;
            }
            
            if (c < min) {
                idx = 2;
                min = c;
            }
            
            if (d < min) {
                idx = 3;
                min = d;
            }

            return idx;
        };

        quat<T> out;
        f32 xx = m.x.x;
        f32 yy = m.y.y;
        f32 zz = m.z.z;
        f32 sum = xx + yy + zz;

        u8 minIdx = getMinParamIdx(sum, xx, yy, zz);

        switch (minIdx) {
            case 0: {
                f32 unk = sqrtf(sum + 1.0f) * 0.5f;
                f32 unk1 = 0.25f / unk;

                out.axis.x = (m.y.z - m.z.y) * unk1;
                out.axis.y = (m.z.x - m.x.z) * unk1;
                out.axis.z = (m.x.y - m.y.x) * unk1;
                out.angle = unk;
                break;
            }
            case 1: {
                f32 unk = sqrtf(((m.x.x + m.x.x) - sum) + 1.0f) * 0.5f;
                f32 unk1 = 0.25f / unk;

                out.axis.x = unk;
                out.axis.y = (m.x.y + m.y.x) * unk1;
                out.axis.z = (m.z.x + m.x.z) * unk1;
                out.angle = (m.y.z - m.z.y) * unk1;
                break;
            }
            case 2: {
                f32 unk = sqrtf(((m.y.y + m.y.y) - sum) + 1.0) * 0.5;
                f32 unk1 = 0.25 / unk;

                out.axis.x = (m.x.y + m.y.x) * unk1;
                out.axis.y = unk;
                out.axis.z = (m.y.z + m.z.y) * unk1;
                out.angle = (m.z.x - m.x.z) * unk1;
                break;
            }
            case 3: {
                f32 unk = sqrtf(((m.z.z + m.z.z) - sum) + 1.0f) * 0.5f;
                f32 unk1 = 0.25f / unk;

                out.axis.x = (m.z.x + m.x.z) * unk1;
                out.axis.y = (m.y.z + m.z.y) * unk1;
                out.axis.z = unk;
                out.angle = (m.x.y - m.y.x) * unk1;
                break;
            }
        }

        return out;
    }

    typedef vec2<i32> vec2i;
    typedef vec2<u32> vec2ui;
    typedef vec2<f32> vec2f;
    typedef vec2<f64> vec2d;
    typedef vec3<i32> vec3i;
    typedef vec3<u32> vec3ui;
    typedef vec3<f32> vec3f;
    typedef vec3<f64> vec3d;
    typedef vec4<i32> vec4i;
    typedef vec4<u32> vec4ui;
    typedef vec4<f32> vec4f;
    typedef vec4<f64> vec4d;

    typedef quat<f32> quatf;
    typedef quat<f64> quatd;

    typedef mat2<f32> mat2f;
    typedef mat2<f64> mat2d;
    typedef mat3<f32> mat3f;
    typedef mat3<f64> mat3d;
    typedef mat4<f32> mat4f;
    typedef mat4<f64> mat4d;

    #pragma pack(pop)
};