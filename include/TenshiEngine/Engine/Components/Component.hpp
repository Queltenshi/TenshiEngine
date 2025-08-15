#pragma once

#include <iostream>

namespace te{
namespace components{

struct Component{
public:
    Component() = default;

    virtual std::string toString() const = 0;
    virtual std::string name() const = 0;
};

}
}
