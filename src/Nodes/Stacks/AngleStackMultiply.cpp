/*

Droplet : AngleStackMultiply

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
#include "AngleStackMultiply.h"

// -- Declare our plugs
MObject AngleStackMultiply::values;
MObject AngleStackMultiply::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* AngleStackMultiply::creator()
{
    return new AngleStackMultiply;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus AngleStackMultiply::initialize()
{
    AngleStackMultiply n;
    dp::attributes::Create("values", MAngle(0), n, AngleStackMultiply::values, true, true);
    dp::attributes::Create("result", MAngle(0), n, AngleStackMultiply::result, false);

    attributeAffects(AngleStackMultiply::values, AngleStackMultiply::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus AngleStackMultiply::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(AngleStackMultiply::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    double sum_of_inputs = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        float _value = inputData.inputValue().asAngle().asDegrees();
        sum_of_inputs *= _value;
    }

    dataBlock.outputValue(AngleStackMultiply::result).set(MAngle(sum_of_inputs, MAngle::kDegrees));
    dataBlock.setClean(AngleStackMultiply::result);

    return MStatus::kSuccess;
}


