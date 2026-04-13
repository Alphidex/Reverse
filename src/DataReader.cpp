#include "rapidjson/document.h"
#include <fstream>
#include <iostream>
#include <except>

#include "DataReader.h"

using namespace rapidjson;
using namespace std;
using std::iostream;

pair<vector<Vertex>, vector<unsigned int>> readShape(string path)
{   
    try {
        ifstream file(path);
        string json((istreambuf_iterator<char>(file)),
                    istreambuf_iterator<char>());

        Document doc;

        // Parse the JSON data
        doc.Parse(json.c_str());

        // Check for parse errors
        if (doc.HasParseError()) {
            cerr << "Error parsing JSON: "
                << doc.GetParseError() << endl;
            return 1;
        }

        // Now you can use the Document object to access the
        // JSON data
        return 0;
    } except (e) {

    }
}