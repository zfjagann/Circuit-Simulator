#include <iostream>
#include "CircuitSimulator.h"

////
//// Example of the circuit simulator that uses components defined
//// on the top level, rather than linking them into the hash of the circuit.
////

int main() {

    // Create the top-level circuit
    Circuit topLevel;

    // In this example, we use this to store information about the components that
    // are in the circuit, rather than just the input and output components.

    // Create the components.
    Component in1(new Button());
    Component in2(new Button());
    Component or1(new Or());
    Component or2(new Or());
    Component not1(new Not());
    Component not2(new Not());
    Component spl1(new Splitter(2));
    Component spl2(new Splitter(2));
    Component out1(new LED());
    Component out2(new LED());

    // Connect the buttons
    topLevel.Connect(in1,0,or1,0);
    topLevel.Connect(in2,0,or1,1);

    // Connect the or's to the splitters
    topLevel.Connect(or1,0,spl1,0);
    topLevel.Connect(or2,0,spl2,0);

    // Connect Splitter1
    topLevel.Connect(spl1,0,out1,0);
    topLevel.Connect(spl1,1,not1,0);

    // Connect Splitter2
    topLevel.Connect(spl2,0,out2,0);
    topLevel.Connect(spl2,1,not2,0);

    // Connect the not's
    topLevel.Connect(not1,0,or2,0);
    topLevel.Connect(not2,0,or2,1);

    // Notify the circuit of it's input gates.
    topLevel.AddInput(in1);
    topLevel.AddInput(in2);
    topLevel.AddOutput(out1);
    topLevel.AddOutput(out2);

    // Evaluate the circuit.
    topLevel.Evaluate();

    return 0;
}
