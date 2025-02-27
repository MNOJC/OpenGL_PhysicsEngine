//
// Created by natha on 27/02/2025.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include "../Mesh.h"
#include <vector>

class Platform : public Mesh {
    
public:
    Platform();
    ~Platform();


private:
    
    static std::vector<float> PlatformVertices();
    static std::vector<unsigned int> PlatformIndices();
};

#endif //PLATFORM_H
