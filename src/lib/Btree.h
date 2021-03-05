#ifndef SQLLITECLONE_BTREE_H
#define SQLLITECLONE_BTREE_H

#include <cstdint>
#include <memory>
#include "Page.h"

namespace SQLCore {
    /*
     * Each node will correspond to one page. Internal nodes will point to their children by storing
     * the page number that stores the child. The btree asks the pager for a particular page number
     * and gets back a pointer into the page cache. Pages are stored in the database
     * file one after the other in order of page number.
     * Nodes need to store some metadata in a header at the beginning of the page.
     * Every node will store what type of node it is, whether or not it is the root node,
     * and a pointer to its parent (to allow finding a node’s siblings).
     * I define constants for the size and offset of every header field:
     */
    typedef enum {
        NODE_INTERNAL, NODE_LEAF, NODE_ROOT
    } NodeType;

    class Node {
    public:
        Node(NodeType nodeType, bool isRootNode, std::shared_ptr<Page> &page;

        );

        const std::shared_ptr<Node> parent() const { return d_parent; };

        void setParent(std::shared_ptr<Node> &node) { d_parent = node; };

        inline bool isRoot() const { return d_isRootNode; }

        inline bool isLeaf() const { return d_isLeafNode; }

        inline const NodeType nodeType() const { return d_nodeType; };

        void setIsRoot(bool isRoot) {
            d_isRootNode = isRoot;
            d_isLeafNode = !isRoot;
        };
    private:
        std::shared_ptr<Node> d_parent = nullptr;
        bool d_isLeafNode;
        bool d_isRootNode;
        std::shared_ptr<Page> d_page;
        NodeType d_nodeType;
    };


    std::shared_ptr<Node> getNode(NodeType nodeType, std::shared_ptr<Page> &page);

    class Btree {
        const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
        const uint32_t NODE_TYPE_OFFSET = 0;
        const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
        const uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
        const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
        const uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
        const uint8_t COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;
    };
}


#endif //SQLLITECLONE_BTREE_H
