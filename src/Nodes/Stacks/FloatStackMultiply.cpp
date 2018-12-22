/*

Droplet : FloatStackMultiply

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
#include "FloatStackMultiply.h"

// -- Declare our plugs
MObject FloatStackMultiply::values;
MObject FloatStackMultiply::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatStackMultiply::creator()
{
    return new FloatStackMultiply;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatStackMultiply::initialize()
{
    FloatStackMultiply n;
    dp::attributes::Create("values", float(0), n, FloatStackMultiply::values, true, true);
    dp::attributes::Create("result", float(0), n, FloatStackMultiply::result, false);

    attributeAffects(FloatStackMultiply::values, FloatStackMultiply::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatStackMultiply::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackMultiply::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    float result = 1;

    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        result *= inputData.inputValue().asFloat();
    }

    dataBlock.outputValue(FloatStackMultiply::result).set(result);
    dataBlock.setClean(FloatStackMultiply::result);

    return MStatus::kSuccess;
}


