/*

Droplet : Power

Calculates the power of a single float

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
#include "Power.h"

// -- Declare our plugs
MObject FloatPower::inValue;
MObject FloatPower::inPower;
MObject FloatPower::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatPower::creator()
{
	return new FloatPower;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatPower::initialize()
{
	FloatPower n;
	dp::attributes::Create("value", float(0), n, FloatPower::inValue, true, false);
	dp::attributes::Create("power", float(0), n, FloatPower::inPower, true, false);

	dp::attributes::Create("result", float(0), n, FloatPower::result, false);

	attributeAffects(FloatPower::inValue, FloatPower::result);
	attributeAffects(FloatPower::inPower, FloatPower::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatPower::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	// -- Get the value array handle
	float value = dataBlock.inputValue(FloatPower::inValue).asFloat();
	float power = dataBlock.inputValue(FloatPower::inPower).asFloat();

	float calculated_result = pow(value, power);
	dataBlock.outputValue(FloatPower::result).set(calculated_result);
	dataBlock.setClean(FloatPower::result);

	return MStatus::kSuccess;
}


