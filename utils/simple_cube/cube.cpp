#include <fstream>

int main() {
    const float vtx[6][3] = {
        {-0.90, -0.90, -1},
        { 0.85, -0.90, -1},
        {-0.90,  0.85, -1},
        { 0.90, -0.85, -1},
        { 0.90,  0.90, -1},
        {-0.85,  0.90, -1}
    };

    std::ofstream file("cube.bin", std::ios::binary);
    file.write((const char *)vtx, sizeof(vtx));
    return 0;
}
