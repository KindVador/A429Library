#ifndef A429BCDWORD_HPP
#define A429BCDWORD_HPP

#include "a429word.hpp"
#include <vector>

using DigitConfig = std::pair<ushort, ushort>;
using DigitsVec = std::vector<DigitConfig>;

class A429BcdWord : public A429Word {

public:
    // CONSTRUCTORS
    A429BcdWord();
    A429BcdWord(uint value, DigitsVec  digits, bool labelNumberMsbFirst=true, bool oddParity=true, const float& resolution=1.0);
    A429BcdWord(const std::string& value, DigitsVec  digits, bool labelNumberMsbFirst=true, int base=16, bool oddParity=true, const float& resolution=1.0);
    A429BcdWord(DigitsVec  digits, const float& resolution);

    // DESTRUCTOR
    ~A429BcdWord() override = default;

    // GETTERS & SETTERS
    float resolution() const;
    void setResolution(float value);

    DigitsVec digitsPositions() const;
    void setDigitsPositions(const DigitsVec &digits);

    // METHODS
    void declareDigit(DigitConfig pos);
    void resetDigitsConfig();
    double value() const;

private:
    float m_resolution = 1.0;
    DigitsVec m_digitsPos; 
};

#endif // A429BCDWORD_HPP