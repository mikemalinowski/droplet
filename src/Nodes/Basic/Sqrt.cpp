/*

Droplet : Sqrt

Calculates the square root of a single float

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
#include "Sqrt.h"

// -- Declare our plugs
MObject FloatSqrt::inValue;
MObject FloatSqrt::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatSqrt::creator()
{
	return new FloatSqrt;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatSqrt::initialize()
{
	FloatSqrt n;
	dp::attributes::Create("value", float(0), n, FloatSqrt::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatSqrt::result, false);

	attributeAffects(FloatSqrt::inValue, FloatSqrt::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatSqrt::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatSqrt::inValue).asFloat();
	dataBlock.outputValue(FloatSqrt::result).set(sqrt(value));
	dataBlock.setClean(FloatSqrt::result);

	return MStatus::kSuccess;
}


