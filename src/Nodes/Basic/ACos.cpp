/*

Droplet : ACos

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
#include "ACos.h"

// -- Declare our plugs
MObject FloatACos::inValue;
MObject FloatACos::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatACos::creator()
{
	return new FloatACos;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatACos::initialize()
{
	FloatACos n;
	dp::attributes::Create("value", float(0), n, FloatACos::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatACos::result, false);

	attributeAffects(FloatACos::inValue, FloatACos::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatACos::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatACos::inValue).asFloat();
	dataBlock.outputValue(FloatACos::result).set(acos(value));
	dataBlock.setClean(FloatACos::result);

	return MStatus::kSuccess;
}


