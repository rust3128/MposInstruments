#include "lisstfuelclass.h"

LisstFuelClass::LisstFuelClass()

{

}

int LisstFuelClass::tankID() const
{
    return m_tankID;
}

QString LisstFuelClass::shortName() const
{
    return m_shortName;
}

QString LisstFuelClass::fuelName() const
{
    return m_fuelName;
}

void LisstFuelClass::setTankID(int tankID)
{
    m_tankID = tankID;
}

void LisstFuelClass::setShortName(const QString &shortName)
{
    m_shortName = shortName;
}

void LisstFuelClass::setFuelName(const QString &fuelName)
{
    m_fuelName = fuelName;
}
