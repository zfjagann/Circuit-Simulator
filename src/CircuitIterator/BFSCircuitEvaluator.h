#ifndef __CIRCUIT_EVALUATOR__
#define __CIRCUIT_EVALUATOR__

#include "CircuitIterator.h"

////
//// BFSCircuitEvaluator class
////

class BFSCircuitEvaluator : public CircuitIterator {

private:

    list<CustomComponent*> toBeVisited;

    CustomComponent* myCurrItem;

    Circuit* myCircuit;

protected:

    // Are we done?
    virtual bool IsDone();

    // Evaluate the current item
    virtual void EvaluateCurrentItem();

    // Proceeds to the next item
    virtual void Progress();

    // Fetch the current item
    virtual CustomComponent* CurrentItem();

    // Resets the simulator for the given circuit.
    void reset();

public:

    BFSCircuitEvaluator();

    // Destructor
    virtual ~BFSCircuitEvaluator();

    // Sets up iteration for a given circuit.
    virtual void Setup(Circuit&);

    // Iterate
    virtual void Iterate();

    // Clears the queue of items.
    void Clear();

};

#endif
