#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{

    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateFighter(
    const std::string& name,
    glm::vec3 bottomCorner,
    float smallDiagonal,
    float bigDiagonal,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(bottomCorner, color),
        VertexFormat(bottomCorner + glm::vec3(0, bigDiagonal, 0), color),
        VertexFormat(bottomCorner + glm::vec3(-smallDiagonal / 2, bigDiagonal / 2, 0), color),
        VertexFormat(bottomCorner + glm::vec3(smallDiagonal / 2, bigDiagonal / 2, 0), color),

        VertexFormat(bottomCorner + glm::vec3(smallDiagonal / 2 - width / 4, bigDiagonal / 2 - height / 2, 0), color),
        VertexFormat(bottomCorner + glm::vec3(smallDiagonal / 2 - width / 4 + width, bigDiagonal / 2 - height / 2, 0), color),
        VertexFormat(bottomCorner + glm::vec3(smallDiagonal / 2 - width / 4 + width, bigDiagonal / 2 - height / 2 + height, 0), color),
        VertexFormat(bottomCorner + glm::vec3(smallDiagonal / 2 - width / 4, bigDiagonal / 2 - height / 2 + height, 0), color)
    };

    Mesh* fighter = new Mesh(name);

    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 1, 3,
                                          4, 5, 6,
                                          4, 6, 7};

    if (!fill) {
        fighter->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    fighter->InitFromData(vertices, indices);
    return fighter;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 bottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = bottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(-length * sqrt(3) / 2, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(length * sqrt(3) / 2, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color),
        VertexFormat(corner + glm::vec3(-length * sqrt(3) / 2, 3 * length / 2, 0), color),
        VertexFormat(corner + glm::vec3(length * sqrt(3) / 2, 3 * length / 2, 0), color),
        VertexFormat(corner + glm::vec3(0, 2 * length, 0), color)
    };

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 3, 1,
                                          0, 2, 3,
                                          2, 5, 3,
                                          5, 6, 3,
                                          6, 4, 3,
                                          1, 3, 4 };

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(11, 12, 2), color),
        VertexFormat(glm::vec3(8, 3, 2), color),
        VertexFormat(glm::vec3(13, 6.5, 2), color),
        VertexFormat(glm::vec3(6, 9, 2), color),
        VertexFormat(glm::vec3(16, 9, 2), color),
        VertexFormat(glm::vec3(11, 5, 2), color),
        VertexFormat(glm::vec3(14, 3, 2), color)
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 1, 2, 0,
                                          5, 4, 3,
                                          2, 5, 6 };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 1, 0), color),   // A 0
        VertexFormat(glm::vec3(1, 2, 0), color),  // B 1
        VertexFormat(glm::vec3(2, 2, 0), color),   // C 2
        VertexFormat(glm::vec3(3, 1, 0), color),    // D 3
        VertexFormat(glm::vec3(3, 0, 0), color),    // E 4
        VertexFormat(glm::vec3(-3, 0, 0), color),   // F 5
        VertexFormat(glm::vec3(0, -3, 0), color),   // G 6
        VertexFormat(glm::vec3(-3, 1, 0), color),    // H 7
        VertexFormat(glm::vec3(-2, 2, 0), color),    // I 8
        VertexFormat(glm::vec3(-1, 2, 0), color)    // J 9
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = { 6, 0, 5,
                                          5, 0, 7,
                                          7, 0, 9,
                                          7, 9, 8,
                                          6, 4, 0,
                                          3, 0, 4,
                                          3, 2, 0, 
                                          2, 1, 0 };

    if (!fill) {
        heart->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    heart->InitFromData(vertices, indices);
    return heart;
}

Mesh* object2D::CreateStrip(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 4, 0), color),  // A 0
        VertexFormat(glm::vec3(0, 3, 0), color),  // B 1
        VertexFormat(glm::vec3(4, 0, 0), color),  // C 2
        VertexFormat(glm::vec3(4, 1, 0), color)   // D 3
    };

    Mesh* strip = new Mesh(name);
    std::vector<unsigned int> indices = { 1, 3, 0,
                                          2, 3, 1 };

    if (!fill) {
        strip->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    strip->InitFromData(vertices, indices);
    return strip;
}

Mesh* object2D::CreateDanger(
    const std::string& name,
    glm::vec3 color,
    bool fill) {

    std::vector<VertexFormat> vertices =
    {
        // D
        VertexFormat(glm::vec3(1, 4, 2), color),        // A 0
        VertexFormat(glm::vec3(1, 0, 2), color),        // B 1
        VertexFormat(glm::vec3(3.62, 1, 2), color),     // C 2
        VertexFormat(glm::vec3(2.88, 0.25, 2), color),  // D 3
        VertexFormat(glm::vec3(3.3, 2.19, 2), color),   // E 4
        VertexFormat(glm::vec3(2.16, 3.11, 2), color),  // F 5
        VertexFormat(glm::vec3(1.66, 2.47, 2), color),  // G 6
        VertexFormat(glm::vec3(1.68, 0.77, 2), color),  // H 7
        VertexFormat(glm::vec3(2.36, 1.95, 2), color),  // I 8
        VertexFormat(glm::vec3(2.76, 1.35, 2), color),  // J 9
        VertexFormat(glm::vec3(2.66, 1, 2), color),     // K 10

        // A
        VertexFormat(glm::vec3(4, 0, 2), color),         // L 11
        VertexFormat(glm::vec3(5, 3.68, 2), color),      // M 12
        VertexFormat(glm::vec3(5.52, 4.11, 2), color),   // N 13
        VertexFormat(glm::vec3(6, 3.68, 2), color),      // O 14
        VertexFormat(glm::vec3(7, 0, 2), color),         // P 15
        VertexFormat(glm::vec3(5, 0, 2), color),         // Q 16
        VertexFormat(glm::vec3(6, 0, 2), color),         // R 17
        VertexFormat(glm::vec3(5.24, 1.39, 2), color),   // S 18
        VertexFormat(glm::vec3(5.7, 1.39, 2), color),    // T 19
        VertexFormat(glm::vec3(5.28, 1.97, 2), color),   // U 20
        VertexFormat(glm::vec3(5.7, 1.95, 2), color),    // V 21
        VertexFormat(glm::vec3(5.48, 2.89, 2), color),   // W 22

        // N
        VertexFormat(glm::vec3(7.64, 0, 2), color),       // Z 23
        VertexFormat(glm::vec3(8.38, 0, 2), color),       // A1 24
        VertexFormat(glm::vec3(7.64, 4.07, 2), color),    // B1 25
        VertexFormat(glm::vec3(8.38, 4.07, 2), color),    // C1 26
        VertexFormat(glm::vec3(9.64, 1.51, 2), color),    // D1 27
        VertexFormat(glm::vec3(9.64, 0, 2), color),       // E1 28
        VertexFormat(glm::vec3(10.4, 0, 2), color),       // F1 29
        VertexFormat(glm::vec3(10.4, 4.03, 2), color),    // G1 30
        VertexFormat(glm::vec3(9.64, 4.03, 2), color),    // H1 31
        VertexFormat(glm::vec3(8.38, 2.25, 2), color),     // I1 32

        // G
        VertexFormat(glm::vec3(14.08, 3.17, 2), color),    // J1 33
        VertexFormat(glm::vec3(13.42, 2.79, 2), color),    // K1 34
        VertexFormat(glm::vec3(13.32, 4.05, 2), color),    // L1 35
        VertexFormat(glm::vec3(12, 4, 2), color),          // M1 36
        VertexFormat(glm::vec3(11, 3, 2), color),          // N1 37
        VertexFormat(glm::vec3(10.98, 1.41, 2), color),    // O1 38
        VertexFormat(glm::vec3(11.3, 0.67, 2), color),     // P1 39
        VertexFormat(glm::vec3(12, 0, 2), color),          // Q1 40
        VertexFormat(glm::vec3(13.24, 0, 2), color),       // R1 41
        VertexFormat(glm::vec3(13.94, 0.69, 2), color),    // S1 42
        VertexFormat(glm::vec3(14.22, 1.49, 2), color),    // T1 43
        VertexFormat(glm::vec3(14.2, 2.05, 2), color),     // U1 44
        VertexFormat(glm::vec3(12.58, 2.05, 2), color),    // V1 45
        VertexFormat(glm::vec3(12.6, 1.47, 2), color),     // W1 46
        VertexFormat(glm::vec3(13.54, 1.49, 2), color),    // Z1 47
        VertexFormat(glm::vec3(13.06, 0.79, 2), color),    // A2 48
        VertexFormat(glm::vec3(12.22, 0.77, 2), color),    // B2 49
        VertexFormat(glm::vec3(11.76, 1.73, 2), color),    // C2 50
        VertexFormat(glm::vec3(11.8, 2.93, 2), color),     // D2 51
        VertexFormat(glm::vec3(12.74, 3.41, 2), color),    // E2 52

        // E
        VertexFormat(glm::vec3(15, 4, 2), color),         // F2 53
        VertexFormat(glm::vec3(15, 0, 2), color),         // G2 54
        VertexFormat(glm::vec3(17.66, 0, 2), color),      // H2 55
        VertexFormat(glm::vec3(17.66, 4.01, 2), color),   // I2 56
        VertexFormat(glm::vec3(17.66, 3.01, 2), color),   // J2 57
        VertexFormat(glm::vec3(16, 3, 2), color),         // K2 58
        VertexFormat(glm::vec3(17.66, 1, 2), color),      // L2 59
        VertexFormat(glm::vec3(16, 1, 2), color),         // M2 60
        VertexFormat(glm::vec3(16, 2.37, 2), color),      // N2 61
        VertexFormat(glm::vec3(16, 1.59, 2), color),      // O2 62
        VertexFormat(glm::vec3(17, 2.37, 2), color),      // P2 63
        VertexFormat(glm::vec3(17, 1.59, 2), color),      // Q2 64

        // R
        VertexFormat(glm::vec3(18.28, 4, 2), color),       // R2 65
        VertexFormat(glm::vec3(18.3, 0, 2), color),        // S2 66
        VertexFormat(glm::vec3(19.16, 4, 2), color),       // T2 67
        VertexFormat(glm::vec3(19.84, 3.91, 2), color),    // U2 68
        VertexFormat(glm::vec3(20.46, 3.43, 2), color),    // V2 69
        VertexFormat(glm::vec3(20.48, 2.79, 2), color),    // W2 70
        VertexFormat(glm::vec3(20.22, 2.13, 2), color),    // Z2 71
        VertexFormat(glm::vec3(19.58, 1.81, 2), color),    // A3 72
        VertexFormat(glm::vec3(20.52, 0, 2), color),       // B3 73
        VertexFormat(glm::vec3(19.76, 0, 2), color),       // C3 74
        VertexFormat(glm::vec3(18.92, 1.59, 2), color),    // D3 75
        VertexFormat(glm::vec3(19, 0, 2), color),          // E3 76
        VertexFormat(glm::vec3(18.88, 3.27, 2), color),    // F3 77
        VertexFormat(glm::vec3(18.9, 2.41, 2), color),     // G3 78
        VertexFormat(glm::vec3(19.44, 3.09, 2), color),    // H3 79
        VertexFormat(glm::vec3(19.68, 2.71, 2), color),    // I3 80
        VertexFormat(glm::vec3(19.36, 2.45, 2), color)     // J3 81
    };

    Mesh* danger = new Mesh(name);
    std::vector<unsigned int> indices = { // D
                                          0, 1, 6,
                                          5, 0, 6,
                                          5, 6, 8,
                                          5, 8, 4,
                                          4, 8, 9,
                                          4, 9, 2,
                                          9, 10, 2,
                                          2, 10, 3,
                                          10, 7, 3,
                                          1, 6, 7,
                                          1, 7, 3,

                                          // A
                                          11, 16, 18,
                                          11, 18, 20,
                                          11, 20, 12,
                                          20, 22, 12,
                                          12, 14, 13,
                                          22, 14, 12,
                                          21, 14, 22,
                                          21, 15, 14,
                                          10, 7, 3,
                                          19, 15, 21,
                                          17, 15, 19,
                                          19, 21, 20,
                                          18, 19, 20,
                                          
                                          // N
                                          23, 24, 25,
                                          25, 24, 26,
                                          32, 27, 26,
                                          28, 27, 32,
                                          28, 29, 31,
                                          29, 30, 31,

                                          // G
                                          34, 33, 35,
                                          34, 35, 52,
                                          35, 36, 52,
                                          36, 51, 52,
                                          51, 36, 37,
                                          37, 50, 51,
                                          50, 37, 38,
                                          38, 49, 50,
                                          49, 38, 39,
                                          49, 39, 40,
                                          49, 40, 41,
                                          41, 48, 49,
                                          48, 41, 42,
                                          48, 42, 47,
                                          42, 43, 47,
                                          47, 43, 44,
                                          47, 44, 45,
                                          45, 46, 47,

                                          // E
                                          57, 56, 53,
                                          54, 55, 60,
                                          54, 60, 61,
                                          62, 63, 61,
                                          62, 64, 63,
                                          58, 53, 54,
                                          58, 57, 53,
                                          56, 57, 53,
                                          55, 59, 60,
                                          54, 60, 58,

                                          // R
                                          66, 76, 77,
                                          77, 65, 66,
                                          77, 67, 65,
                                          77, 68, 67,
                                          68, 77, 79,
                                          79, 69, 68,
                                          79, 70, 69,
                                          70, 79, 80,
                                          80, 71, 70,
                                          71, 80, 81,
                                          81, 72, 71,
                                          72, 81, 78,
                                          72, 78, 75,
                                          74, 72, 75,
                                          74, 73, 72
    };

    if (!fill) {
        danger->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    danger->InitFromData(vertices, indices);
    return danger;
}