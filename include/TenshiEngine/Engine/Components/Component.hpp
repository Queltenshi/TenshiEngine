#pragma once

#include <iostream>
#include <string>
#include "TenshiEngine/Engine/Utils/boolToString.hpp"

namespace te{
namespace components{

/**
 * @brief Base component
 */
struct Component{
public:
    /**
     * @brief Constructor
     *
     * Creates a component
     */
    Component() = default;
    
    /**
     * @brief shows data as a string
     *
     * converts the data into a string,
     * components do override this method
     */
    virtual std::string toString() const = 0;
};

}
}
