#ifndef A429WORD_HPP
#define A429WORD_HPP

#include <string>
#include <iostream>

#define LABEL_MASK 255UL
#define SDI_MASK 768UL
#define PAYLOAD_MASK 536869888UL
#define SSM_MASK 1610612736UL
#define PARITY_MASK 2147483648UL

using uint = unsigned int;
using ushort = unsigned short;

class A429Word
{
    friend std::ostream& operator<<(std::ostream& os, const A429Word& item);
    friend bool operator==(const A429Word& lhs, const A429Word& rhs);
    friend bool operator!=(const A429Word& lhs, const A429Word& rhs);

public:
    // CONSTRUCTORS
    A429Word();
    A429Word(uint value, bool labelNumberMsbFirst=true, bool oddParity=true);
    A429Word(std::string value, bool labelNumberMsbFirst=true, int base=16, bool oddParity=true);

    // DESTRUCTOR
    virtual ~A429Word();

    // OPERATORS
    bool operator[](std::size_t n) { return getBit(n); }
    const bool operator[](std::size_t n) const { return getBit(n); }
    
    // GETTERS & SETTERS
    uint rawValue() const;
    void setRawValue(uint rawValue);

    bool labelNumberMsbFirst() const;
    void setLabelNumberMsbFirst(bool value);

    bool isOddParity() const;
    void setIsOddParity(const bool value);

    // METHODS
    ushort labelNumber() const;
    void setLabelNumber(ushort labelNumber);

    ushort sdi() const;
    void setSdi(ushort sdi);

    uint payload() const;
    void setPayload(uint payload);

    ushort ssm() const;
    void setSsm(ushort ssm);

    bool parity() const;
    void setParity(bool parity);
    
    std::string getLabelAsBinaryString(const bool &msbFirst);
    bool getBit(const ushort &bitNumber) const;
    void setBit(const ushort &bitNumber, const bool &value);
    std::string toBinaryString() const;
    std::string getLabelAsOctalString() const;
    double getBnrValue(const bool &isSigned, const ushort &bitSign, const ushort &msbPos, const ushort &lsbPos, const double &resolution);
    bool isParityValid() const;
    void toggleBit(const ushort& bitNumber);
    uint getBitRange(const ushort& msbPos, const ushort& lsbPos) const;

private:
    uint m_rawValue = 0;
    bool m_labelNumberMsbFirst = true;
    bool m_isOddParity = true;
};

std::ostream& operator<<(std::ostream& os, const A429Word& item);
bool operator==(const A429Word& lhs, const A429Word& rhs);
bool operator!=(const A429Word& lhs, const A429Word& rhs);

#endif // A429WORD_HPP