#include "a429bnrword.hpp"

A429BnrWord::A429BnrWord()
{

}

A429BnrWord::A429BnrWord(bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution) : m_isSigned(isSigned), 
                m_signBitPosition(signBitPos), m_msbBitPosition(msbBitPos), m_lsbBitPosition(lsbBitPos), m_resolution(resolution)
{

}

A429BnrWord::A429BnrWord(uint value, bool labelNumberMsbFirst, bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution): 
                A429Word(value, labelNumberMsbFirst), m_isSigned(isSigned), m_signBitPosition(signBitPos), m_msbBitPosition(msbBitPos), m_lsbBitPosition(lsbBitPos), m_resolution(resolution)
{

}

A429BnrWord::A429BnrWord(std::string value, bool labelNumberMsbFirst, int base, bool isSigned, ushort signBitPos, ushort msbBitPos, ushort lsbBitPos, double resolution):
                A429Word(value, labelNumberMsbFirst, base), m_isSigned(isSigned), m_signBitPosition(signBitPos), m_msbBitPosition(msbBitPos), m_lsbBitPosition(lsbBitPos), m_resolution(resolution)
{

}

A429BnrWord::~A429BnrWord()
{

}