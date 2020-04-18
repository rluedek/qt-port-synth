#ifndef IPARAM_H
#define IPARAM_H

class Param
{
public:

    Param(float fMinValue, float fMaxValue, float fDefaultValue);

    float getValue();
    void setValue(float);

    float getMinValue();
    void setMinValue(float fMinValue);
    
    float getMaxValue();
    void setMaxValue(float fMaxValue);

protected:

    float   m_fValue;
    float   m_fMinValue;
    float   m_fMaxValue;
};

#endif