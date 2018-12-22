/*

Droplet : FloatStackMin

This takes in a list of values and return the smallest
of all the values

Author : Mike Malinowski : www.twisted.space

*/
// -- Maya Includes
#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericAttribute.h>

// -- Droplet Includes
#include "FloatStackMin.h"

// Other Includes
#include <algorithm>

// -- Declare our plugs
MObject FloatStackMin::values;
MObject FloatStackMin::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatStackMin::creator()
{
    return new FloatStackMin;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatStackMin::initialize()
{
    FloatStackMin n;
    dp::attributes::Create("values", float(0), n, FloatStackMin::values, true, true);
    dp::attributes::Create("result", float(0), n, FloatStackMin::result, false);

    attributeAffects(FloatStackMin::values, FloatStackMin::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatStackMin::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackMin::values));

    // If there are no values our range is zero
    if (inputData.elementCount() == 0) {
        dataBlock.outputValue(FloatStackMin::result).set(0);
        dataBlock.setClean(FloatStackMin::result);
    }

    //double max = *max_element(vector.begin(), vector.end());
    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    // Define our min and max values
    float minValue = inputData.inputValue().asFloat();

    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        minValue = std::fmin(minValue, inputData.inputValue().asFloat());
    }

    // Set the output plugs and clean them (which removes
    // the dirty flag)
    dataBlock.outputValue(FloatStackMin::result).set(minValue);
    dataBlock.setClean(FloatStackMin::result);

    return MStatus::kSuccess;
}


