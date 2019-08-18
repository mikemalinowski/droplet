/*

Droplet : Exponent

Calculates the exponent of a single float

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
#include "Exponent.h"

// -- Declare our plugs
MObject FloatExponent::inValue;
MObject FloatExponent::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatExponent::creator()
{
	return new FloatExponent;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatExponent::initialize()
{
	FloatExponent n;
	dp::attributes::Create("value", float(0), n, FloatExponent::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatExponent::result, false);

	attributeAffects(FloatExponent::inValue, FloatExponent::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatExponent::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatExponent::inValue).asFloat();
	dataBlock.outputValue(FloatExponent::result).set(exp(value));
	dataBlock.setClean(FloatExponent::result);

	return MStatus::kSuccess;
}


