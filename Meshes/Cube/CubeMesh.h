//
// Created by natha on 26/02/2025.
//

#ifndef CUBEMESH_H
#define CUBEMESH_H

#include "../Mesh.h"
#include <vector>


class CubeMesh : public Mesh {
    
public:
    CubeMesh();
    ~CubeMesh();


private:
    
    static std::vector<float> CubeVertices();
    static std::vector<unsigned int> CubeIndices();
};



#endif //CUBEMESH_H
