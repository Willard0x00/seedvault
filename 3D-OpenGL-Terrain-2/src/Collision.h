#ifndef COLLISION_H
#define COLLISION_H

#include <glm/gtc/matrix_transform.hpp>

namespace collision {

    inline bool point_and_rect(glm::vec4 r, glm::vec2 p) {
        return !( p.x < r.x || p.x > r.x + r.z || p.y < r.y || p.y > r.y + r.w );
    }

    inline bool circle_and_rect(glm::vec4 r, glm::vec2 p, float radius) {
        float tx = p.x;
        float ty = p.y;

        if     (p.x < r.x)       tx = r.x;
        else if(p.x > r.x + r.z) tx = r.x + r.z;
        if     (p.y < r.y)       ty = r.y;
        else if(p.y > r.y + r.w) ty = r.y + r.w;

        float dx = p.x - tx;
        float dy = p.y - ty;
        float distance = sqrt(dx * dx + dy * dy);

        return distance <= radius;
    }
}

#endif