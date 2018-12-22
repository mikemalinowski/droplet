/*

Droplet : FloatStackSum

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
#include "FloatStackSum.h"

// -- Declare our plugs
MObject FloatStackSum::values;
MObject FloatStackSum::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatStackSum::creator()
{
    return new FloatStackSum;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatStackSum::initialize()
{
    FloatStackSum n;
    dp::attributes::Create("values", float(0), n, FloatStackSum::values, true, true);
    dp::attributes::Create("result", float(0), n, FloatStackSum::result, false);

    attributeAffects(FloatStackSum::values, FloatStackSum::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatStackSum::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackSum::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    float result = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        result += inputData.inputValue().asFloat();
    }
    
    dataBlock.outputValue(FloatStackSum::result).set(result);
    dataBlock.setClean(FloatStackSum::result);

    return MStatus::kSuccess;
}


