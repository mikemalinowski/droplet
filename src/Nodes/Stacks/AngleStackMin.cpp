/*

Droplet : AngleStackMin

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
#include "AngleStackMin.h"

// -- Declare our plugs
MObject AngleStackMin::values;
MObject AngleStackMin::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* AngleStackMin::creator()
{
    return new AngleStackMin;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus AngleStackMin::initialize()
{
    AngleStackMin n;
    dp::attributes::Create("values", MAngle(0), n, AngleStackMin::values, true, true);
    dp::attributes::Create("result", MAngle(0), n, AngleStackMin::result, false);

    attributeAffects(AngleStackMin::values, AngleStackMin::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus AngleStackMin::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(AngleStackMin::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    double minValue = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        minValue = std::fmin(minValue, inputData.inputValue().asAngle().asDegrees());
    }

    dataBlock.outputValue(AngleStackMin::result).set(MAngle(minValue, MAngle::kDegrees));
    dataBlock.setClean(AngleStackMin::result);

    return MStatus::kSuccess;
}


