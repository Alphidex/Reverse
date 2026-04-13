#include <vector>
#include <string>

#include "CoreTypes.h"

using std::pair;
using std::vector;
using std::string;

class Reader 
{
public:
    pair<vector<Vertex>, vector<unsigned int>> readShape(string path);
};