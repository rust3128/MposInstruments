#ifndef LISSTFUELCLASS_H
#define LISSTFUELCLASS_H

#include <QString>

class LisstFuelClass
{
public:
    LisstFuelClass();
    int tankID() const;
    QString shortName() const;
    QString fuelName() const;
    void setTankID(int tankID);
    void setShortName(const QString &shortName);
    void setFuelName(const QString &fuelName);

private:
    int m_tankID;
    QString m_shortName;
    QString m_fuelName;

};

#endif // LISSTFUELCLASS_H
