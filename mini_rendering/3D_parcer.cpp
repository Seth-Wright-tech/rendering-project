#include "3D_parcer.h"

// global vectors
std::vector<Vec3> vertices;
std::vector<Vec2> textureCoords;
std::vector<Vec3> normals;
std::vector<Face> faces;

bool loadOBJ(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::string type;
        s >> type;

        if (type == "v") {
            Vec3 vertex;
            s >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (type == "vt") {
            Vec2 texCoord;
            s >> texCoord.u >> texCoord.v;
            textureCoords.push_back(texCoord);
        } else if (type == "vn") {
            Vec3 normal;
            s >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (type == "f") {
            Face face;
            char slash;
            for (int i = 0; i < 3; ++i) {
                s >> face.vertexIndices[i] >> slash >> face.textureIndices[i] >> slash >> face.normalIndices[i];
                // OBJ files are 1-indexed, convert to 0-indexed
                face.vertexIndices[i]--;
                face.textureIndices[i]--;
                face.normalIndices[i]--;
            }
            faces.push_back(face);
        }
    }

    file.close();
    return true;
}

std::vector<Face> get_faces() {
    return faces;
}

std::vector<Vec3> get_vertices() {
    return vertices;
}
std::vector<Vec3> get_normals() {
    return normals;
}
std::vector<Vec2> get_textureCoords() {
    return textureCoords;
}