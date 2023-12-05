#pragma once

// #include "glm.hpp"
// #include "gtc/matrix_transform.hpp"
// #include "gtc/type_ptr.hpp"

#include "Material.h"
#include "Mesh.h"
#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <memory>

namespace shapes{

    enum VertexType {
        Pos = 1 << 0,
        Norm = 1 <<1,
        Tex = 1 << 2,
        Col = 1 << 3
    };

    inline VertexType operator|(VertexType a, VertexType b)
    {
        return static_cast<VertexType>(static_cast<int>(a) | static_cast<int>(b));
    }

    inline int operator&(VertexType a, VertexType b)
    {
        return (static_cast<int>(a) & static_cast<int>(b));
    }

    class Shape {
    protected:
        float* m_vertices;
        unsigned int m_size;
        int m_vertcount;
        int m_indcount;
        VertexType m_vertLayout;
        std::vector<unsigned int> m_Pind;
        std::vector<unsigned int> m_Nind;
        std::vector<unsigned int> m_Tind;
        std::vector<glm::vec3> m_pos;
        std::vector<glm::vec3> m_norm;
        std::vector<glm::vec2> m_tex;
    public:
        glm::vec3 origin;
        glm::mat4 transform;
        std::unique_ptr<Mesh> m_mesh;

        Shape(const glm::mat4 &trans, const glm::vec3 &origin);
        unsigned int GetSize();
        int GetIndexCount();
        int GetVertexCount();
        
        void SetMaterial(std::shared_ptr<Material> mat);
    };

    class Triangle : public Shape {
        public:
            Triangle(const glm::mat4 &trans, const glm::vec3 &origin);
    };

    class Cube : public Shape {
        public:
            Cube(const glm::mat4 &trans, const glm::vec3 &origin);
    };

    class Rectangle: public Shape {
        public:
            Rectangle(
                const glm::mat4 &trans,
                const glm::vec3 &origin);
    };
    
}