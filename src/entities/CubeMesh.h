//
// Created by natha on 26/02/2025.
//

#pragma once

#include "../rendering/Mesh.h"
#include <vector>
#include <memory>


class CubeMesh : public Mesh {
    
public:
 
    static std::shared_ptr<Mesh> Create();


private:
    
    static std::vector<float> GetVertices();
    static std::vector<unsigned int> GetIndices();
};



