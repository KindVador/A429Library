#include "a429bcdword.hpp"
#include <cmath>

A429BcdWord::A429BcdWord(): A429Word()
{

}

A429BcdWord::A429BcdWord(uint value, const DigitsVec& digits, bool labelNumberMsbFirst, bool oddParity, const float& resolution): 
    A429Word(value, labelNumberMsbFirst, oddParity), m_digitsPos(digits), m_resolution(resolution)
{

}

A429BcdWord::A429BcdWord(std::string value, const DigitsVec& digits, bool labelNumberMsbFirst, int base, bool oddParity, const float& resolution):
    A429Word(value, labelNumberMsbFirst, base, oddParity), m_digitsPos(digits), m_resolution(resolution)
{

}

A429BcdWord::A429BcdWord(const DigitsVec& digits, const float& resolution): A429Word(), m_digitsPos(digits), m_resolution(resolution)
{

}

A429BcdWord::~A429BcdWord()
{

}

bool A429BcdWord::isSigned() const
{
    return m_isSigned;
}

void A429BcdWord::setIsSigned(const bool value)
{
    m_isSigned = value;
}

ushort A429BcdWord::signBit() const
{
    return m_signBit;
}

void A429BcdWord::setSignBit(const ushort bitNumber)
{
    m_signBit = bitNumber;
}

float A429BcdWord::resolution() const
{
    return m_resolution;
}

void A429BcdWord::setResolution(const float value)
{
    m_resolution = value;
}

DigitsVec A429BcdWord::digitsPositions() const
{
    return m_digitsPos;
}

void A429BcdWord::setDigitsPositions(const DigitsVec digits)
{
    m_digitsPos = digits;
}

void A429BcdWord::declareDigit(DigitConfig pos)
{
    // TODO: check a digit is already declared on this position
    m_digitsPos.push_back(pos);
}

void A429BcdWord::resetDigitsConfig()
{
    if (m_digitsPos.empty()) return;
    m_digitsPos.clear();
}

double A429BcdWord::value() const
{
    double tmp = 0.0;
    for(int i=m_digitsPos.size()-1; i>=0; --i)
    {
        uint digitValue = getBitRange(m_digitsPos[i].first, m_digitsPos[i].second);
        tmp += digitValue * std::pow(10, (m_digitsPos.size() - (i+1)));
    }
    return tmp * m_resolution;
}
