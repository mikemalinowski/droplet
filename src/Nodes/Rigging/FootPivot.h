/*

Droplet : FootPivot

This is an implementation of a foot pivot node

Author : Mike Malinowski : www.twisted.space
*/
#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MPlug.h>
#include <maya/MStatus.h>

// Droplet Includes
#include "../../Core/DropletNode.h"
#include "../../Utilities/Attributes.h"

// Create a node class
class FootPivot : public DropletNode
{
public:

    static const int Identifier = 0x00117fcf;
    static const char* NodeName() { return "FootPivot"; }

    //-------------------------------------------
    // Returns a new instance of this
    // node
    static void* creator();

    //-------------------------------------------
    // Called on the initialisation of the node
    static MStatus initialize();

    //-------------------------------------------
    // This is the caluclation method
    MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

    // These are our matrix inputs. They define the default
    // pivot points
    static MObject BaseMatrix;
    static MObject RightMatrix;
    static MObject LeftMatrix;
    static MObject RearMatrix;
    static MObject FrontMatrix;
    static MObject BridgeMatrix;
    static MObject AnchorMatrix;

    // These are our main animatable attributes
    static MObject Roll;
    static MObject Bank;
    static MObject Ball;

    // These are our setup attributes
    static MObject MaxRoll;
    static MObject MaxBridge;
    static MObject MaxBank;
    static MObject MaxBall;

    // Define our output attributes
    static MObject Demo;
};
