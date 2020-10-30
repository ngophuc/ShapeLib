// SHAPELIB example

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "shapefil.h"

#define MAX_SIZE 1000

struct Point {
    double x,y;
};

using namespace std;

typedef std::vector<Point> polygon_2d;

void read_textefile (const std::string& filename, std::vector<polygon_2d>& polygons)
{
    std::ifstream myfile;
    myfile.open (filename);
    double x, y;
    Point p;

    if (myfile.is_open()) {
        std::string line;
        while (std::getline(myfile, line))
        {
            polygon_2d polygon;
            std::istringstream iss(line);
            while(iss >> x >> y) {
                p.x = x;
                p.y = y;
                polygon.push_back(p);
            }
            polygons.push_back(polygon);
        }
    }
    myfile.close();
}

void write_textefile (const std::string& filename, std::vector<polygon_2d>& polygons)
{
    std::ofstream myfile;
    myfile.open (filename);
    //myfile << polygons.size() << std::endl;
    for(int it=0; it<polygons.size(); it++) {
        //myfile << polygons.at(it).size() << std::endl;
        for(int it_bis=0; it_bis<polygons.at(it).size(); it_bis++) {
            myfile << polygons.at(it).at(it_bis).x << " " <<polygons.at(it).at(it_bis).y<<" ";
        }
        myfile << std::endl;
    }
    myfile.close();
}

void read_shapefile(const std::string& filename, std::vector<polygon_2d>& polygons)
{
    SHPHandle handle = SHPOpen(filename.c_str(), "rb");
    if (!handle)
        throw std::string("File " + filename + " not found");

    int nShapeType, nEntities;
    double adfMinBound[4], adfMaxBound[4];
    SHPGetInfo(handle, &nEntities, &nShapeType, adfMinBound, adfMaxBound );

    for (int i = 0; i < nEntities; i++)
    {
        SHPObject* psShape = SHPReadObject(handle, i );

        // Read only polygons, and only those without holes
        //if (psShape->nSHPType == SHPT_POLYGON && psShape->nParts == 1)
        if (psShape->nSHPType == SHPT_POLYGON || psShape->nSHPType == SHPT_ARC)
        {
            polygon_2d polygon;
            double* x = psShape->padfX;
            double* y = psShape->padfY;
            for (int v = 0; v < psShape->nVertices; v++)
            {
                Point p;
                p.x = x[v];
                p.y = y[v];
                polygon.push_back(p);
                //std::cout<<x[v]<<", "<<y[v]<<std::endl;
            }
            polygons.push_back(polygon);
        }
        SHPDestroyObject( psShape );
    }
    SHPClose(handle);
}

void write_shapefile(const std::string& filename, std::vector<polygon_2d>& polygons)
{
    int nSHPType = SHPT_ARC; //Shape Type: SHPT_POINT SHPT_ARC SHPT_POLYGON
    int iShape = -1; //Shape Number
    SHPHandle    hSHPHandle;
    SHPObject    *psShape;
    
    hSHPHandle = SHPCreate( filename.c_str(), nSHPType );
    for(int it=0; it<polygons.size(); it++)
    {
        int size = polygons.at(it).size();
        double* x = (double*) malloc(size*sizeof(double));
        double* y = (double*) malloc(size*sizeof(double));
        for(int it_bis=0; it_bis<size; it_bis++) {
            x[it_bis] = polygons.at(it).at(it_bis).x;
            y[it_bis] = polygons.at(it).at(it_bis).y;
        }
        for(int it_bis=0; it_bis<size; it_bis++) {
            std::cout<<x[it_bis]<<" "<<y[it_bis]<<" ";
        }
        std::cout<<std::endl;
        psShape = SHPCreateObject( nSHPType, iShape, 0, NULL, NULL, size, x, y, NULL, NULL);
        SHPWriteObject( hSHPHandle, -1, psShape );
        SHPDestroyObject( psShape );
        free(x);
        free(y);
    }
    SHPClose( hSHPHandle );
}

int main()
{
    //Read Shape File
    std::string filename = "../Samples/shapes.shx";
    std::vector<polygon_2d> polygons;
    read_shapefile(filename, polygons);
    filename = "../Samples/shapes.txt";
    //Read / Write a polygon point file
    //write_textefile("shapes.txt", polygons);
    std::vector<polygon_2d> polygons2;
    read_textefile(filename, polygons2);
    //Write Shape File
    filename = "test.shx";
    write_shapefile(filename, polygons2);

    return 0;
}
