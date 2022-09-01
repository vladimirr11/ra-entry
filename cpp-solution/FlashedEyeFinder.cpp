#include "FlashedEyeFinder.h"

std::vector<int32_t> FlashedEyeFinder::findFlashedEye(const EyePattern& eye_pattern, int32_t start_idx) {
    for (int32_t r = 0; r < eye_pattern.size(); ++r) {
        for (int32_t c = 0; c < EYE_PATTERN_COL_SIZE; ++c) {
            if (_image.redPixels[start_idx++] >= RED_CHANNEL_TARGET_VALUE && eye_pattern[r][c] != ' ') {
                _pixelsIndices.push_back(start_idx);
            }
        }

        start_idx += _image.resolution.width - EYE_PATTERN_COL_SIZE;
    }
    
    if (_pixelsIndices.size() < MIN_EYE_PATTERN_LENGTH) {
        _pixelsIndices.clear();
    }

    return _pixelsIndices;
}

PatternType FlashedEyeFinder::quickFlashedEyePatternFinder(int32_t start_idx) const {
    const int32_t sanity_ckeck_idx_1 = start_idx + _image.resolution.width + 2; // offset of row 1 == col 2
    const int32_t sanity_ckeck_idx_2 = start_idx + (_image.resolution.width * 2) + 1; // offset of row 2 == col 1
    const int32_t sanity_ckeck_idx_3 = start_idx + (_image.resolution.width * 3) + 2; // offset of row 3 == col 2
    const int32_t sanity_ckeck_idx_4 = start_idx + (_image.resolution.width * 2) + 3; // offset of row 2 == col 3

    if (_image.redPixels[sanity_ckeck_idx_1] < RED_CHANNEL_TARGET_VALUE && 
        _image.redPixels[sanity_ckeck_idx_2] >= RED_CHANNEL_TARGET_VALUE &&
        _image.redPixels[sanity_ckeck_idx_3] < RED_CHANNEL_TARGET_VALUE &&
        _image.redPixels[sanity_ckeck_idx_4] >= RED_CHANNEL_TARGET_VALUE) {

        return PATTERN_1;

    } else if ( _image.redPixels[sanity_ckeck_idx_1] >= RED_CHANNEL_TARGET_VALUE && 
                _image.redPixels[sanity_ckeck_idx_2] < RED_CHANNEL_TARGET_VALUE &&
                _image.redPixels[sanity_ckeck_idx_3] >= RED_CHANNEL_TARGET_VALUE &&
                _image.redPixels[sanity_ckeck_idx_4] < RED_CHANNEL_TARGET_VALUE) { 

        return PATTERN_2;
    
    } else if (_image.redPixels[sanity_ckeck_idx_1] >= RED_CHANNEL_TARGET_VALUE && 
               _image.redPixels[sanity_ckeck_idx_2] >= RED_CHANNEL_TARGET_VALUE &&
               _image.redPixels[sanity_ckeck_idx_3] >= RED_CHANNEL_TARGET_VALUE &&
               _image.redPixels[sanity_ckeck_idx_4] >= RED_CHANNEL_TARGET_VALUE) {
        
        return PATTERN_3;
    
    } else if (_image.redPixels[sanity_ckeck_idx_1] < RED_CHANNEL_TARGET_VALUE && 
               _image.redPixels[sanity_ckeck_idx_2] < RED_CHANNEL_TARGET_VALUE &&
               _image.redPixels[sanity_ckeck_idx_3] < RED_CHANNEL_TARGET_VALUE &&
               _image.redPixels[sanity_ckeck_idx_4] < RED_CHANNEL_TARGET_VALUE) {
        
        return PATTERN_4;
    }

    return UNKNOWN_PATTERN;
}

bool FlashedEyeFinder::isStartOrEndOfEye(const StrideImage& image, int32_t curr_pos) const {
    int32_t counter{};
    for (int32_t i = 0; i < EYE_PATTERN_COL_SIZE; ++i) {
        if (image.redPixels[curr_pos + i] >= RED_CHANNEL_TARGET_VALUE) {
            ++counter;
        }
    }

    return counter == EYE_PATTERN_COL_SIZE ? true : false;
}

void FlashedEyeFinder::storeEyePattern(const std::vector<int32_t>& eye_vec) {
    if (!_pixelsIndices.empty()) {
        _pixelsIndices.clear();
    }
    
    _storage.push_back(eye_vec);
}

void FlashedEyeFinder::clearEyes() {
    for (const auto& eye_vec : _storage) {
        for (const int32_t idx : eye_vec) {
            if (_image.redPixels[idx - 1] >= RED_CHANNEL_TARGET_VALUE) {
                _image.redPixels[idx - 1] -= REDUCE_CONSTANT;
            }
        }
    }

    _storage.clear();
}
