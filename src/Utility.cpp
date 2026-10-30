#include "Utility.hpp"
#include <cmath>
float roundToSecond(const float& number) {
    float rounded = std::round(number * 10);
    float result = 0.0f;
    if (number < 0) {
        int remainder = static_cast<int>(-rounded)%10;
        result = static_cast<float>(static_cast<int>(rounded)/10);
        if (remainder > 3 && remainder < 7) 
        {
            result -= 0.5f;
        } 
        else if (remainder >= 7) 
        {
            result -= 1.0f;
        }
    }
    else if (number > 0) {
        int remainder = static_cast<int>(rounded)%10;
        result = static_cast<float>(static_cast<int>(rounded)/10);
        if (remainder > 3 && remainder < 7) 
        {
            result += 0.5f;
        } 
        else if (remainder >= 7) 
        {
            result += 1.0f;
        }
    }
    return result;
}

Vector3 divideVector3(const Vector3& value, const float scalar)
{
    return {value.x / scalar, value.y / scalar, value.z / scalar};
}