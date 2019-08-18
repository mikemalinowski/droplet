/*

Droplet : Cos

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


class FloatCos : public DropletNode
{
public:

	static const int Identifier = 0x00117fd5;
	static const char* NodeName() { return "Cos"; }

	//-------------------------------------------
	static void* creator();

	//-------------------------------------------
	static MStatus initialize();

	//-------------------------------------------
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	//-------------------------------------------
	// These are our input plugs
	static MObject inValue;

	//-------------------------------------------
	// These are our output plugs
	static MObject result;

};