#ifndef DOMELEMENT_H
#define DOMELEMENT_H


#include <vector>
#include <QtXml>
#include "Attribute.h"

using namespace std;

class DomElement : public QDomElement
{
    public:
        DomElement();
        vector<Attribute> attributeList;
};

#endif // DOMELEMENT_H
