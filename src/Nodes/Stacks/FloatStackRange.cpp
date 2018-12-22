/*

Droplet : FloatStackRange

This takes in a list of values and takes the floor and
cieling and gives the absolute of the delta between them

Author : Mike Malinowski : www.twisted.space

*/
// -- Maya Includes
#include <maya/MPxNode.h>
#include <maya/MDataBlock.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericAttribute.h>

// -- Droplet Includes
#include "FloatStackRange.h"

// Other Includes
#include <algorithm>

// -- Declare our plugs
MObject FloatStackRange::values;
MObject FloatStackRange::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatStackRange::creator()
{
    return new FloatStackRange;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatStackRange::initialize()
{
    FloatStackRange n;
    dp::attributes::Create("values", float(0), n, FloatStackRange::values, true, true);
    dp::attributes::Create("result", float(0), n, FloatStackRange::result, false);

    attributeAffects(FloatStackRange::values, FloatStackRange::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatStackRange::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackRange::values));

    // If there are no values our range is zero
    if (inputData.elementCount() == 0) {
        dataBlock.outputValue(FloatStackRange::result).set(0);
        dataBlock.setClean(FloatStackRange::result);
    }

    //double max = *max_element(vector.begin(), vector.end());
    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    // Define our min and max values
    float minValue = inputData.inputValue().asFloat();
    float maxValue = inputData.inputValue().asFloat();

    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        float currentValue = inputData.inputValue().asFloat();
        minValue = std::fmin(minValue, currentValue);
        maxValue = std::fmax(maxValue, currentValue);
    }

    // Get the range between the two values
    float range = maxValue - minValue;

    // Set the output plugs and clean them (which removes
    // the dirty flag)
    dataBlock.outputValue(FloatStackRange::result).set(range);
    dataBlock.setClean(FloatStackRange::result);

    return MStatus::kSuccess;
}


