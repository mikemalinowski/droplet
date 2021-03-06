/*

Droplet : AngleStackMinus

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
#include "AngleStackMinus.h"

// -- Declare our plugs
MObject AngleStackMinus::values;
MObject AngleStackMinus::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* AngleStackMinus::creator()
{
    return new AngleStackMinus;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus AngleStackMinus::initialize()
{
    AngleStackMinus n;
    dp::attributes::Create("values", MAngle(0), n, AngleStackMinus::values, true, true);
    dp::attributes::Create("result", MAngle(0), n, AngleStackMinus::result, false);

    attributeAffects(AngleStackMinus::values, AngleStackMinus::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus AngleStackMinus::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(AngleStackMinus::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    double sum_of_inputs = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        float _value = inputData.inputValue().asAngle().asDegrees();
        sum_of_inputs -= _value;
    }

    dataBlock.outputValue(AngleStackMinus::result).set(MAngle(sum_of_inputs, MAngle::kDegrees));
    dataBlock.setClean(AngleStackMinus::result);

    return MStatus::kSuccess;
}


