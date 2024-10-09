//
// Created by filip on 8/8/24.
//

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "VAO.h"
#include "EBO.h"
#include "Shader.h"

class Renderable {
public:
    Renderable(Shader& shader);
    virtual void update();
    virtual ~Renderable();


    const VAO& GetVAO() const {
        return vao;
    }

    const EBO& GetEBO() const {
        return ebo;
    }

    const Shader& GetShader() const {
        return shader;
    }

protected:
    VAO vao;
    EBO ebo;
    Shader& shader;
};



#endif //RENDERABLE_H
