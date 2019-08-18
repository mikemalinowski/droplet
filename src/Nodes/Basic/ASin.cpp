/*

Droplet : ASin

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
#include "ASin.h"

// -- Declare our plugs
MObject FloatASin::inValue;
MObject FloatASin::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatASin::creator()
{
	return new FloatASin;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatASin::initialize()
{
	FloatASin n;
	dp::attributes::Create("value", float(0), n, FloatASin::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatASin::result, false);

	attributeAffects(FloatASin::inValue, FloatASin::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatASin::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatASin::inValue).asFloat();
	dataBlock.outputValue(FloatASin::result).set(asin(value));
	dataBlock.setClean(FloatASin::result);

	return MStatus::kSuccess;
}


