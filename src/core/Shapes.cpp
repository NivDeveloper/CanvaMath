#include "Shapes.h"

namespace shapes {


    int Shape::GetVertexCount() { return m_vertcount;}
    int Shape::GetIndexCount() { return m_indcount; }
    unsigned int Shape::GetSize() { return m_size*m_vertcount*sizeof(float); }

    Shape::Shape(const glm::mat4 &trans, const glm::vec3 &origin)
        : transform{trans}, origin{origin}, m_size{0}, m_vertcount{0}, m_indcount{0}{}

    void Shape::SetMaterial(std::shared_ptr<Material> mat) {
        m_mesh->SetMaterial(mat);
    }

    Triangle::Triangle(const glm::mat4 &trans, const glm::vec3 &origin): Shape{trans, origin} {
        m_vertices = new float[3*5]{
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.5f, 1.0f
        };

        m_size = 3*5*sizeof(float);
    }

    Cube::Cube(const glm::mat4 &trans, const glm::vec3 &origin): Shape{trans, origin} {
        
        m_vertcount = 8;
        m_pos = {
            //front
            {-0.5f, -0.5f, 0.5f},  //bot left
            {0.5f, -0.5f, 0.5f},   //bot right
            {0.5f,  0.5f, 0.5f},   //top right
            {-0.5f,  0.5f, 0.5f},  //top left
            //back
            {-0.5f, -0.5f, -0.5f},   //bot left
            {0.5f, -0.5f, -0.5f},    //bot right
            {0.5f,  0.5f, -0.5f},    //top right
            {-0.5f,  0.5f, -0.5f}    //top left
        };

        m_indcount = 6*6;
        m_Pind = {
            //front
            0, 1, 2,
            2, 0, 3,
            //top
            3, 2, 6,
            6, 3, 7,
            //back
            7, 6, 5,
            5, 7, 4,
            //bot
            5, 4, 0,
            0, 5, 1,
            //right
            1, 5, 6,
            6, 1, 2,
            //left
            4, 0, 3,
            3, 4, 7
        };

        m_tex = {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        };
        
        m_Tind = {
            0, 1, 2,
            2, 0, 3,

            0, 1, 2,
            2, 0, 3,

            0, 1, 2,
            2, 0, 3,

            0, 1, 2,
            2, 0, 3,

            0, 1, 2,
            2, 0, 3,

            0, 1, 2,
            2, 0, 3
        };

        m_norm = {
            {0.0f, 0.0f, 1.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, -1.0f},
            {0.0f, -1.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {-1.0f, 0.0f, 0.0f},
        };

        m_Nind = {
            //front
            0, 0, 0,
            0, 0, 0,
            //top
            1, 1, 1,
            1, 1, 1,
            //back
            2, 2, 2,
            2, 2, 2,
            //bot
            3, 3, 3,
            3, 3, 3,
            //right
            4, 4, 4,
            4, 4, 4,
            //left
            5, 5, 5,
            5, 5, 5
        };

        std::vector<Vertex> vertices;
        for (size_t i = 0; i < m_Pind.size(); i++) {
            vertices.push_back(Vertex{
                m_pos[m_Pind[i]],
                m_norm[m_Nind[i]],
                m_tex[m_Tind[i]]});
        }
        std::vector<unsigned int> indices{};
        m_mesh = std::make_unique<Mesh>(vertices, indices);
    }

    Rectangle::Rectangle(const glm::mat4 &trans, const glm::vec3 &origin): Shape{trans, origin} {
        
        m_vertcount = 4;

        m_pos = {
            {-0.5f, -0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {0.5f,  0.5f, 0.0f},
            {-0.5f, 0.5f, 0.0f}
        };

        m_indcount = 6;
        m_Pind = {
            0, 1, 2,
            2, 0, 3
        };

        m_tex = {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
        };

        m_Tind = {
            0, 1, 2,
            2, 0, 3
        };

        m_norm = {
            {0.0f, 0.0f, 1.0f}
        };

        m_Nind = {
            0, 0, 0,
            0, 0, 0
        };
        
        std::vector<Vertex> vertices;
        for (size_t i = 0; i < m_Pind.size(); i++) {
            vertices.push_back(Vertex{
                m_pos[m_Pind[i]],
                m_norm[m_Nind[i]],
                m_tex[m_Tind[i]]});
        }
        std::vector<unsigned int> indices{};
        m_mesh = std::make_unique<Mesh>(vertices, indices);

    }

    

}