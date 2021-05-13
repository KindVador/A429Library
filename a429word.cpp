#include "a429word.hpp"
#include <algorithm>
#include <stdexcept>
#include <bitset>

A429Word::A429Word()
{

}

A429Word::A429Word(unsigned int value, bool labelNumberMsbFirst)
{
    setRawValue(value);
    setLabelNumberMsbFirst(labelNumberMsbFirst);
}

A429Word::A429Word(std::string value, bool labelNumberMsbFirst, int base)
{
    setRawValue(std::stoul(value,nullptr,16));
    setLabelNumberMsbFirst(labelNumberMsbFirst);
}

unsigned int A429Word::rawValue() const
{
    return m_rawValue;
}

void A429Word::setRawValue(unsigned int rawValue)
{
    if (rawValue > 4294967295UL) {
        throw std::out_of_range("Raw value should be lower than 4294967295 (decimal base)");
    }
    m_rawValue = rawValue;
    // update others fields
    m_labelNumber = m_rawValue & LABEL_MASK;
    m_sdi = (m_rawValue & SDI_MASK) >> 8;
    m_payload = (m_rawValue & PAYLOAD_MASK) >> 10;
    m_ssm = (m_rawValue & SSM_MASK) >> 29;
    m_parity = (m_rawValue & PARITY_MASK) >> 31;
}

unsigned short A429Word::labelNumber() const
{
    return m_labelNumber;
}

void A429Word::setLabelNumber(unsigned short labelNumber)
{
    if (labelNumber > 255UL) {
        throw std::out_of_range("Label Number should be lower than 255 (decimal base)");     // value must be between 0 and 255
    }
    m_labelNumber = labelNumber & LABEL_MASK;
    m_rawValue = m_rawValue & ~LABEL_MASK;         // set all LABEL bits to 0
    m_rawValue = m_rawValue & m_labelNumber;
}

unsigned short A429Word::sdi() const
{
    return m_sdi;
}

void A429Word::setSdi(unsigned short sdi)
{
    if (sdi > 3UL) {
        throw std::out_of_range("SDI value should be lower than 3 (decimal base)");
    }
    m_sdi = sdi;
    m_rawValue = m_rawValue & ~SDI_MASK;         // set all SDI bits to 0
    m_rawValue = m_rawValue & m_sdi;
}

unsigned int A429Word::payload() const
{
    return m_payload;
}

void A429Word::setPayload(unsigned int payload)
{
    if (payload > 524287UL) {
        throw std::out_of_range("Payload value should be lower than 524287 (decimal base)");
    }
    m_payload = payload;
    m_rawValue = m_rawValue & ~PAYLOAD_MASK;         // set all PAYLOAD bits to 0
    m_rawValue = m_rawValue & m_payload;
}

unsigned short A429Word::ssm() const
{
    return m_ssm;
}

void A429Word::setSsm(unsigned short ssm)
{
    if (ssm > 3UL) {
        throw std::out_of_range("Payload value should be lower than 524287 (decimal base)");
    }
    m_ssm = ssm;
    m_rawValue = m_rawValue & ~SSM_MASK;         // set all SSM bits to 0
    m_rawValue = m_rawValue & m_ssm;
}

bool A429Word::parity() const
{
    return m_parity;
}

void A429Word::setParity(bool parity)
{
    m_parity = parity;
    if (m_parity) {
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

std::string A429Word::getLabelAsBinaryString(const bool &msbFirst)
{
    if (m_labelNumberMsbFirst && msbFirst) {
        return std::bitset<8>(m_labelNumber).to_string();
    } else if ((m_labelNumberMsbFirst && !msbFirst) || (!m_labelNumberMsbFirst && msbFirst)) {
        std::string s = std::bitset<8>(m_labelNumber).to_string();
        std::reverse(s.begin(), s.end());   // reverse QString
        return s;
    } else {
        return std::bitset<8>(m_labelNumber).to_string();
    }
}

bool A429Word::getBit(const unsigned short &bitNumber)
{
    if (bitNumber > 32) {
        throw std::out_of_range("Bit number value should be lower than 33 (decimal base)");
    }
    unsigned int mask = 1UL << (bitNumber -1 );
    bool bitValue = (m_rawValue & mask) >> (bitNumber -1 );

    return bitValue;
}

void A429Word::setBit(const unsigned short &bitNumber, const bool &value)
{
    if (bitNumber > 32) {
        throw std::out_of_range("Bit number value should be lower than 33 (decimal base)");
    }
    unsigned int mask = 4294967295UL ^ (1 << (bitNumber - 1));
    m_rawValue = (m_rawValue & mask) | (value << (bitNumber - 1));
}

std::string A429Word::toBinaryString()
{
    return std::bitset<32>(m_rawValue).to_string();
}

std::string A429Word::getLabelAsOctalString()
{
    if (m_labelNumberMsbFirst) {
        std::string labelString = std::bitset<8>(m_labelNumber).to_string();
        std::reverse(labelString.begin(), labelString.end());
        unsigned short labelInt = std::stoi(labelString, nullptr, 2);
        char buffer[4];
        int n = sprintf(buffer, "%03o", labelInt);
        return std::string(buffer);
    } else {
        char buffer[4];
        int n = sprintf(buffer, "%03o", m_labelNumber);
        return std::string(buffer);
    }
    
}

double A429Word::getBnrValue(const bool &isSigned, const unsigned short &bitSign, const unsigned short &msbPos, const unsigned short &lsbPos, const double &resolution)
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

bool A429Word::isParityValid()
{
    int nbBitSet = static_cast<int>(std::bitset<32>(m_rawValue).count());
    if ((std::bitset<32>(m_rawValue & ~PARITY_MASK).count() % 2) == m_parity) {
        return false;
    } else {
        return true;
    }
}

void A429Word::toggleBit(const unsigned short &bitNumber)
{
    if (bitNumber > 32) {
        throw std::out_of_range("Bit number value should be lower than 33 (decimal base)");
    }
    m_rawValue ^=  (1UL << (bitNumber - 1));
    setRawValue(m_rawValue);
}
