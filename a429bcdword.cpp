#include "a429bcdword.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <utility>

A429BcdWord::A429BcdWord(): A429Word()
{

}

A429BcdWord::A429BcdWord(uint value, DigitsVec  digits, bool labelNumberMsbFirst, bool oddParity, const float& resolution):
    A429Word(value, labelNumberMsbFirst, oddParity), m_digitsPos(std::move(digits)), m_resolution(resolution)
{

}

A429BcdWord::A429BcdWord(const std::string& value, DigitsVec  digits, bool labelNumberMsbFirst, int base, bool oddParity, const float& resolution):
    A429Word(value, labelNumberMsbFirst, base, oddParity), m_digitsPos(std::move(digits)), m_resolution(resolution)
{

}

A429BcdWord::A429BcdWord(DigitsVec  digits, const float& resolution): A429Word(), m_digitsPos(std::move(digits)), m_resolution(resolution)
{

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

void A429BcdWord::setDigitsPositions(const DigitsVec &digits)
{
    m_digitsPos = digits;
}

void A429BcdWord::declareDigit(DigitConfig pos)
{
    // check if digit is already declared
    if(std::find(m_digitsPos.cbegin(), m_digitsPos.cend(), pos) != m_digitsPos.cend())
    {
        // digit is already in the vector
        return;
    } else {
        // check if digit is superposed with another one
        for(DigitConfig digitPos : m_digitsPos) {
            if(digitPos.first == pos.first || digitPos.first == pos.second
            || digitPos.second == pos.first || digitPos.second == pos.second)
                throw std::range_error("Superposition of one Digit");
        }
        
        // we add the digit to the vector
        m_digitsPos.push_back(pos);

    }
}

void A429BcdWord::resetDigitsConfig()
{
    if (m_digitsPos.empty()) return;
    m_digitsPos.clear();
}

double A429BcdWord::value() const
{
    double tmp = 0.0;
    for(size_t i=m_digitsPos.size()-1; i>=0; --i)
    {
        std::cout << i << std::endl;
        uint digitValue = getBitRange(m_digitsPos[i].first, m_digitsPos[i].second);
        tmp += digitValue * std::pow(10, (m_digitsPos.size() - (i+1)));
    }
    return tmp * m_resolution;
}
