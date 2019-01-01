/*

Droplet : FloatStackDivide

This takes in a list of values and performs the operation
sequentially through them.

Author : Mike Malinowski : www.twisted.space

*/
#pragma once

// Maya Includes
#include <maya/MPlug.h>
#include <maya/MStatus.h>
#include <maya/MObject.h>
#include <maya/MDataBlock.h>

// Droplet Includes
#include "../../Core/DropletNode.h"
#include "../../Utilities/Attributes.h"

// This node takes in any number of float values
// and outputs the sum of all those values
class FloatStackDivide : public DropletNode
{
public:

    static const int Identifier = 0x00117fc6;
    static const char* NodeName() { return "FloatStackDivide"; }

    //-------------------------------------------
    static void* creator();

    //-------------------------------------------
    static MStatus initialize();

    //-------------------------------------------
    virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

    //-------------------------------------------
    // These are our input plugs
    static MObject values;

    //-------------------------------------------
    // These are our output plugs
    static MObject result;

};