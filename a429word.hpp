#ifndef A429WORD_H
#define A429WORD_H

#include <string>

#define LABEL_MASK 255UL
#define SDI_MASK 768UL
#define PAYLOAD_MASK 536869888UL
#define SSM_MASK 1610612736UL
#define PARITY_MASK 214748364UL
#define EVEN_PARITY 0
#define ODD_PARITY 1

class A429Word
{
public:
    // CONSTRUCTORS
    A429Word();
    A429Word(unsigned int value, bool labelNumberMsbFirst=true);
    A429Word(std::string value, bool labelNumberMsbFirst=true, int base=16);

    // GETTERS & SETTERS
    unsigned int rawValue() const;
    void setRawValue(unsigned int rawValue);

    unsigned short labelNumber() const;
    void setLabelNumber(unsigned short labelNumber);

    unsigned short sdi() const;
    void setSdi(unsigned short sdi);

    unsigned int payload() const;
    void setPayload(unsigned int payload);

    unsigned short ssm() const;
    void setSsm(unsigned short ssm);

    bool parity() const;
    void setParity(bool parity);

    bool labelNumberMsbFirst() const;
    void setLabelNumberMsbFirst(bool value);

    // METHODS
    std::string getLabelAsBinaryString(const bool &msbFirst);
    bool getBit(const unsigned short &bitNumber);
    void setBit(const unsigned short &bitNumber, const bool &value);
    std::string toBinaryString();
    std::string getLabelAsOctalString();
    double getBnrValue(const bool &isSigned, const unsigned short &bitSign, const unsigned short &msbPos, const unsigned short &lsbPos, const double &resolution);
    bool isParityValid();
    void toggleBit(const unsigned short& bitNumber);

private:
    unsigned int m_rawValue = 0;
    unsigned short m_labelNumber = 0;
    unsigned short m_sdi = 0;
    unsigned int m_payload = 0;
    unsigned short m_ssm = 0;
    bool m_parity = 0;
    bool m_labelNumberMsbFirst = true;
};

#endif // A429WORD_H
