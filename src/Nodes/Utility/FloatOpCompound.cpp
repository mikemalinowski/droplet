/*

Droplet : FloatOpCompound

This takes in a list of values and performs the operation
sequentially through them.

Author : Mike Malinowski : www.twisted.space

*/
// -- Maya Includes
#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MDataBlock.h>
#include <maya/MArrayDataHandle.h>

// -- Droplet Includes
#include "FloatOpCompound.h"

// -- Declare our plugs
MObject FloatOpCompound::values;
MObject FloatOpCompound::operation;
MObject FloatOpCompound::result;


/* ---------------------------------------------------------------------- */
void* FloatOpCompound::creator()
{
	return new FloatOpCompound;
}


/* ---------------------------------------------------------------------- */
MStatus FloatOpCompound::initialize()
{
	MFnNumericAttribute  numericAttrFn;
	MFnEnumAttribute     enumAttrFn;

	FloatOpCompound::values = numericAttrFn.create("values", "val", MFnNumericData::kFloat);
	numericAttrFn.setArray(true);
	numericAttrFn.setKeyable(true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(FloatOpCompound::values), MStatus::kFailure);

	FloatOpCompound::operation = enumAttrFn.create("operation", "op");
	enumAttrFn.addField("addition", 0);
	enumAttrFn.addField("subtraction", 1);
	enumAttrFn.addField("multiplication", 2);
	CHECK_MSTATUS_AND_RETURN(addAttribute(FloatOpCompound::operation), MStatus::kFailure);

	FloatOpCompound::result = numericAttrFn.create("result", "res", MFnNumericData::kFloat);
	CHECK_MSTATUS_AND_RETURN(addAttribute(FloatOpCompound::result), MStatus::kFailure);

	attributeAffects(FloatOpCompound::values, FloatOpCompound::result);
	attributeAffects(FloatOpCompound::operation, FloatOpCompound::result);

	return MS::kSuccess;
}

/* ---------------------------------------------------------------------- */
MStatus FloatOpCompound::compute(const MPlug& plug, MDataBlock& dataBlock)
{
	// -- Get the value array handle
	MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatOpCompound::values));

	// -- Get the Operation index
	int opIndex = dataBlock.inputValue(FloatOpCompound::operation).asInt();

	// -- Ensure we're starting the interation at the begining
	inputData.jumpToElement(0);

	float tracking_value = 0;
	for (int i = 0; i < inputData.elementCount(); i++, inputData.next())
	{
		float input = inputData.inputValue().asFloat();

		if (opIndex == 0)
			tracking_value += input;
		if (opIndex == 1)
			tracking_value -= input;
		if (opIndex == 2)
			tracking_value *= input;
	}
	dataBlock.outputValue(FloatOpCompound::result).set(tracking_value);
	
	return MStatus::kSuccess;
}


