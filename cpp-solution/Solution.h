#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <cstdint>

#include "utils/Image.h"
#include "utils/FunctionTracer.h"
#include "utils/EyePatterns.h"

#include "FlashedEyeFinder.h"

class Solution {
public:
    void compute([[maybe_unused]] std::vector<PackedImage>& images) {
        FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
        // TODO: fill solution
    }

    void compute([[maybe_unused]] std::vector<StrideImage>& images) {
        FunctionTracer<std::chrono::milliseconds> tracer("compute", "ms");
        // TODO: fill solution
        
        for (size_t i = 0; i < images.size(); ++i) {
            const int32_t image_length = images[i].resolution.width * images[i].resolution.height;

            FlashedEyeFinder eyeFinder(images[i]);

            std::vector<int32_t> eye_pattern_vec;
            for (int32_t j = 0; j < image_length - EYE_PATTERN_COL_SIZE; ++j) {
                const int32_t jump_value = JUMP_ROWS_CONSTANT * images[i].resolution.width;

                if (eyeFinder.isStartOrEndOfEye(images[i], j) && 
                    eyeFinder.isStartOrEndOfEye(images[i], j + jump_value)) {
                        
                    const PatternType p_type = eyeFinder.quickFlashedEyePatternFinder(j);

                    switch (p_type) {
                    case PATTERN_1:
                        eye_pattern_vec = eyeFinder.findFlashedEye(EYE_PATTERN_1, j);
                        if (!eye_pattern_vec.empty()) {
                            eyeFinder.storeEyePattern(eye_pattern_vec);
                            eye_pattern_vec.clear();
                        }
                        break;

                    case PATTERN_2:
                        eye_pattern_vec = eyeFinder.findFlashedEye(EYE_PATTERN_2, j);
                        if (!eye_pattern_vec.empty()) {
                            eyeFinder.storeEyePattern(eye_pattern_vec);
                            eye_pattern_vec.clear();
                        }
                        break;   

                    case PATTERN_3:
                        eye_pattern_vec = eyeFinder.findFlashedEye(EYE_PATTERN_3, j);
                        if (!eye_pattern_vec.empty()) {
                            eyeFinder.storeEyePattern(eye_pattern_vec);
                            eye_pattern_vec.clear();
                        }
                        break; 

                    case PATTERN_4:
                        eye_pattern_vec = eyeFinder.findFlashedEye(EYE_PATTERN_4, j);
                        if (!eye_pattern_vec.empty()) {
                            eyeFinder.storeEyePattern(eye_pattern_vec);
                            eye_pattern_vec.clear();
                        }
                        break; 
                    
                    default:
                        std::cerr << "Unknown EyePattern found" << std::endl;
                    }
                }
            }

            eyeFinder.clearEyes();
        }
    }
};

#endif /* SOLUTION_H_ */
