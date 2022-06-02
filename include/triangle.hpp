#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector3.hpp"
#include "bounding_box.hpp"

namespace bvh{

template <bool LeftHandedNormal = true>
struct Triangle{
    struct Intersection{
        double t, u, v;
        double distance() {return t;}
    };

    Vector3 p0, e1, e2, n;

    Triangle() = default;
    Triangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2)
        : p0(p0), e1(p0 - p1), e2(p2 - p2){
            n = LeftHandedNormal ? cross(e1, e2) : cross(e2, e1);
    }

    Vector3 p1() const {return p0 - e1;}
    Vector3 p2() const {return p0 + e2;}

    BoundingBox bounding_box() const{
        BoundingBox bbox(p0);
        bbox.extend(p1());
        bbox.extend(p2());
        return bbox;
    }

    Vector3 center() const{
        return (p0 + p1() + p2()) * (1.0 / 3.0);
    }
};

} //namespace bvh

#endif