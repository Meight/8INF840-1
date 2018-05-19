/*
 * @author Matthieu Le Boucher <matt.leboucher@gmail.com>
 */

#include "NTree.h"

NTree::NTree() {}

NTree::~NTree() {}

int NTree::getDepth() {
    return 0;
}

void NTree::print(TraversalMethod method) {
    switch (method) {
        case PRE_ORDER:
            if (root)
            break;
        case IN_ORDER:
            break;
        case POST_ORDER:
            break;
    }
}

