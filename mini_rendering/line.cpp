#include <iostream>
#include "tgaimage.h"
#include "3D_parcer.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const int width  = 800;
const int height = 800;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    // transpose the line if it is a steep line for Bresenhams's algorithm
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        steep = true;
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    
    // verify that x0 is always smaller than x1
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);
    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for(int x = x0; x <= x1; x++) {
        
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 

        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);
    if (!loadOBJ("head.obj")) {
        std::cerr << "Failed to load OBJ file." << std::endl;
        return -1;
    }

    std::vector<Face> faces = get_faces();
    std::vector<Vec3> vertices = get_vertices();
    int num_faces = faces.size();
    for (int i = 0; i < num_faces; i++) {
        for (int j = 0; j < 3; j++) {
            int face_val1 = faces[i].vertexIndices[j];
            int face_val2 = faces[i].vertexIndices[(j + 1) % 3];
            Vec3 v0 = vertices[face_val1];
            Vec3 v1 = vertices[face_val2];
            int x0 = (v0.x + 1) * width / 2; 
            int y0 = (v0.y + 1) * height / 2; 
            int x1 = (v1.x + 1) * width / 2; 
            int y1 = (v1.y + 1) * height / 2;
            line(x0, y0, x1, y1, image, white);
        }
    } 
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}