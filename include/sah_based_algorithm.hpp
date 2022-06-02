#ifndef SAH_BASED_ALGORITHM_H
#define SAH_BASED_ALGORITHM_H

#include "bvh.hpp"

namespace bvh{

class SahBasedAlgorithm{
public:
    double traversal_cost = 1;

protected:
    ~SahBasedAlgorithm(){}
    
    double compute_cost(const Bvh& bvh) const {
        double cost = 0;
        for(size_t i=0; i<bvh.node_count; i++){
            auto half_area = bvh.nodes[i].bounding_box_proxy().half_area();
            if(bvh.nodes[i].is_leaf())
                cost += half_area * static_cast<double>(bvh.nodes[i].primitive_count);
            else
                cost += half_area * traversal_cost;
        }
        return cost / bvh.nodes[0].bounding_box_proxy().half_area();
    }

};

}//namespace bvh

#endif