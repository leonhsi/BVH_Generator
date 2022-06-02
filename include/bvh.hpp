#ifndef BVH_H
#define BVH_H

#include "climits"
#include "stddef.h"
#include "cassert"

#include "bounding_box.hpp"

namespace bvh{

struct Bvh{
    struct Node{
        double bounds[6];
        size_t primitive_count;
        size_t first_child_or_primitive;

        bool is_leaf() const {return primitive_count != 0;}

        struct BoundingBoxProxy{
            Node& node;
            
            BoundingBoxProxy(Node& node) : node(node) {}

            BoundingBoxProxy& operator= (const BoundingBox& bbox){
                node.bounds[0] = bbox.min[0];
                node.bounds[1] = bbox.max[0];
                node.bounds[2] = bbox.min[1];
                node.bounds[3] = bbox.max[1];
                node.bounds[4] = bbox.min[2];
                node.bounds[5] = bbox.max[2];
                return *this;
            }

            operator BoundingBox () const{
                return BoundingBox(Vector3(node.bounds[0], node.bounds[1], node.bounds[2]), 
                                    Vector3(node.bounds[3], node.bounds[4], node.bounds[5]));
            }

            BoundingBox to_bounding_box() const{
                return static_cast<BoundingBox>(*this);
            }

            double half_area() const {return to_bounding_box().half_area();}

        };//struct BoundingBoxProxy

        BoundingBoxProxy bounding_box_proxy(){
            return BoundingBoxProxy(*this);
        }

        const BoundingBoxProxy bounding_box_proxy() const{
            return BoundingBoxProxy(*const_cast<Node*>(this));
        }

    };//struct Node

    size_t sibling(size_t index){
        assert(index != 0);
        return index %2 == 1 ? index+1 : index-1;
    }

    std::unique_ptr<Node[]> nodes;
    std::unique_ptr<size_t[]> primitive_indices;

    size_t node_count = 0;
};

} //namespace bvh

#endif