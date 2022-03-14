#pragma once


template<typename SizeT>
class StaticEditCosts {
    static void setDeletionCost(SizeT deletionCost);
    static void setInsertionCost(SizeT insertionCost);
    static void setSwapCost(SizeT swapCost);

protected:
    static SizeT DELETION_COST;
    static SizeT INSERTION_COST;
    static SizeT SWAP_COST;
};


template<typename SizeT>
void StaticEditCosts<SizeT>::setDeletionCost(SizeT deletionCost) {
    DELETION_COST = deletionCost;
}


template<typename SizeT>
void StaticEditCosts<SizeT>::setInsertionCost(SizeT insertionCost) {
    INSERTION_COST = insertionCost;
}


template<typename SizeT>
void StaticEditCosts<SizeT>::setSwapCost(SizeT swapCost) {
    SWAP_COST = swapCost;
}


template<typename SizeT>
SizeT StaticEditCosts<SizeT>::DELETION_COST = 1;


template<typename SizeT>
SizeT StaticEditCosts<SizeT>::INSERTION_COST = 1;


template<typename SizeT>
SizeT StaticEditCosts<SizeT>::SWAP_COST = 1;