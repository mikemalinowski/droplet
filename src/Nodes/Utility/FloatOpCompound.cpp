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
#include "../../Utilities/Attributes.h"

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
	FloatOpCompound::values = CreateAttribute("values", float(0), true, true, true, true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(FloatOpCompound::values), MStatus::kFailure);

	std::vector<const char*> labels = {"Addition", "Subtraction", "Multiplication"};
	FloatOpCompound::operation = CreateAttribute("operation", labels, false, true, false, true);
	CHECK_MSTATUS_AND_RETURN(addAttribute(FloatOpCompound::operation), MStatus::kFailure);

	FloatOpCompound::result = CreateAttribute("result", float(0), false, false, false, false);
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

	float result = 0;
	for (int i = 0; i < inputData.elementCount(); i++, inputData.next())
	{
		float input = inputData.inputValue().asFloat();

		if (opIndex == 0)
			result += input;
		if (opIndex == 1)
			result -= input;
		if (opIndex == 2)
			result *= input;
	}
	dataBlock.outputValue(FloatOpCompound::result).set(result);
	dataBlock.setClean(FloatOpCompound::result);

	return MStatus::kSuccess;
}


