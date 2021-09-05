#include "model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

Model::Model(std::string obj_path, std::string mtl_path)
    : obj_path_(obj_path), mtl_path_(mtl_path) {
        LoadVertices();
    }

void Model::LoadVertices() {
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;

    reader_config.mtl_search_path = mtl_path_;
    reader_config.triangulate = true;

    reader.ParseFromFile(obj_path_, reader_config);

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();

    for (size_t s = 0; s < shapes.size(); s++) {

        // loop over faces
        size_t face_num = shapes[s].mesh.num_face_vertices.size();
        vertices_ = new Vertex[face_num * 3];

        for (size_t f = 0; f < face_num; f++) {

            // loop over vertices in the face
            for (size_t i = 0; i < 3; i++) {

                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[f * 3 + i];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
                vertices_[f * 3 + i].coord.world = glm::vec4(vx ,vy, vz, 1.f);

                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    vertices_[f * 3 + i].attr.vec3_attr["norm"] = glm::vec3(nx, ny, nz);
                }

                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    vertices_[f * 3 + i].attr.vec2_attr["uv"] = glm::vec2(tx, ty);
                }
            }
            auto pv = vertices_ + f * 3;
            faces_.push_back({pv, pv + 1, pv + 2});         
        }
    }
}

Model::~Model() {
    delete[] vertices_;
}

std::vector<Triangle> Model::Faces() {
    return faces_;
}

