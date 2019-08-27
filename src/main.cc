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
using Vec3d = OpenVolumeMesh::Geometry::Vec3d;
using TetMesh = OpenVolumeMesh::TetrahedralGeometryKernel<Vec3d, OpenVolumeMesh::TetrahedralMeshTopologyKernel>;

void save_ovm_as_UCD_inp(const TetMesh& _tetmesh)
{
  string _filename = "output.inp";
  ofstream f_write(_filename);

  f_write << _tetmesh.n_vertices() << " " << _tetmesh.n_cells() << " 0 0 0" << endl;

  // write Node coordinates
  int v_count = 1;
  for (auto v_it = _tetmesh.v_iter(); v_it.valid(); ++v_it)
  {
    auto p = _tetmesh.vertex(*v_it);
    f_write << v_count << " " << p[0] << " " << p[1] << " " << p[2] << endl;
    v_count += 1;
  }

  // write Tet cells
  int c_count = 1;
  for (auto c_it = _tetmesh.c_iter(); c_it.valid(); ++c_it)
  {
    f_write << c_count << " 0 tet "; 
    for (auto cv_it = _tetmesh.cv_iter(*c_it); cv_it.valid(); ++cv_it)
    {
      int id = cv_it.cur_handle().idx();
      f_write << id + 1 << " ";
    }
    f_write << endl;
    c_count += 1;
  }

  f_write.close();
}

void countMeanValeance(const std::string& inFileName)
{
    OpenVolumeMesh::IO::FileManager fm;
    TetMesh tetmesh;
    fm.readFile(inFileName, tetmesh);

    int V = tetmesh.n_vertices();
    int E = tetmesh.n_edges();
    int F = tetmesh.n_faces();
    int T = tetmesh.n_cells();

    int const C = V - E + F - T;

    cout << "V - E + F - T = " << C << endl;

    save_ovm_as_UCD_inp(tetmesh);
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
    if (isInFileGood(inFilename))
    {
      countMeanValeance(inFilename);
      return 0;
    } 

    return 0;
}

