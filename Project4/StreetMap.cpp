#include "provided.h"
#include "ExpandableHashMap.h"
#include <string>
#include <vector>
#include <functional>
#include <fstream>
using namespace std;

unsigned int hasher(const GeoCoord& g)
{
    return std::hash<string>()(g.latitudeText + g.longitudeText);
}
//unsigned int hasher(const string& g)
//{
//    std::hash<string> stringHash;
//    unsigned int h = stringHash(g);
//    return h;
//}

class StreetMapImpl
{
public:
    StreetMapImpl();
    ~StreetMapImpl();
    bool load(string mapFile);
    bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
private:
    StreetSegment reverseCoords(StreetSegment& seg) const
    {
//        vector<StreetSegment>tempHolder;
//        for (int i = 0; i < m_numberOfSegments; ++i)
//        {
//            if (gc == segs[i].start)
//            {
//                tempHolder.push_back(segs[i]);
//            }
//            else if (gc == segs[i].end)
//            {
//                StreetSegment reversedSegment;
//                reversedSegment.start.latitudeText = segs[i].end.latitudeText;
//                reversedSegment.start.longitudeText = segs[i].end.longitudeText;
//                reversedSegment.end.latitudeText = segs[i].start.latitudeText;
//                reversedSegment.end.longitudeText = segs[i].start.longitudeText;
//                reversedSegment.name = segs[i].name;
//                tempHolder.push_back(reversedSegment);
//            }
//        }
//        swap(segs, tempHolder);
        return (StreetSegment(seg.end, seg.start, seg.name));
    }
    ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_streetSegments;
};

StreetMapImpl::StreetMapImpl()
{
}

StreetMapImpl::~StreetMapImpl()
{
}

bool StreetMapImpl::load(string mapFile) //Runs in O(n*e), where n is the number of lines and e is the number of characters per line
{
    ifstream inputFile(mapFile);
    if (!inputFile)
    {
        return false;
    }
    string streetName, segment, startLat, startLon, endLat, endLon;
    vector<StreetSegment> street;
    while (getline(inputFile, streetName)) //Here, the line is the name of the street
    {
        int numStreetSegs; //Read the line and store the name of the street
        inputFile >> numStreetSegs; //Go to the next line
        inputFile.ignore(1000, '\n');
        for (int i = 0; i < numStreetSegs; ++i) //This will loop through the number of segements each street has
        {
            getline(inputFile, segment);
            istringstream iss(segment);
            iss >> startLat >> startLon >> endLat >> endLon;
            
            GeoCoord start(startLat, startLon);
            GeoCoord end(endLat, endLon);
            StreetSegment newStreetSegment(start, end, streetName);
            
            vector<StreetSegment>* existingSegments = m_streetSegments.find(start);
            if (existingSegments != nullptr)
                existingSegments -> push_back(newStreetSegment);
            else
            {
                vector<StreetSegment> startSegments;
                startSegments.push_back(newStreetSegment);
                m_streetSegments.associate(start, startSegments);
            }
            
            existingSegments = m_streetSegments.find(end);
            if (existingSegments != nullptr)
                existingSegments -> push_back(newStreetSegment);
            else
            {
                vector<StreetSegment> endSegments;
                endSegments.push_back(reverseCoords(newStreetSegment));
                m_streetSegments.associate(end, endSegments);
            }
            street.push_back(newStreetSegment);
            street.push_back(reverseCoords(newStreetSegment));
            //cerr << "Another one bites the dust" << i <<  endl;
        }
    }
    return true;
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
    if (m_streetSegments.find(gc) == nullptr)
    {
        return false;
    }
    else
    {
        segs = (*m_streetSegments.find(gc));
        return true;
    }
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
    delete m_impl;
}

bool StreetMap::load(string mapFile)
{
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
   return m_impl->getSegmentsThatStartWith(gc, segs);
}
