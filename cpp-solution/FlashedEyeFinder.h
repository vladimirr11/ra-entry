#ifndef FLASHEDEYEFINDER_H
#define FLASHEDEYEFINDER_H

#include <cstdint>
#include <vector>

#include "utils/Image.h"
#include "utils/EyePatterns.h"

constexpr int32_t RED_CHANNEL_TARGET_VALUE = 200;
constexpr int32_t REDUCE_CONSTANT = 150;
using FlashedEyesStorage = std::vector<std::vector<int32_t>>;

enum PatternType : uint8_t {
    PATTERN_1, 
    PATTERN_2, 
    PATTERN_3, 
    PATTERN_4, 

    UNKNOWN_PATTERN
};

class FlashedEyeFinder {
public:
    FlashedEyeFinder() = delete;

    FlashedEyeFinder(StrideImage& image) 
        : _image{image}, _pixelsIndices{}, _storage{} {}

    std::vector<int32_t> findFlashedEye(const EyePattern& eye_pattern, int32_t start_idx);
    
    PatternType quickFlashedEyePatternFinder(const int32_t start_idx) const;

    bool isStartOrEndOfEye(const StrideImage& image, int32_t curr_pos) const;

    void storeEyePattern(const std::vector<int32_t>& eye_vec);

    void clearEyes();

private:
    StrideImage& _image;
    std::vector<int32_t> _pixelsIndices;
    FlashedEyesStorage _storage;
};

#endif // !FLASHEDEYEFINDER_H
