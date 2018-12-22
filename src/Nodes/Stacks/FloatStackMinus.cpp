/*

Droplet : FloatStackMinus

This takes in a list of values and performs a subtraction
sequentially through them.

Author : Mike Malinowski : www.twisted.space

*/
// -- Maya Includes
#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MArrayDataHandle.h>

// -- Droplet Includes
#include "FloatStackMinus.h"

// -- Declare our plugs
MObject FloatStackMinus::values;
MObject FloatStackMinus::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatStackMinus::creator()
{
    return new FloatStackMinus;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatStackMinus::initialize()
{
    FloatStackMinus n;
    dp::attributes::Create("values", float(0), n, FloatStackMinus::values, true, true);
    dp::attributes::Create("result", float(0), n, FloatStackMinus::result, false);

    attributeAffects(FloatStackMinus::values, FloatStackMinus::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatStackMinus::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackMinus::values));

    // -- Ensure we're starting the interation at the begining
    inputData.jumpToElement(0);

    float result = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        result -= inputData.inputValue().asFloat();
    }

    dataBlock.outputValue(FloatStackMinus::result).set(result);
    dataBlock.setClean(FloatStackMinus::result);

    return MStatus::kSuccess;
}


