#ifndef SWEEP_SAH_BUILDER_H
#define SWEEP_SAH_BUILDER_H

#include "stddef.h"
#include "stack"

namespace bvh{

class TopDownBuildTask{
protected:
    struct WorkItem{
        size_t node_index;
        size_t begin;
        size_t end;
        size_t depth;

        WorkItem() = default;
        WorkItem(size_t node_index, size_t begin, size_t end, size_t depth) 
            : node_index(node_index), begin(begin), end(end), depth(depth) {}

        size_t work_size() const {return end - begin;}
    };
};

class TopDownBuilder{
public:
    size_t task_threshold = 1024;
    size_t max_depth = 64;
    size_t max_leaf_size = 16;
protected:
    ~TopDownBuilder(){}

    template <typename BuildTask, typename... Args>
    void run_task(BuildTask& task, Args&&... args){
        using WorkItem = typename BuildTask::WorkItemType;
        std::stack<WorkItem> stack;
        stack.emplace(std::forward<Args&&>(args)...);
        while(!stack.empty()){
            auto work_item = stack.top();
            //assert
            stack.pop();

            auto more_work = task.build(work_item);
            if(more_work){
                if(more_work->first.work_size() > more_work->second.work_size())
                    std::swap(more_work->first, more_work->second);

                stack.push(more_work->second);
                auto first_item = more_work->first;
                if(first_item.work_size() > task_threshold){
                    BuildTask new_task(task);
                    run_task(new_task, first_item);
                }
                else{
                    stack.push(first_item);
                }
            }
        }
    }

};

}//namespace bvh

#endif