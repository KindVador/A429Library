#include "a429bnrword.hpp"

A429BnrWord::A429BnrWord(): A429Word()
{

}

A429BnrWord::A429BnrWord(bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution) : A429Word(), m_isSigned(isSigned), 
                m_signBitPosition(signBitPos), m_msbBitPosition(msbBitPos), m_lsbBitPosition(lsbBitPos), m_resolution(resolution)
{

}

A429BnrWord::A429BnrWord(uint value, bool labelNumberMsbFirst, bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution): 
                A429Word(value, labelNumberMsbFirst), m_isSigned(isSigned), m_signBitPosition(signBitPos), m_msbBitPosition(msbBitPos), m_lsbBitPosition(lsbBitPos), m_resolution(resolution)
{

}

A429BnrWord::A429BnrWord(const std::string& value, bool labelNumberMsbFirst, int base, bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution):
                A429Word(value, labelNumberMsbFirst, base), m_isSigned(isSigned), m_signBitPosition(signBitPos), m_msbBitPosition(msbBitPos), m_lsbBitPosition(lsbBitPos), m_resolution(resolution)
{

}

bool A429BnrWord::isSigned() const
{
    return m_isSigned;
}

void A429BnrWord::setIsSigned(const bool value)
{
    m_isSigned = value;
}

ushort A429BnrWord::signBitPosition() const
{
    return m_signBitPosition;
}

void A429BnrWord::setSignBitPosition(const ushort position)
{
    m_signBitPosition = position;
}

ushort A429BnrWord::msbBitPosition() const
{
    return m_msbBitPosition;
}

void A429BnrWord::setMsbBitPosition(const ushort position)
{
    m_msbBitPosition = position;
}

ushort A429BnrWord::lsbBitPosition() const
{
    return m_lsbBitPosition;
}

void A429BnrWord::setLsbBitPosition(const ushort position)
{
    m_lsbBitPosition = position;
}

double A429BnrWord::resolution() const
{
    return m_resolution;
}

void A429BnrWord::setResolution(const double value)
{
    m_resolution = value;
}

double A429BnrWord::getIndustrialValue()
{
    return getBnrValue(m_isSigned, m_signBitPosition, m_msbBitPosition, m_lsbBitPosition, m_resolution);
}
