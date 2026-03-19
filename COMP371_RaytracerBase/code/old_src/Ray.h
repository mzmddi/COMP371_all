
#ifndef RAY_H
#define RAY_H

struct Ray {
    Vector3f o;
    Vector3f d;
    Ray(Vector3f origin, Vector3f direction) {
        o = origin;
        d = direction;
    };
};

#endif