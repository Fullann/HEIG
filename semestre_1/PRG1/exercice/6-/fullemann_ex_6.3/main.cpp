#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "tinyxml2-master/tinyxml2.h"

using namespace std;
struct Coordinates {
    double x, y;
};

struct WGS84 {
    double longitude, latitude;
};

WGS84 convertToWGS84(const Coordinates& nationalCoords) {
    WGS84 wgs84;

    wgs84.longitude = 7.4386372 + 13.13606 * nationalCoords.x + 2.19856 * nationalCoords.x * nationalCoords.y
                     + 0.3628 * nationalCoords.x * nationalCoords.y * nationalCoords.y - 0.121 * nationalCoords.x * nationalCoords.x * nationalCoords.x;

    wgs84.latitude = 46.9510811 + 8.9952 * nationalCoords.y - 0.75272 * nationalCoords.x * nationalCoords.x
                    - 0.00702 * nationalCoords.y * nationalCoords.y - 0.1242 * nationalCoords.x * nationalCoords.x * nationalCoords.y
                    - 0.0389 * nationalCoords.y * nationalCoords.y * nationalCoords.y;

    return wgs84;
}

vector<Coordinates> readCoordinatesFromFile(const string& fileName) {
    vector<Coordinates> coordinates;
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        exit(EXIT_FAILURE);
    }

    double x, y;
    while (file >> x >> y) {
        coordinates.push_back({x, y});
    }

    file.close();
    return coordinates;
}

void exportToKML(const vector<Coordinates>& path, const string& outputFileName) {
    tinyxml2::XMLDocument kmlDoc;
    tinyxml2::XMLElement* kml = kmlDoc.NewElement("kml");
    kml->SetAttribute("xmlns", "http://www.opengis.net/kml/2.2");
    kmlDoc.InsertEndChild(kml);

    tinyxml2::XMLElement* document = kmlDoc.NewElement("Document");
    kml->InsertEndChild(document);

    for (const auto& coord : path) {
        WGS84 wgs84Coord = convertToWGS84(coord);

        tinyxml2::XMLElement* placemark = kmlDoc.NewElement("Placemark");

        tinyxml2::XMLElement* point = kmlDoc.NewElement("Point");
        tinyxml2::XMLElement* coordinates = kmlDoc.NewElement("coordinates");
        coordinates->SetText((to_string(wgs84Coord.longitude) + "," + to_string(wgs84Coord.latitude) + ",0").c_str());

        point->InsertEndChild(coordinates);
        placemark->InsertEndChild(point);
        document->InsertEndChild(placemark);
    }

    kmlDoc.SaveFile(outputFileName.c_str());
}

int main() {
    vector<Coordinates> marathonPath = readCoordinatesFromFile("../../dependence/marathon_de_la_heig.txt");

    exportToKML(marathonPath, "marathon_path.kml");

    cout << "KML file exported successfully." << endl;

    return 0;
}
