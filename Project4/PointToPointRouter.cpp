#include "provided.h"
#include <list>
#include <stack>
using namespace std;

class PointToPointRouterImpl
{
public:
    PointToPointRouterImpl(const StreetMap* sm);
    ~PointToPointRouterImpl();
    DeliveryResult generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const;
private:
    const StreetMap *m_map;
    struct Node
    {
        GeoCoord currentCoord;
        Node *previousCoord;
        double fCost = 0;
        double gCost = 0;
        double hCost = 0;
    };
};

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm)
{
    m_map = sm;
}

PointToPointRouterImpl::~PointToPointRouterImpl()
{
}

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    //Since the specs say we can look up A*, I will be following a method implemented by this website: https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2
    if (start == end)
    {
        totalDistanceTravelled = 0;
        route.clear();
        return DELIVERY_SUCCESS;
    }
    vector<StreetSegment> dummyNormal; //This will be overwritten by the infile in streetmap.cpp
    m_map -> getSegmentsThatStartWith(start, dummyNormal);
    vector<StreetSegment> dummyReverse;
    m_map -> getSegmentsThatStartWith(end, dummyReverse);
    if (dummyNormal.empty() || dummyReverse.empty())
    {
        cerr << "Bullshit again" << endl;
        return BAD_COORD; //If we cannot find either the start or end geocoord, then why bother running this?
    }
    else
    {
        cerr << "Beginning Analysis..." << endl;
    }
    Node startingCoord; //oH bOY, i cAnT wAIt tO ImpLEmEnT a-StAR
    startingCoord.currentCoord = start;
    startingCoord.previousCoord = nullptr;
    vector<Node> openList, closedList;
    openList.insert(openList.begin(), startingCoord);
    while (!openList.empty())
    {
        Node currentNode = openList[0];
        int currentIndex = 0;
        vector<Node>::iterator it;
        for (it = openList.begin(); it != openList.end(); ++it)
        {
            if ((*it).fCost < currentNode.fCost)
            {
                currentNode = (*it);
            }
            currentIndex++;
        }
        openList.erase(openList.begin());
        closedList.insert(closedList.begin(), currentNode);
        if (currentNode.currentCoord == end)
        {
            Node current = currentNode;
            while (current.previousCoord != nullptr)
            {
                vector<StreetSegment> streetSegmentGetter;
                StreetSegment segmentGetter;
                if (m_map -> getSegmentsThatStartWith(current.currentCoord, streetSegmentGetter))
                {
                    for (int i = 0; i < streetSegmentGetter.size(); ++i)
                    {
                        if (streetSegmentGetter[i].end == current.previousCoord -> currentCoord)
                        {
                            route.push_front(streetSegmentGetter[i]);
                            totalDistanceTravelled += distanceEarthMiles(streetSegmentGetter[i].start, streetSegmentGetter[i].end);
                        }
                    }
                }
            }
            return DELIVERY_SUCCESS;
        }
        vector<StreetSegment> children;
        vector<Node> childrenGeoCoords;
        m_map -> getSegmentsThatStartWith(currentNode.currentCoord, children);
        for (int i = 0; i < children.size(); ++i)
        {
            Node *temp = new Node;
            (*temp).currentCoord = children[i].end;
            (*temp).previousCoord = &currentNode;
            childrenGeoCoords.push_back(*temp);
            delete temp;
        }
        for (vector<Node>::iterator jt = childrenGeoCoords.begin(); jt != childrenGeoCoords.end(); ++jt)
        {
            for (vector<Node>::iterator kt = closedList.begin(); kt != closedList.end(); ++kt)
            {
                if ((*jt).currentCoord == (*kt).currentCoord)
                {
                    continue;
                }
            }
            (*jt).gCost = currentNode.gCost + 1;
            (*jt).hCost = distanceEarthMiles((*jt).currentCoord, end);
            (*jt).fCost = (*jt).hCost + (*jt).gCost;
            for (vector<Node>::iterator kt = openList.begin(); kt != openList.end(); ++kt)
            {
                if ((*jt).currentCoord == (*kt).currentCoord && (*jt).gCost < (*kt).gCost)
                {
                    continue;
                }
            }
            openList.insert(openList.begin(), (*jt));
        }
    }
    return NO_ROUTE;
}

//******************** PointToPointRouter functions ***************************

// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code.

PointToPointRouter::PointToPointRouter(const StreetMap* sm)
{
    m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter()
{
    delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}
