/*

Droplet : Sin

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
#include "Sin.h"

// -- Declare our plugs
MObject FloatSin::inValue;
MObject FloatSin::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatSin::creator()
{
	return new FloatSin;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatSin::initialize()
{
	FloatSin n;
	dp::attributes::Create("value", float(0), n, FloatSin::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatSin::result, false);

	attributeAffects(FloatSin::inValue, FloatSin::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatSin::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatSin::inValue).asFloat();
	dataBlock.outputValue(FloatSin::result).set(sin(value));
	dataBlock.setClean(FloatSin::result);

	return MStatus::kSuccess;
}


