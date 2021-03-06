/*

Droplet : Power

Calculates the power of a single float

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
class FloatPower : public DropletNode
{
public:

	static const int Identifier = 0x00117fd0;
	static const char* NodeName() { return "Power"; }

	//-------------------------------------------
	static void* creator();

	//-------------------------------------------
	static MStatus initialize();

	//-------------------------------------------
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	//-------------------------------------------
	// These are our input plugs
	static MObject inValue;
	static MObject inPower;

	//-------------------------------------------
	// These are our output plugs
	static MObject result;

};