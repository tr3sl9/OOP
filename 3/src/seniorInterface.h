#ifndef SENIOR_INTERFACE_H
#define SENIOR_INTERFACE_H

#include <string>

class ERWProvider {
    public:
        virtual std::string getERWName() const = 0;
        virtual void setERWName(const std::string& ERW) noexcept = 0;
        virtual void setPlace(const std::string& placeERW) noexcept = 0;
        virtual std::string getPlaceERW() const = 0;
};

#endif