#ifndef __MESH_H__
#define __MESH_H__

#include "Elastic/Core/Base.h"
#include "Elastic/Renderer/VertexArray.h"
#include "Elastic/Renderer/Shader.h"

#include "glm/glm.hpp"

namespace Elastic {
    
    struct Vertex {
        glm::vec3 Position;
        glm::vec4 Color;
    };

    struct Edge {
        size_t v1, v2;
        glm::vec4 Color;
    };

    struct Facet {
        size_t v1, v2, v3;
        glm::vec4 Color;
    };
    

    class Mesh
    {
    public:

        Mesh() = default;
        Mesh(
            std::vector<Vertex> vertices,
            std::vector<Edge> edges,
            std::vector<Facet> faces)
            : m_Vertices(vertices), m_Edges(edges), m_Facets(faces)
            {};

        Vertex GetVertex(size_t index) const { 
            if(index >= m_Vertices.size()) {
                EL_CORE_ERROR("Index out of bounds: {0} >= {1}", index, m_Vertices.size());
                assert(index < m_Vertices.size());
            }
            return m_Vertices[index];
        }
        std::vector<Vertex> GetVertices() const { return m_Vertices; }
        std::vector<Edge> GetEdges() const { return m_Edges; }
        std::vector<Facet> GetFacets() const { return m_Facets; }
        float GetOpacity() const { return opacity; }

        std::string ToOBJ() const {
            std::stringstream ss;
            for(const Vertex& v : m_Vertices) {
                ss << "v " << v.Position.x << " " << v.Position.y << " " << v.Position.z << std::endl;
            }

            for(const Facet& f : m_Facets) {
                ss << "f " << f.v1+1 << " " << f.v2+1 << " " << f.v3+1 << std::endl;
            }

            for(const Edge& e : m_Edges) {
                ss << "l " << e.v1+1 << " " << e.v2+1 << std::endl;
            }
            return ss.str();
        }

    protected:
        std::vector<Vertex> m_Vertices;
        std::vector<Edge> m_Edges;
        std::vector<Facet> m_Facets;

        float opacity = 0.5f;
    };

}

#endif