#ifndef MIN_MAX_H
#define MIN_MAX_H

#include "Random.h"

template<class T>
class MinMax
{
public:
    MinMax(const T& minValue, const T& maxValue)
        : minValue(minValue), maxValue(maxValue) {}

    bool IsInRange(const T& value) const
    {
        return value >= minValue && value <= maxValue;
    }

    bool IsInRangeExclusive(const T& value) const
    {
        return value > minValue && value < maxValue;
    }

    virtual T GetRandomValue() const = 0;
    virtual T Lerp(float t) const = 0;
    
    //setter
    void SetMinValue(const T& value) { minValue = value; }
    void SetMaxValue(const T& value) { maxValue = value; }
    
    //getter
    T GetMinValue() const { return minValue; }
    T GetMaxValue() const { return maxValue; }

private:
    T minValue;
    T maxValue;
};


class MinMaxInt : public MinMax<int>
{
public:
    MinMaxInt(int minValue, int maxValue)
        : MinMax<int>(minValue, maxValue) {}
    int GetRandomValue() const override
    {
        return Random::GetInstance().RandomRange(GetMinValue(), GetMaxValue());
    }
    int Lerp(float t) const override
    {
        return static_cast<int>(GetMinValue() + t * (GetMaxValue() - GetMinValue()));
    }
};

class MinMaxFloat : public MinMax<float>
{
public:
    MinMaxFloat(float minValue, float maxValue)
        : MinMax<float>(minValue, maxValue) {}
    float GetRandomValue() const override
    {
        return Random::GetInstance().RandomRange(GetMinValue(), GetMaxValue());
    }
    float Lerp(float t) const override
    {
        return GetMinValue() + t * (GetMaxValue() - GetMinValue());
    }
};

class MinMaxDouble : public MinMax<double>
{
public:
    MinMaxDouble(double minValue, double maxValue)
        : MinMax<double>(minValue, maxValue) {}
    double GetRandomValue() const override
    {
        return Random::GetInstance().RandomRange(GetMinValue(), GetMaxValue());
    }
    double Lerp(float t) const override
    {
        return GetMinValue() + t * (GetMaxValue() - GetMinValue());
    }
};

#endif // MIN_MAX_H