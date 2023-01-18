#pragma once
struct Point {
public:
    int x, y;
    bool operator < (const Point& o) const { // Note *const* at end
        return (y < o.y) && (x < o.x);
    }
};