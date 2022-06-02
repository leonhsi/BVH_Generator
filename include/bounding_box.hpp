#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "vector3.hpp"
#include "climits"

namespace bvh{

struct BoundingBox{
    Vector3 min, max;

    BoundingBox() = default;
    BoundingBox(const Vector3 &v) : min(v), max(v) {}
    BoundingBox(const Vector3 &min, const Vector3 &max) : min(min), max(max) {}

    BoundingBox& shrink(const BoundingBox &bbox){
        min = bvh::max(min, bbox.min);
        max = bvh::min(max, bbox.max);
        return *this;
    }

    BoundingBox& extend (const BoundingBox &bbox){
        min = bvh::min(min, bbox.min);
        max = bvh::max(max, bbox.max);
        return *this;
    }

    BoundingBox& extend(const Vector3 &v){
        min = bvh::min(min, v);
        max = bvh::max(max, v);
        return *this;
    }

    BoundingBox empty(){
        return BoundingBox(Vector3(std::numeric_limits<double>::max()), Vector3(-std::numeric_limits<double>::max()));
    }

    Vector3 diagonal() const{
        return max - min;
    }

    Vector3 center() const{
        return (max+min) * (double)(0.5);
    }

    double half_area() const{
        auto d = diagonal();
        return (d[0] + d[1]) * d[2] + d[0] * d[1];
    }
};

template <typename Primitive>
std::pair<std::unique_ptr<BoundingBox[]>, std::unique_ptr<Vector3[]>>
compute_bounding_boxes_and_centers(const Primitive* primitives, size_t primitive_count){
    auto bounding_boxes = std::make_unique<BoundingBox[]>(primitive_count);
    auto centers = std::make_unique<Vector3[]>(primitive_count);

    for(size_t i=0; i<primitive_count; i++){
        bounding_boxes[i] = primitives[i].bounding_box();
        centers[i] = primitives[i].centers();
    }

    return std::make_pair(std::move(bounding_boxes), std::move(centers));
}

BoundingBox compute_bounding_boxes_union(const BoundingBox* bboxes, size_t count){
    BoundingBox bbox;
    bbox = bbox.empty();

    for(size_t i=0; i<count; i++){
        bbox.extend(bboxes[i]);
    }
    return bbox;
}

} //namespace bvh

#endif