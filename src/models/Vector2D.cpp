#include "Vector2D.h"

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(const int& nx, const int& ny) : x(nx), y(ny) {}

Vector2D Vector2D::operator+(const Vector2D& a)
{
    Vector2D r;
    r.x = this->x + a.x;
    r.y = this->y + a.y;
    return r;
}

Vector2D Vector2D::operator-(const Vector2D& a)
{
    Vector2D r;
    r.x = this->x - a.x;
    r.y = this->y - a.y;
    return r;
}

Vector2D Vector2D::operator*(const Vector2D& a)
{
    Vector2D r;
    r.x = this->x * a.x - this->y * a.y;
    r.y = this->y * a.x + this->x * a.y;
    return r;
}

Vector2D Vector2D::operator*(const int& i)
{
    Vector2D r;
    r.x = this->x * i;
    r.y = this->y * i;
    return r;
}

Vector2D Vector2D::calculNorme()
{
    Vector2D r;
    double norme = sqrt(this->x * this->x + this->y * this->y);
    if (norme != 0.0)
    {
        r.x = this->x / norme;
        r.y = this->y / norme;
    }
    return r;
}