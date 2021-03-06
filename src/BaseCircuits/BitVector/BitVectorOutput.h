#ifndef __BitVectorOutput_H__
#define __BitVectorOutput_H__

#include "CircuitSimulator.h"

////
//// BitVectorOutput
////

class BitVectorOutput : public CustomComponent {

protected:

    // Evaluates the Subcircuit with certain states.
    // Returns the amount of time it takes to run.
    // If not simulating gate delays, a 0 should be returned.
    void Evaluate(const vector<State::Boolean>& inputStates, vector<State::Boolean>& outputStates) {

        // Actually Do Stuff:

        cout << "[" << GetName() << "] ";
        for(int i = 0; i < inputStates.size(); i++) {
            cout << bool(inputStates[i]);
        }
        cout << endl;
    }

    // Returns the delay of the component
    State::Timestamp Delay() {
        return 0;
    }

public:

    // Constructor
    BitVectorOutput(int size)
        : CustomComponent("BitVectorOutput", size, 0)
        {
        // Do Nothing
    }

};

#endif
