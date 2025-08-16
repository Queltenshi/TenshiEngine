#pragma once

#include <string>

namespace te{
namespace utils{

/**
 * @brief converts boolean to string
 *
 * converts the given boolean to a string
 *
 * @param boolean boolean to conver
 */
inline std::string boolToString(bool boolean){
    if(boolean)
        return "true";
    return "false";
};

}
}
