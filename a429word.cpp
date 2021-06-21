#include "a429word.hpp"
#include <algorithm>
#include <stdexcept>
#include <bitset>

A429Word::A429Word()
{

}

A429Word::A429Word(uint value, bool labelNumberMsbFirst, bool oddParity)
{
    setRawValue(value);
    setLabelNumberMsbFirst(labelNumberMsbFirst);
    m_isOddParity = oddParity;
}

A429Word::A429Word(std::string value, bool labelNumberMsbFirst, int base, bool oddParity)
{
    setRawValue(std::stoul(value,nullptr,base));
    setLabelNumberMsbFirst(labelNumberMsbFirst);
    m_isOddParity = oddParity;
}

A429Word::~A429Word()
{

}

uint A429Word::rawValue() const
{
    return m_rawValue;
}

void A429Word::setRawValue(uint rawValue)
{
    if (rawValue > 4294967295UL) {
        throw std::out_of_range("Raw value should be lower than 4294967295 (decimal base)");
    }
    m_rawValue = rawValue;
}

ushort A429Word::labelNumber() const
{
    return m_rawValue & LABEL_MASK;
}

void A429Word::setLabelNumber(ushort labelNumber)
{
    if (labelNumber > 255UL) {
        throw std::out_of_range("Label Number should be lower than 255 (decimal base)");     // value must be between 0 and 255
    }
    m_rawValue = m_rawValue & ~LABEL_MASK;         // set all LABEL bits to 0
    m_rawValue = m_rawValue | labelNumber;
}

ushort A429Word::sdi() const
{
    return (m_rawValue & SDI_MASK) >> 8;
}

void A429Word::setSdi(ushort sdi)
{
    if (sdi > 3UL) {
        throw std::out_of_range("SDI value should be lower than 3 (decimal base)");
    }
    m_rawValue = m_rawValue & ~SDI_MASK;         // set all SDI bits to 0
    m_rawValue = m_rawValue | (sdi << 8);
}

uint A429Word::payload() const
{
    return (m_rawValue & PAYLOAD_MASK) >> 10;
}

void A429Word::setPayload(uint payload)
{
    if (payload > 524287UL) {
        throw std::out_of_range("Payload value should be lower than 524287 (decimal base)");
    }
    m_rawValue = m_rawValue & ~PAYLOAD_MASK;         // set all PAYLOAD bits to 0
    m_rawValue = m_rawValue | (payload << 10);
}

ushort A429Word::ssm() const
{
    return (m_rawValue & SSM_MASK) >> 29;
}

void A429Word::setSsm(ushort ssm)
{
    if (ssm > 3UL) {
        throw std::out_of_range("Payload value should be lower than 524287 (decimal base)");
    }
    m_rawValue = m_rawValue & ~SSM_MASK;         // set all SSM bits to 0
    m_rawValue = m_rawValue | (ssm << 29);
}

bool A429Word::parity() const
{
    return (m_rawValue & PARITY_MASK) >> 31;
}

void A429Word::setParity(bool parity)
{
    if (parity) {
        m_rawValue = m_rawValue | PARITY_MASK;
    }
    else {
        m_rawValue = m_rawValue & ~PARITY_MASK;
    }
}

bool A429Word::labelNumberMsbFirst() const
{
    return m_labelNumberMsbFirst;
}

void A429Word::setLabelNumberMsbFirst(bool value)
{
    m_labelNumberMsbFirst = value;
}

bool A429Word::isOddParity() const
{
    return m_isOddParity;
}

void A429Word::setIsOddParity(const bool value)
{
    m_isOddParity = value;
}

std::string A429Word::getLabelAsBinaryString(const bool &msbFirst)
{
    if (m_labelNumberMsbFirst && msbFirst) {
        return std::bitset<8>(this->labelNumber()).to_string();
    } else if ((m_labelNumberMsbFirst && !msbFirst) || (!m_labelNumberMsbFirst && msbFirst)) {
        std::string s = std::bitset<8>(this->labelNumber()).to_string();
        std::reverse(s.begin(), s.end());   // reverse QString
        return s;
    } else {
        return std::bitset<8>(this->labelNumber()).to_string();
    }
}

bool A429Word::getBit(const ushort &bitNumber) const
{
    if (bitNumber > 32) {
        throw std::out_of_range("Bit number value should be lower than 33 (decimal base)");
    }
    uint mask = 1UL << (bitNumber -1 );
    bool bitValue = (m_rawValue & mask) >> (bitNumber -1 );

    return bitValue;
}

void A429Word::setBit(const ushort &bitNumber, const bool &value)
{
    if (bitNumber > 32) {
        throw std::out_of_range("Bit number value should be lower than 33 (decimal base)");
    }
    uint mask = 4294967295UL ^ (1 << (bitNumber - 1));
    m_rawValue = (m_rawValue & mask) | (value << (bitNumber - 1));
}

std::string A429Word::toBinaryString() const
{
    return std::bitset<32>(m_rawValue).to_string();
}

std::string A429Word::getLabelAsOctalString() const
{
    if (m_labelNumberMsbFirst) {
        std::string labelString = std::bitset<8>(this->labelNumber()).to_string();
        std::reverse(labelString.begin(), labelString.end());
        ushort labelInt = std::stoi(labelString, nullptr, 2);
        char buffer[4];
        sprintf(buffer, "%03o", labelInt);
        return std::string(buffer);
    } else {
        char buffer[4];
        sprintf(buffer, "%03o", this->labelNumber());
        return std::string(buffer);
    }
    
}

double A429Word::getBnrValue(const bool &isSigned, const ushort &bitSign, const ushort &msbPos, const ushort &lsbPos, const double &resolution)
{    
    long long maskMsbLsb = ((1 << msbPos) - 1) & (~((1 << (lsbPos - 1)) - 1));
    if (isSigned) {
        if ((m_rawValue & (1 << (bitSign - 1))) >> (bitSign - 1) == 1) {
            // Negative input
            // (leading ‘1’ bit): Convert to decimal, getting a positive number, then subtract 2^numBits.
            return (((m_rawValue & maskMsbLsb) >> (lsbPos - 1)) - (1 << ((msbPos - lsbPos) + 1))) * resolution;
        } else {
            // Non-negative input (leading ‘0’ bit): Simply convert to decimal.
            return ((m_rawValue & maskMsbLsb) >> (lsbPos - 1)) * resolution;
        }
    } else {
        // Non-negative input (leading ‘0’ bit): Simply convert to decimal.
        return ((m_rawValue & maskMsbLsb) >> (lsbPos - 1)) * resolution;
    }
}

bool A429Word::isParityValid() const
{
    if ((std::bitset<32>(m_rawValue).count() % 2) == m_isOddParity) {
        return true;
    } else {
        return false;
    }
}

void A429Word::toggleBit(const ushort &bitNumber)
{
    if (bitNumber > 32) {
        throw std::out_of_range("Bit number value should be lower than 33 (decimal base)");
    }
    m_rawValue ^=  (1UL << (bitNumber - 1));
    setRawValue(m_rawValue);
}

uint A429Word::getBitRange(const ushort& msbPos, const ushort& lsbPos) const
{
    if (msbPos > 32 || lsbPos > 32) {
        throw std::out_of_range("MSB or LSB position should be lower than 33 (decimal base)");
    } else if (msbPos < lsbPos)
    {
        throw std::range_error("MSB position should be greate ot equal to LSB position");
    }
    long long maskMsbLsb = ((1 << msbPos) - 1) & (~((1 << (lsbPos - 1)) - 1));
    return (m_rawValue & maskMsbLsb) >> (lsbPos - 1);
}

std::ostream& operator<<(std::ostream& os, const A429Word& item)
{
    os << item.parity() << " " << item.ssm() << " " << item.payload() << " " << item.sdi() << " " << item.getLabelAsOctalString();
    return os;
}

bool operator==(const A429Word& lhs, const A429Word& rhs)
{
    return lhs.rawValue() == rhs.rawValue() && lhs.labelNumberMsbFirst() == rhs.labelNumberMsbFirst() && lhs.isOddParity() == rhs.isOddParity();
}

bool operator!=(const A429Word& lhs, const A429Word& rhs)
{
    return !(lhs == rhs);
}