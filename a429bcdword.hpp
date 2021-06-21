#ifndef A429BCDWORD_HPP
#define A429BCDWORD_HPP

#include "a429word.hpp"

using ushort = unsigned short;
using uint = unsigned int;

class A429BcdWord : public A429Word {

public:
    // CONSTRUCTORS
    A429BcdWord();
    A429BcdWord(const ushort& nbDigits, const float& resolution);

    // DESTRUCTOR
    ~A429BcdWord();

    // GETTERS & SETTERS

    // METHODS
private:
    int getDigitValue(const ushort& msb, const ushort& lsb);

private:
    bool m_isSigned = false;
    short m_signBit = -1;
    ushort m_nbDigits = 0;
    float m_resolution = 1.0;
};

#endif // A429BCDWORD_HPP