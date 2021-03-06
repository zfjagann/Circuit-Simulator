#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include "Component.h"
#include "CustomComponent.h"
#include "Wire.h"
#include <list>
#include <string>
#include "gc_cpp.h"
#include <utility>
#include "sparse_hash_map.h"
using namespace std;

//
// eqstr Structure
//
// Used for string comparison in the dictionary.
//

struct eqstr {
    bool operator()(const string& s1, const string& s2) const {
        return s1 == s2;
    }
};

////
//// Circuit Class Definition
////

/**
Class:
	Circuit

The circuit class provides a complete interface for interacting with circuit components and evaluators.

All interactions that a user should routinely need are represented in this class, including creating components and
adding them to the breadboard, connecting components with wires, desegnating components for input or output, and
evaluating a circuit in a variety of ways.
*/

class Circuit : public gc {

private:

    // Inputs to the Circuit
    list<CustomComponent*> inputComponents;

    // Outputs to the Circuit
    list<CustomComponent*> outputComponents;

    // Hash table for all the linked components
    google::sparse_hash_map<string, Component, tr1::hash<string>, eqstr> components;

    // Are we simulating gate delays?
    bool simulateGateDelays;

public:

    /// Constructor
	/// Creates an empty breadboard circuit.
    Circuit();

    /// Destructor
	/// Empty destructor
    virtual ~Circuit ();

    ////
    //// Hashing Functions
    ////

    /// Links a circuit as an input gate of this circuit, with an optional identifier
    void AddInput(Component);
    void AddInput(string);

    /// Links a subcircuit as an output gate of this circuit, with an optional identifier
    void AddOutput(Component);
    void AddOutput(string);

    /// Links an arbitrary component with an identifier.
    void AddComponent(string, Component);

    /// Returns the component with the given identifier.
    Component Lookup(string);

    /// Attaches a probe to a particular component's output
    void AttachProbe(string name, int outNo);

    ////
    //// Helper Functions
    ////

    /// Links two circuits with a wire.
    /// Uses the specified input and output wire numbers.
    static void Connect(Component in, unsigned int inNo, Component out, unsigned int outNo, bool initWireState = true);
    void Connect(string inId, unsigned int inNo, string outId, unsigned int outNo, bool initWireState = true);

    ////
    //// Circuit Evaluation
    ////

    /// Evaluates the circuit
    void Evaluate();

    /// Turn on using gate delays.
    void UseGateDelays();

	/// Turn off using gate delays.
    void IgnoreGateDelays();

	/// Debug the circuit
	void Debug();

    /// Returns the input subcircuits
    list<CustomComponent*> GetInputComponents() const;

    /// Returns the output subcircuits
    list<CustomComponent*> GetOutputComponents() const;

    ////
    //// Helper Functions for Black-Box components:
    ////

    /// Copies a circuit's output components's states to a vector:
    void PushOutput(vector<State::Boolean>&);

    /// Provides input to the circuit from a vector:
    void PullInput(const vector<State::Boolean>&);

};

#endif /* __CIRCUIT_H__ */

