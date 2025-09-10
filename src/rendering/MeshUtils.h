//
// Created by natha on 10/09/2025.
//


#pragma once

#include <memory>
#include "Mesh.h"


class MeshUtils {

    public:

    static std::shared_ptr<Mesh> CreatePlane(float width, float height);
    static std::shared_ptr<Mesh> CreateSphere(float radius,  int segments = 32);
};

