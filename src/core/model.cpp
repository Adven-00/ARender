#include "model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

Model::Model(std::string name) {
    name_ = name;
}

void Model::LoadVertices() {
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config;

    reader_config.mtl_search_path = DEFAULT_MODEL_PATH + name_;
    reader_config.triangulate = true;

    reader.ParseFromFile(DEFAULT_MODEL_PATH + name_ + "/" + name_ + ".obj", reader_config);

    auto &attrib = reader.GetAttrib();
    auto &shapes = reader.GetShapes();

    for (size_t s = 0; s < shapes.size(); s++) {

        // loop over faces
        size_t offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // loop over vertices in the face
            for (size_t i = 0; i < fv; i++) {
                Vertex v;

                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[offset + i];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
                v.coord.world = glm::vec4(vx, vy, vz, 1.f);

                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    v.attr.vec3_attr["normal"] = glm::vec3(nx, ny, nz);
                }

                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    v.attr.vec2_attr["uv"] = glm::vec2(tx, ty);
                }
                vertex_buffer_.Add(v);
            }
            offset += fv;           
        }
    }
    Vertex *pv = vertex_buffer_.GetPointer(0);
    for (int i = 0; i < vertex_buffer_.Size() / 3; i++) {
        faces_.push_back({pv + i, pv + i + 1, pv + i + 2});
    }
}

std::vector<Triangle> Model::Faces() {
    return faces_;
}

void Model::LoadTexture(std::string texture_name) {
    auto texture_path = DEFAULT_MODEL_PATH + name_ + "/" + texture_name;
    texture_.Load(texture_path);
}

void Model::AlterUniformTexture(Uniform &uniform) {
    uniform.texture = texture_;
}