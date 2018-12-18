
#include <maya/MPxNode.h>
#include "../../Core/DropletNode.h"


class FloatStackSum : public DropletNode
{
public:

    static const int TypeId = 0x00117fc9;
    static const char* NodeName() { return "FloatStackSum"; }

    //-------------------------------------------
    static void* creator();

    //-------------------------------------------
    static MStatus initialize();

    //-------------------------------------------
    virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

    //-------------------------------------------
    // These are our input plugs
    static MObject values;
    static MObject operation;

    //-------------------------------------------
    // These are our output plugs
    static MObject result;

};