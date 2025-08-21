#pragma once

#include <string>
#include "TenshiEngine/Engine/Components/Component.hpp"

namespace te{
namespace components{

/**
 * @brief component with grounded state
 *
 * checks if the entity is grounded or not
 */
struct Grounded : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component
     */
    Grounded() = default;

    std::string toString() const override{
        return "(state: " + utils::boolToString(isGrounded) + ")";
    };

    ///state of grounded
    bool isGrounded = false;

    ///Name of component
    inline static const std::string name = "Grounded";
};

}
}
