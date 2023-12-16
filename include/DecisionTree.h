//
// Created by adrien on 12/16/23.
//

#ifndef CLASSIFICATIONTP_DECISIONTREE_H
#define CLASSIFICATIONTP_DECISIONTREE_H

#include "Split.h"

typedef struct sDecisionTreeNode{
    struct sDecisionTreeNode* left;
    struct sDecisionTreeNode* right;
    Split split;
    int classID;
} DecisionTreeNode;

#endif //CLASSIFICATIONTP_DECISIONTREE_H
