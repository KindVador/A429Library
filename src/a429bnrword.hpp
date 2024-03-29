#ifndef A429BNRWORD_HPP
#define A429BNRWORD_HPP

#include "a429word.hpp"

class A429BnrWord : public A429Word {

public:
    // CONSTRUCTORS
    A429BnrWord();
    A429BnrWord(bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution);
    A429BnrWord(uint value, bool labelNumberMsbFirst, bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution);
    A429BnrWord(const std::string& value, bool labelNumberMsbFirst, int base, bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution);

    // DESTRUCTOR
    ~A429BnrWord() override = default;

    // GETTERS & SETTERS
    bool isSigned() const;
    void setIsSigned(bool value);

    ushort signBitPosition() const;
    void setSignBitPosition(ushort position);

    ushort msbBitPosition() const;
    void setMsbBitPosition(ushort position);

    ushort lsbBitPosition() const;
    void setLsbBitPosition(ushort position);

    double resolution() const;
    void setResolution(double value);

    // METHODS
    double getIndustrialValue();

private:
    bool m_isSigned = true;
    ushort m_signBitPosition = 29;
    ushort m_msbBitPosition = 28;
    ushort m_lsbBitPosition = 11;
    double m_resolution = 1.0;
};

#endif // A429BNRWORD_HPP