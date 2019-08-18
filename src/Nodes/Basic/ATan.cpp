/*

Droplet : ATan

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
#include "ATan.h"

// -- Declare our plugs
MObject FloatATan::inValue;
MObject FloatATan::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatATan::creator()
{
	return new FloatATan;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatATan::initialize()
{
	FloatATan n;
	dp::attributes::Create("value", float(0), n, FloatATan::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatATan::result, false);

	attributeAffects(FloatATan::inValue, FloatATan::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatATan::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatATan::inValue).asFloat();
	dataBlock.outputValue(FloatATan::result).set(atan(value));
	dataBlock.setClean(FloatATan::result);

	return MStatus::kSuccess;
}


