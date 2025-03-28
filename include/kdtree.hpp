#ifndef KDTREE_H
#define KDTREE_H

#include "precomp.hpp"

namespace cv
{
namespace ml
{

/*!
 Fast Nearest Neighbor Search Class.

 The class implements D. Lowe BBF (Best-Bin-First) algorithm for the last
 approximate (or accurate) nearest neighbor search in multi-dimensional spaces.

 First, a set of vectors is passed to KDTree::KDTree() constructor
 or KDTree::build() method, where it is reordered.

 Then arbitrary vectors can be passed to KDTree::findNearest() methods, which
 find the K nearest neighbors among the vectors from the initial set.
 The user can balance between the speed and accuracy of the search by varying Emax
 parameter, which is the number of leaves that the algorithm checks.
 The larger parameter values yield more accurate results at the expense of lower processing speed.

 \code
 KDTree T(points, false);
 const int K = 3, Emax = INT_MAX;
 int idx[K];
 float dist[K];
 T.findNearest(query_vec, K, Emax, idx, 0, dist);
 CV_Assert(dist[0] <= dist[1] && dist[1] <= dist[2]);
 \endcode
*/
class CV_EXPORTS_W KDTree
{
public:
    /*!
        KD树节点结构体
    */
    struct Node
    {
        // 默认构造函数，初始化一个空节点
        Node() : idx(-1), left(-1), right(-1), boundary(0.f) {}
        // 构造一个新节点
        Node(int _idx, int _left, int _right, float _boundary)
            : idx(_idx), left(_left), right(_right), boundary(_boundary) {}

        int idx;      // 对于内部节点，表示分割维度；对于叶节点，表示点的索引（<0）
        int left;     // 左子节点在nodes数组中的索引
        int right;    // 右子节点在nodes数组中的索引
        float boundary; // 分割边界值：如果查询点在该维度的值<=boundary则走左子树，否则走右子树
    };

    //! the default constructor
    CV_WRAP KDTree();
    //! the full constructor that builds the search tree
    CV_WRAP KDTree(InputArray points, bool copyAndReorderPoints = false);
    //! the full constructor that builds the search tree
    CV_WRAP KDTree(InputArray points, InputArray _labels,
                   bool copyAndReorderPoints = false);
    //! builds the search tree
    CV_WRAP void build(InputArray points, bool copyAndReorderPoints = false);
    //! builds the search tree
    CV_WRAP void build(InputArray points, InputArray labels,
                       bool copyAndReorderPoints = false);
    //! finds the K nearest neighbors of "vec" while looking at Emax (at most) leaves
    CV_WRAP int findNearest(InputArray vec, int K, int Emax,
                            OutputArray neighborsIdx,
                            OutputArray neighbors = noArray(),
                            OutputArray dist = noArray(),
                            OutputArray labels = noArray()) const;
    //! finds all the points from the initial set that belong to the specified box
    CV_WRAP void findOrthoRange(InputArray minBounds,
                                InputArray maxBounds,
                                OutputArray neighborsIdx,
                                OutputArray neighbors = noArray(),
                                OutputArray labels = noArray()) const;
    //! returns vectors with the specified indices
    CV_WRAP void getPoints(InputArray idx, OutputArray pts,
                           OutputArray labels = noArray()) const;
    //! return a vector with the specified index
    const float* getPoint(int ptidx, int* label = 0) const;
    //! returns the search space dimensionality
    CV_WRAP int dims() const;

    std::vector<Node> nodes; //!< all the tree nodes
    CV_PROP Mat points; //!< all the points. It can be a reordered copy of the input vector set or the original vector set.
    CV_PROP std::vector<int> labels; //!< the parallel array of labels.
    CV_PROP int maxDepth; //!< maximum depth of the search tree. Do not modify it
    CV_PROP_RW int normType; //!< type of the distance (cv::NORM_L1 or cv::NORM_L2) used for search. Initially set to cv::NORM_L2, but you can modify it
};

}
}

#endif