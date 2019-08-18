/*

Droplet : Cos

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
#include "Cos.h"

// -- Declare our plugs
MObject FloatCos::inValue;
MObject FloatCos::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatCos::creator()
{
	return new FloatCos;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatCos::initialize()
{
	FloatCos n;
	dp::attributes::Create("value", float(0), n, FloatCos::inValue, true, false);
	dp::attributes::Create("result", float(0), n, FloatCos::result, false);

	attributeAffects(FloatCos::inValue, FloatCos::result);

	return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatCos::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	float value = dataBlock.inputValue(FloatCos::inValue).asFloat();
	dataBlock.outputValue(FloatCos::result).set(cos(value));
	dataBlock.setClean(FloatCos::result);

	return MStatus::kSuccess;
}


