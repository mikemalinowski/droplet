/*

Droplet : AngleStackRange

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

// Other Includes
#include <algorithm>

// -- Droplet Includes
#include "AngleStackRange.h"

// -- Declare our plugs
MObject AngleStackRange::values;
MObject AngleStackRange::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* AngleStackRange::creator()
{
    return new AngleStackRange;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus AngleStackRange::initialize()
{
    AngleStackRange n;
    dp::attributes::Create("values", MAngle(0), n, AngleStackRange::values, true, true);
    dp::attributes::Create("result", MAngle(0), n, AngleStackRange::result, false);

    attributeAffects(AngleStackRange::values, AngleStackRange::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus AngleStackRange::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(AngleStackRange::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    // Define our min and max values
    double minValue = inputData.inputValue().asAngle().asDegrees();
    double maxValue = inputData.inputValue().asAngle().asDegrees();

    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        double currentValue = inputData.inputValue().asAngle().asDegrees();
        minValue = std::fmin(minValue, currentValue);
        maxValue = std::fmax(maxValue, currentValue);
    }

    // Get the range between the two values
    double range = maxValue - minValue;
    dataBlock.outputValue(AngleStackRange::result).set(MAngle(range, MAngle::kDegrees));
    dataBlock.setClean(AngleStackRange::result);

    return MStatus::kSuccess;
}


