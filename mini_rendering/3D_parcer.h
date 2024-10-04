#ifndef THREE_D_PARSER_H
#define THREE_D_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Struct to represent a 3D vector
struct Vec3 {
    float x, y, z;
};

// Struct to represent a 2D vector
struct Vec2 {
    float u, v;
};

// Struct to represent a face in the OBJ file
struct Face {
    int vertexIndices[3];
    int textureIndices[3];
    int normalIndices[3];
};

// Global vectors to hold the vertices, texture coordinates, normals, and faces
extern std::vector<Vec3> vertices;
extern std::vector<Vec2> textureCoords;
extern std::vector<Vec3> normals;
extern std::vector<Face> faces;

// Function to load an OBJ file
bool loadOBJ(const std::string& filename);

// Functions to access the parsed data
std::vector<Face> get_faces();
std::vector<Vec3> get_vertices();
std::vector<Vec2> get_textureCoords();
std::vector<Vec3> get_normals();

#endif // THREE_D_PARSER_H
