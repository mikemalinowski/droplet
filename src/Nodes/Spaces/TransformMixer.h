/*

Droplet : TransformMixer

Takes in a list of matrices and for each one the

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
class TransformMixer : public DropletNode
{
public:

	static const int Identifier = 0x0012f77f;
	static const char* NodeName() { return "TransformMixer"; }

	//-------------------------------------------
	static void* creator();

	//-------------------------------------------
	static MStatus initialize();

	//-------------------------------------------
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	//-------------------------------------------
	// These are our input plugs
	static MObject weights;
	static MObject poses;
	static MObject tracks;

	//-------------------------------------------
	// These are our output plugs
	static MObject result;

};