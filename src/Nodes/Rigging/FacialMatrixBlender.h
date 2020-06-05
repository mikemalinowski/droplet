/*
Droplet : FacialMatrixBlender

This is used to operate on matrix transforms much like how we're
used to operating on blendshapes. Each pose is additively applied
based on a given weighting.
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
class FacialMatrixBlender : public DropletNode
{
public:

	static const int Identifier = 0x0012f77e;
	static const char* NodeName() { return "FacialMatrixBlender"; }

	//-------------------------------------------
	static void* creator();

	//-------------------------------------------
	static MStatus initialize();

	//-------------------------------------------
	virtual MStatus compute(const MPlug& plug, MDataBlock& dataBlock);

	//-------------------------------------------
	// These are our input plugs
	static MObject label;
	static MObject neutralTracks;
	static MObject poseList;
	static MObject posedTracks;
	static MObject weight;
	static MObject targets;

	//-------------------------------------------
	// These are our output plugs
	static MObject results;

};
