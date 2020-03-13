#include "provided.h"
#include <vector>
using namespace std;

class DeliveryPlannerImpl
{
public:
    DeliveryPlannerImpl(const StreetMap* sm);
    ~DeliveryPlannerImpl();
    DeliveryResult generateDeliveryPlan(
        const GeoCoord& depot,
        const vector<DeliveryRequest>& deliveries,
        vector<DeliveryCommand>& commands,
        double& totalDistanceTravelled) const;
private:
    const StreetMap* m_streetMap;
    PointToPointRouter m_router;
};

DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm): m_router(sm)
{
    m_streetMap = sm;
}

DeliveryPlannerImpl::~DeliveryPlannerImpl()
{
}

DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{
    GeoCoord startingPoint = depot;
    list<StreetSegment> segmentGetter;
    for (auto it = deliveries.begin(); it != deliveries.end(); ++it)
    {
        m_router.generatePointToPointRoute(startingPoint, (*it).location, segmentGetter, totalDistanceTravelled);
        startingPoint = (*it).location; //Set the starting location for the next delivery to the end point of this delivery
    }
    m_router.generatePointToPointRoute(startingPoint, depot, segmentGetter, totalDistanceTravelled); //Return to the depot, duh!
    int i = 0; //This shall be used to get to the delivery vector position
    auto it = segmentGetter.begin();
    for (; it != segmentGetter.end(); ++it)
    {
        StreetSegment currentStreet = (*it);
        DeliveryCommand commandToPush;
        string turningInstruction;
        ++it; //it shall now be known as the next street
        double distanceToProceed = 0;
        if (currentStreet.name == (*it).name)
        {
            double angleToTurn = angleBetween2Lines(currentStreet, (*it));
            if (angleToTurn >= 0 && angleToTurn < 22.5)
                turningInstruction = "east";
            else if (angleToTurn >= 22.5 && angleToTurn < 67.5)
                turningInstruction = "northeast";
            else if (angleToTurn >= 67.5 && angleToTurn < 112.5)
                turningInstruction = "north";
            else if (angleToTurn >= 112.5 && angleToTurn < 157.5)
                turningInstruction = "northwest";
            else if (angleToTurn >= 157.5 && angleToTurn < 202.5)
                turningInstruction = "west";
            else if (angleToTurn >= 202.5 && angleToTurn < 247.5)
                turningInstruction = "southwest";
            else if (angleToTurn >= 247.5 && angleToTurn < 292.5)
                turningInstruction = "south";
            else if (angleToTurn >= 292.5 && angleToTurn < 337.5)
                turningInstruction = "southeast";
            else if (angleToTurn >= 337.5)
                turningInstruction = "east";
            bool atDeliveryLocation = false;
            while (currentStreet.name == (*it).name)
            {
                if (deliveries[i].location == currentStreet.start)
                {
                    atDeliveryLocation = true;
                    break;
                }
                distanceToProceed += (distanceEarthMiles(currentStreet.start, (*it).end));
                currentStreet = (*it);
                ++it;
            }
            commandToPush.initAsProceedCommand(turningInstruction, currentStreet.name, distanceToProceed);
            commands.push_back(commandToPush);
            if (atDeliveryLocation)
            {
                commandToPush.initAsDeliverCommand(deliveries[i].item);
                commands.push_back(commandToPush);
                i++;
            }
            double turnDirection = angleBetween2Lines(currentStreet, (*it));
            if (turnDirection >= 1 && turnDirection < 180)
                turningInstruction = "left";
            else if (turnDirection >= 180 && turnDirection < 359)
                turningInstruction = "right";
            commandToPush.initAsTurnCommand(turningInstruction, (*it).name);
            commands.push_back(commandToPush);
        }
        else
        {
            double turnDirection = angleBetween2Lines(currentStreet, (*it));
            if (turnDirection >= 1 && turnDirection < 180)
                turningInstruction = "left";
            else if (turnDirection >= 180 && turnDirection < 359)
                turningInstruction = "right";
            commandToPush.initAsTurnCommand(turningInstruction, (*it).name);
            commands.push_back(commandToPush);
        }
    }
    if ((*it).start == depot)
    {
        return DELIVERY_SUCCESS;
    }
    return NO_ROUTE;
}

//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm)
{
    m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner()
{
    delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{
    return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}
