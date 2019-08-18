/*

Droplet : Tan

Author : Mike Malinowski : www.twisted.space

*/
// -- Maya Includes
#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MDataBlock.h>
#include <maya/MArrayDataHandle.h>
#include <math.h>

// -- Droplet Includes
#include "Tan.h"

// -- Declare our plugs
MObject FloatTan::inValue;
MObject FloatTan::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatTan::creator()
{
	return new FloatTan;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatTan::initialize()
{
	FloatTan n;
	dp::attributes::Create("value", float(0), n, FloatTan::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatTan::result, false);

	attributeAffects(FloatTan::inValue, FloatTan::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatTan::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatTan::inValue).asFloat();
	dataBlock.outputValue(FloatTan::result).set(sin(value));
	dataBlock.setClean(FloatTan::result);

	return MStatus::kSuccess;
}


