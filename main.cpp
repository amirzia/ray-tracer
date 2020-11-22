
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include "math.hpp"

using namespace std;

typedef vector< float* > Arr2D;

Arr2D vertices, faces, cameras;
vector<string> cameraNames;
vector<Vec3f> projectedVertices;

Vec3f projectVertex(Vec4f vertex, Vec4f cameraPos, float pitch, float yaw, float roll, float f) {
    Vec4f localC(0);
    Mat4f Mt, Mpr, Myr, Mrr;

    Mt.setCol(3, cameraPos * -1);
    Mt.set(3, 3, 1.);

    Mpr.setRow(1, Vec4f(0., cos(pitch), sin(pitch), 0.));
    Mpr.setRow(2, Vec4f(0., -sin(pitch), cos(pitch), 0.));

    Myr.setRow(0, Vec4f(cos(yaw), 0, -sin(yaw), 0));
    Myr.setRow(2, Vec4f(sin(yaw), 0, cos(yaw), 0));

    Mrr.setRow(0, Vec4f(cos(roll), sin(roll), 0., 0.));
    Mrr.setRow(1, Vec4f(-sin(roll), cos(roll), 0., 0.));

    Mat4f transformMatrix = Mrr * Myr * Mpr * Mt;
    localC = transformMatrix * vertex;
    Vec3f projectedP(f * localC.x_ / localC.z_, f * localC.y_ / localC.z_, 1.);
    return projectedP;
}

void parse_file(
        string filename,
        Arr2D &vertices,
        Arr2D &faces,
        Arr2D &cameras,
        vector<string> &cameraNames)
{
    enum ReadMode
    {
        READ_VERTICES,
        READ_FACES,
        READ_CAMERAS
    };
    ReadMode readMode = READ_VERTICES;

    ifstream infile(filename);
    string line;
    while (getline(infile, line))
    {
        if (line == "")
            continue;

        if (line == "VERTICES")
        {
            readMode = READ_VERTICES;
            continue;
        }
        else if (line == "FACES")
        {
            readMode = READ_FACES;
            continue;
        }
        else if (line == "CAMERAS")
        {
            readMode = READ_CAMERAS;
            continue;
        }

        float *vertex = new float[4];
        float *face = new float[7];
        float *camera = new float[8];
        string cameraName;

        istringstream iss(line);
        switch (readMode)
        {
            case READ_VERTICES:
                iss >> vertex[0] >> vertex[1] >> vertex[2] >> vertex[3];
                vertices.push_back(vertex);
                break;
            case READ_FACES:
                iss >> face[0] >> face[1] >> face[2] >> face[3] >> face[4] >> face[5] >> face[6];
                faces.push_back(face);
                break;
            case READ_CAMERAS:
                iss >> camera[0] >> camera[1] >> camera[2] >> camera[3] >> camera[4] >> camera[5] >> camera[6] >> camera[7] >> cameraName;
                cameras.push_back(camera); 
                cameraNames.push_back(cameraName);
                break;
        }
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    for (unsigned i = 0; i < faces.size(); i++) {
        int i1 = faces[i][0] - 1;
        int i2 = faces[i][1] - 1;
        int i3 = faces[i][2] - 1;

        Vec3f v1 = projectedVertices[i1];
        Vec3f v2 = projectedVertices[i2];
        Vec3f v3 = projectedVertices[i3];

        glVertex2f(v1.x_, v1.y_); glVertex2f(v2.x_, v2.y_);  
        glVertex2f(v2.x_, v2.y_); glVertex2f(v3.x_, v3.y_);  
        glVertex2f(v3.x_, v3.y_); glVertex2f(v1.x_, v1.y_);  
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    string filename = "model.txt";
    parse_file(filename, vertices, faces, cameras, cameraNames);

    int camNum = 0;
    float pitch = cameras[camNum][4] * M_PI / 180.;
    float yaw = cameras[camNum][5] * M_PI / 180.;
    float roll = cameras[camNum][6] * M_PI / 180.;
    float f = cameras[camNum][7];
    Vec4f cameraPos(cameras[camNum][0], cameras[camNum][1], cameras[camNum][2], cameras[camNum][3]);
    for (unsigned i = 0; i < vertices.size(); i++) {
        Vec4f globalV(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3]);
        Vec3f projectedV = projectVertex(globalV, cameraPos, pitch, yaw, roll, f); 
        projectedVertices.push_back(projectedV * 1);
    }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(200, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow(cameraNames[camNum].c_str());
  glutDisplayFunc(draw);
  glutMainLoop();
}

