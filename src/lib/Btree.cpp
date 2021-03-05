#include "Btree.h"

namespace SQLCore {

    Node::Node(NodeType nodeType, bool isRootNode, std::shared_ptr<Page> &page)
            : d_nodeType(nodeType),
              d_isLeafNode(!isRootNode),
              d_isRootNode(isRootNode),
              d_page(page),
              d_parent(nullptr) {
    }

    std::shared_ptr<Node> getNode(NodeType nodeType, std::shared_ptr<Page> &page) {
        if (nodeType == NODE_LEAF || nodeType == NODE_INTERNAL) {
            return std::shared_ptr<Node>(new Node(nodeType, false, page));
        }
        return std::shared_ptr<Node>(new Node(NODE_ROOT, true, page));
    }
}