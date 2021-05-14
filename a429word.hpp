#ifndef A429WORD_HPP
#define A429WORD_HPP

#include <string>

#define LABEL_MASK 255UL
#define SDI_MASK 768UL
#define PAYLOAD_MASK 536869888UL
#define SSM_MASK 1610612736UL
#define PARITY_MASK 2147483648UL
#define EVEN_PARITY 0
#define ODD_PARITY 1

using uint = unsigned int;
using ushort = unsigned short;

class A429Word
{
public:
    // CONSTRUCTORS
    A429Word();
    A429Word(uint value, bool labelNumberMsbFirst=true);
    A429Word(std::string value, bool labelNumberMsbFirst=true, int base=16);

    // GETTERS & SETTERS
    uint rawValue() const;
    void setRawValue(uint rawValue);

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

    bool labelNumberMsbFirst() const;
    void setLabelNumberMsbFirst(bool value);

    // METHODS
    std::string getLabelAsBinaryString(const bool &msbFirst);
    bool getBit(const ushort &bitNumber);
    void setBit(const ushort &bitNumber, const bool &value);
    std::string toBinaryString();
    std::string getLabelAsOctalString();
    double getBnrValue(const bool &isSigned, const ushort &bitSign, const ushort &msbPos, const ushort &lsbPos, const double &resolution);
    bool isParityValid();
    void toggleBit(const ushort& bitNumber);

private:
    uint m_rawValue = 0;
    ushort m_labelNumber = 0;
    ushort m_sdi = 0;
    uint m_payload = 0;
    ushort m_ssm = 0;
    bool m_parity = 0;
    bool m_labelNumberMsbFirst = true;
};

#endif // A429WORD_HPP
