/*

Droplet : FloatStackDivide

This takes in a list of values and multiply them all
together and return the result

Author : Mike Malinowski : www.twisted.space

*/
// -- Maya Includes
#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericAttribute.h>

// -- Droplet Includes
#include "FloatStackDivide.h"

// -- Declare our plugs
MObject FloatStackDivide::values;
MObject FloatStackDivide::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatStackDivide::creator()
{
    return new FloatStackDivide;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatStackDivide::initialize()
{
    FloatStackDivide n;
    dp::attributes::Create("values", float(0), n, FloatStackDivide::values, true, true);
    dp::attributes::Create("result", float(0), n, FloatStackDivide::result, false);

    attributeAffects(FloatStackDivide::values, FloatStackDivide::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatStackDivide::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackDivide::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    float result = 1;

    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        float value = inputData.inputValue().asFloat();

        if (value != 0) {
            value = 0.0000001;
        }
        result /= value;
    }

    dataBlock.outputValue(FloatStackDivide::result).set(result);
    dataBlock.setClean(FloatStackDivide::result);

    return MStatus::kSuccess;
}


