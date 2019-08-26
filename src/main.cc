// C++ includes
#include <iostream>
#include <vector>

// Include vector classes
#include <OpenVolumeMesh/Geometry/VectorT.hh>

// Include polyhedral mesh kernel
#include <OpenVolumeMesh/Mesh/TetrahedralGeometryKernel.hh>

// Include File Manager
#include <OpenVolumeMesh/FileManager/FileManager.hh>

// Make some typedefs to facilitate your life

using namespace std;

void countMeanValeance(const std::string& inFileName)
{
    using Vec3d = OpenVolumeMesh::Geometry::Vec3d;
    using TetMesh = OpenVolumeMesh::TetrahedralGeometryKernel<Vec3d, OpenVolumeMesh::TetrahedralMeshTopologyKernel>;
    
    OpenVolumeMesh::IO::FileManager fm;
    TetMesh tetmesh;
    fm.readFile(inFileName, tetmesh);

    int V = tetmesh.n_vertices();
    int E = tetmesh.n_edges();
    int F = tetmesh.n_faces();
    int T = tetmesh.n_cells();

    int const C = V - E + F - T;

    cout << "V - E + F - T = " << C << endl;
}

bool isInFileGood(const std::string& filename)
{
  std::ifstream is(filename.c_str());
  return is.good();
}

void printUsage(const std::string& progname)
{
  std::cout << "usage: " << progname << " <inFile>" << std::endl
            << std::endl
            << "Reads input tet mesh with properties from <inFile> " << std::endl
            << "and writes the resulting tet mesh with properties to <outFile> in ovm format." << std::endl;
}

int main(int argc, const char* argv[]) {

    if (argc != 2)
    {
        printUsage(argv[0]);
        return 0;
    }

    auto inFilename  = std::string(argv[1]);

    if (!isInFileGood(inFilename))
    {
        std::cout << "Could not open input File " << inFilename << std::endl;
        return 1;
    }
    if (isInFileGood(inFilename)) countMeanValeance(inFilename);

    return 0;
}

