#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <vector>
#include <map>
#include <iostream>
using namespace std;

namespace Common
{

class Disjoint_sets
{
public:
    explicit Disjoint_sets(size_t num_elements)
        : sets_(num_elements, -1),
          rank_(num_elements, 1)
    {}

    void union_sets(int root1, int root2)
    {
        // TBD: implement weighted-union to take into account size of the trees
        if ((root1 == root2) || (root1 < 0) || (root1 > sets_.size()) || (root2 < 0) || (root2 > sets_.size()))
            return;
        sets_[root2] = root1;
    }

    void union_elements(int elem1, int elem2)
    {
        int root1 = this->find(elem1);
        int root2 = this->find(elem2);
        this->union_sets(root1, root2);
    }

    int find(int elem)
    {
        // TBD: implement path compression
        if ((elem < 0) || (elem > sets_.size()))
            return -1;
        if (sets_[elem] == -1)
            return elem;
        return find(sets_[elem]);
    }

    map<int, size_t> count_sets()
    {
        map<int, size_t> res;
        for (size_t i=0; i < sets_.size(); ++i) {
            // not root
            if (sets_[i] >= 0) {
                int root = this->find(i);
                if (root >= 0)
                    res[root] += 1;
            }
            // root
            else {
                res.insert({i, 1});
            }
        }
        return res;
    }

private:
    vector<int> sets_;
    vector<int> rank_;
};

}

#endif // DATA_STRUCT_H
