/*

Droplet : AngleStackMax

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
#include "AngleStackMax.h"

// -- Declare our plugs
MObject AngleStackMax::values;
MObject AngleStackMax::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* AngleStackMax::creator()
{
    return new AngleStackMax;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus AngleStackMax::initialize()
{
    AngleStackMax n;
    dp::attributes::Create("values", MAngle(0), n, AngleStackMax::values, true, true);
    dp::attributes::Create("result", MAngle(0), n, AngleStackMax::result, false);

    attributeAffects(AngleStackMax::values, AngleStackMax::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus AngleStackMax::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(AngleStackMax::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    double maxValue = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        maxValue = std::fmax(maxValue, inputData.inputValue().asAngle().asDegrees());
    }

    dataBlock.outputValue(AngleStackMax::result).set(MAngle(maxValue, MAngle::kDegrees));
    dataBlock.setClean(AngleStackMax::result);

    return MStatus::kSuccess;
}


