/*

Droplet : AngleStackDivide

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
#include "AngleStackDivide.h"

// -- Declare our plugs
MObject AngleStackDivide::values;
MObject AngleStackDivide::result;


// --------------------------------------------------------
// This method returns a new instance of the node
void* AngleStackDivide::creator()
{
    return new AngleStackDivide;
}


// ---------------------------------------------------------
// This method defines all the attributes to be added to the
// node instance and how those attributes interact with one
// another.
MStatus AngleStackDivide::initialize()
{
    AngleStackDivide n;
    dp::attributes::Create("values", MAngle(0), n, AngleStackDivide::values, true, true);
    dp::attributes::Create("result", MAngle(0), n, AngleStackDivide::result, false);

    attributeAffects(AngleStackDivide::values, AngleStackDivide::result);

    return MS::kSuccess;
}


// --------------------------------------------------------
// Resolves the plug calculations
MStatus AngleStackDivide::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(AngleStackDivide::values));

    // -- Ensure we're starting the interaction at the beginning
    inputData.jumpToElement(0);

    double _result = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        float _value = inputData.inputValue().asAngle().asDegrees();

        if (_result != 0) {
            _result = 0.0000001;
        }
        _result /= _value;
    }

    dataBlock.outputValue(AngleStackDivide::result).set(MAngle(_result, MAngle::kDegrees));
    dataBlock.setClean(AngleStackDivide::result);

    return MStatus::kSuccess;
}


