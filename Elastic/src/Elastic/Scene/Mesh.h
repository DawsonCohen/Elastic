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

        Vertex GetVertex(size_t index) const { return m_Vertices[index]; }
        std::vector<Vertex> GetVertices() const { return m_Vertices; }
        std::vector<Edge> GetEdges() const { return m_Edges; }
        std::vector<Facet> GetFacets() const { return m_Facets; }
        float GetOpacity() const { return opacity; }

    protected:
        std::vector<Vertex> m_Vertices;
        std::vector<Edge> m_Edges;
        std::vector<Facet> m_Facets;

        float opacity = 0.5f;
    };

}

#endif