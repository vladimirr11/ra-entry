#ifndef COMMONDEFINES_H_
#define COMMONDEFINES_H_

#include <cstdint>

struct Resolution {
    bool operator==(const Resolution& other) const {
        return (width == other.width) && (height == other.height);
    }

    int32_t width{};
    int32_t height{};
};

struct Pixel {
    bool operator==(const Pixel& other) const {
        return (red == other.red) && (green == other.green) &&
               (blue == other.blue) && (alpha == other.alpha);
    }

    uint8_t red{};
    uint8_t green{};
    uint8_t blue{};
    uint8_t alpha{};
};

#endif /* COMMONDEFINES_H_ */
