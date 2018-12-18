
#include <maya/MPxNode.h>


class DropletNode : public MPxNode
{
public:
    static const int TypeId = 0;
    static const char* NodeName() { return "undefined"; }
};