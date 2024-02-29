#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::transpose(
            glm::mat3(
                1, 0, translateX,
                0, 1, translateY,
                0, 0, 1)
               ); 

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        return glm::transpose(
            glm::mat3(
                scaleX, 0 , 0,
                0, scaleY, 0,
                0, 0, 1)
                );
    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        float cost = cos(radians);
        float sint = sin(radians);
        return glm::transpose(
            glm::mat3(
                cost, -sint, 0,
                sint, cost, 0,
                0, 0, 1
            )
        );

    }
}   // namespace transform2D
