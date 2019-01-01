/*

Droplet : FloatStackMax

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
#include "FloatStackMax.h"

// Other Includes
#include <algorithm>

// -- Declare our plugs
MObject FloatStackMax::values;
MObject FloatStackMax::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* FloatStackMax::creator()
{
    return new FloatStackMax;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus FloatStackMax::initialize()
{
    FloatStackMax n;
    dp::attributes::Create("values", float(0), n, FloatStackMax::values, true, true);
    dp::attributes::Create("result", float(0), n, FloatStackMax::result, false);

    attributeAffects(FloatStackMax::values, FloatStackMax::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus FloatStackMax::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackMax::values));

    // If there are no values our range is zero
    if (inputData.elementCount() == 0) {
        dataBlock.outputValue(FloatStackMax::result).set(0);
        dataBlock.setClean(FloatStackMax::result);
    }

    //double max = *max_element(vector.begin(), vector.end());
    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    // Define our min and max values
    float minValue = inputData.inputValue().asFloat();

    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        minValue = std::fmax(minValue, inputData.inputValue().asFloat());
    }

    // Set the output plugs and clean them (which removes
    // the dirty flag)
    dataBlock.outputValue(FloatStackMax::result).set(minValue);
    dataBlock.setClean(FloatStackMax::result);

    return MStatus::kSuccess;
}


