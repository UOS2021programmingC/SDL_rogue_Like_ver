#ifndef VECTOR2D_H
#define VECTOR2D_H 

#include "defs.h"

class Vector2D 
{
public:

    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    /*
     * friend : friend로 선언된 클래스 끼리 
     *서로 private 및 portected멤버에 접근 가능
     */

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+= (const Vector2D& vec);
    Vector2D& operator-= (const Vector2D& vec);
    Vector2D& operator*= (const Vector2D& vec);
    Vector2D& operator/= (const Vector2D& vec);

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);

};

#endif