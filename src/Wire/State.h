#ifndef __WIRE_STATE_H__
#define __WIRE_STATE_H__

#include "gc_cpp.h"

////
//// State Class
////

class State : public gc
{

public:

    ////
    //// Type Definitions
    ////

    // This class's main purpose is to restrict the opertions
    // available to timestamps.
    // It's essentially a wrapper for an integer type with only
    // certain operations defined.
    class Timestamp : public gc
    {

    private:

        // Long long is always 64 bits, whereas long is only 64 bits on a x64 system.
        // I wanted something REALLY long.

        // Internal timestamp
        unsigned long long stamp;

    public:

        // Default Constructor
        Timestamp(unsigned long long = 0);

        // Incremental copy constructor
        // Copies the value, then adds the specified amount.
        Timestamp(const Timestamp&, const unsigned long long&);

        // Copy Constructor
        Timestamp(const Timestamp&);

        // Addition
        Timestamp operator+(const Timestamp&) const;

        // Subtraction
        Timestamp operator-(const Timestamp&) const;

        // Greater than
        bool operator>(const Timestamp&) const;

        // Less than
        bool operator<(const Timestamp&) const;

        unsigned long long value() const;

    };

    ////
    //// State Declaration
    //// Along with associated constants.
    ////

    //typedef State bool;

    class Boolean : public gc
    {

    private:

        // The state of the State (ba dum cha)
        bool intern_state;

    public:

        // Constructor
        Boolean(bool);

        // Destructor
        ~Boolean();

        // Comparison Operators
        bool operator ==(const Boolean&) const;
        bool operator !=(const Boolean&) const;

        // Or Operators
        Boolean operator or(const Boolean&) const;

        // And Operators
        Boolean operator and(const Boolean&) const;

        // Exclusive Or
        Boolean operator xor(const Boolean&) const;

        // Not Operators
        Boolean operator not() const;

        // Convert to a bool
        operator bool() const;

    };

private:

    // Most Recent State Change
    Boolean change;

    // Timestamp of the most recent change.
    Timestamp changeTime;

public:

    static const Boolean Up;
    static const Boolean High;
    static const Boolean Down;
    static const Boolean Low;

    // Creates a State with a Boolean value and Timestamp.
    State (const Boolean& = false, const Timestamp = 0);

    // Destructor
    virtual ~State ();

    // Returns the last state of the wire.
    Boolean LastValue() const;

    // Returns the current state of the wire.
    Boolean CurrentValue() const;

    // Returns the timestamp of the wire state.
    Timestamp Time() const;

    // Convert to a bool
    operator bool() const;

    operator Boolean() const;

};

#endif /* __WIRE_STATE_H__ */

