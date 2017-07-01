#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED
#include <math.h>
#include <iostream>
using namespace std;
struct Point
{
    float x;
    float y;
    float z;
    Point()
    {
        x=0;
        y=0;
        z=0;
    }
    Point(float X,float Y,float Z=0)
    {
        x = X;
        y = Y;
        z = Z;
    }
};
 class Vector3D
 {
    public:
    float x;
    float y;
    float z;
    Vector3D()
    {
        x = 0.0f; y = 0.0f; z = 0.0f;
    }
    Vector3D(float X, float Y, float Z = 0.0f)
    {
        x = X;
        y = Y;
        z = Z;
    }
    /*Vector3D(float _x, float _y)
    {
        x = _x; y = _y; z = 0.0f;
    }*/
    Vector3D operator - (Vector3D p);
    Vector3D& operator * (const float p);
    Vector3D& operator /= (const float p);
    Vector3D& operator = (const Vector3D &p);
    Vector3D& operator += (const Vector3D &p);

    void setX(float x_)
    {
        x = x_;
    }
    void setY(float y_)
    {
        y = y_;
    }
    void setZ(float z_)
    {
        z = z_;
    }
    void setXY(float x_, float y_)
    {
        x = x_;
        y = y_;
    }
    void setXYZ(float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
    void setXYZ(Vector3D v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    float magnitude()
    {
        return (float) sqrt(x*x + y*y + z*z);
    }

    Vector3D copy()
    {
        return  Vector3D(x,y,z);
    }
    Vector3D copy(Vector3D v)
    {
        return  Vector3D(v.x, v.y,v.z);
    }
    void add(Vector3D v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    void sub(Vector3D v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    void mult(float n)
    {
        x *= n;
        y *= n;
        z *= n;
    }
    void div(float n)
    {
        x /= n;
        y /= n;
        z /= n;
    }
    void normalize()
    {
        float m = magnitude();
        if (m > 0)
        {
            div(m);
        }

    }
    void limit(float maximo)
    {
        if (magnitude() > maximo)
        {
            normalize();
            mult(maximo);
        }
    }
    float heading2D()
    {
        float angle = (float) atan2(z,x);
        if (angle == 0) return 0.0;
        //cout <<endl<<angle*-1;
        return -1*angle;
    }

    Vector3D add(Vector3D v1, Vector3D v2)
    {
        Vector3D v =  Vector3D(v1.x + v2.x,v1.y + v2.y, v1.z + v2.z);
        return v;
    }
    Vector3D sub(Vector3D v1, Vector3D v2)
    {
        Vector3D v =  Vector3D(v1.x - v2.x,v1.y - v2.y,v1.z - v2.z);
        return v;
    }
    Vector3D div(Vector3D v1, float n)
    {
        Vector3D v =  Vector3D(v1.x/n,v1.y/n,v1.z/n);
        return v;
    }
    Vector3D mult(Vector3D v1, float n)
    {
        Vector3D v =  Vector3D(v1.x*n,v1.y*n,v1.z*n);
        return v;
    }
    float distance (Vector3D v1, Vector3D v2)
    {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        float dz = v1.z - v2.z;
        return (float) sqrt(dx*dx + dy*dy + dz*dz);
    }
};

Vector3D& Vector3D::operator = (const Vector3D &p)
{
    if(this!=&p){ //Comprueba que no se esté intentanod igualar un objeto a sí mismo
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;
    }
    return *this;
}

Vector3D& Vector3D::operator += (const Vector3D &p)
{
    if(this!=&p){ //Comprueba que no se esté intentanod igualar un objeto a sí mismo
        this->x += p.x;
        this->y += p.y;
        this->z += p.z;
    }
    return *this;
}
Vector3D& Vector3D::operator * (const float p)
{
//    if(this!=&p){ //Comprueba que no se esté intentanod igualar un objeto a sí mismo
        this->x *= p;
        this->y *= p;
        this->z *= p;
//    }
    return *this;
}

Vector3D& Vector3D::operator /= (const float p)
{
    if (p>0)
    {
        this->x /= p;
        this->y /= p;
        this->z /= p;
    }
    return *this;
}
Vector3D Vector3D::operator - (Vector3D v2)
{
        Vector3D v =  Vector3D(x - v2.x,y - v2.y,z - v2.z);
        return v;
}

#endif // VECTOR3D_H_INCLUDED
