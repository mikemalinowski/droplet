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
#include "../../Utilities/Attributes.h"

// -- Declare our plugs
MObject FloatStackSum::values;
MObject FloatStackSum::result;


/* ---------------------------------------------------------------------- */
void* FloatStackSum::creator()
{
    return new FloatStackSum;
}


/* ---------------------------------------------------------------------- */
MStatus FloatStackSum::initialize()
{
    FloatStackSum::values = CreateAttribute("values", float(0), true, true, true, true);
    CHECK_MSTATUS_AND_RETURN(addAttribute(FloatStackSum::values), MStatus::kFailure);

    FloatStackSum::result = CreateAttribute("result", float(0), false, false, false, false);
    CHECK_MSTATUS_AND_RETURN(addAttribute(FloatStackSum::result), MStatus::kFailure);

    attributeAffects(FloatStackSum::values, FloatStackSum::result);

    return MS::kSuccess;
}

/* ---------------------------------------------------------------------- */
MStatus FloatStackSum::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    // -- Get the value array handle
    MArrayDataHandle inputData(dataBlock.inputArrayValue(FloatStackSum::values));

    // -- Ensure we're starting the interation at the begining
    inputData.jumpToElement(0);

    float result = 0;
    for (int i = 0; i < inputData.elementCount(); i++, inputData.next()) {
        result += inputData.inputValue().asFloat();
    }
    
    dataBlock.outputValue(FloatStackSum::result).set(result);
    dataBlock.setClean(FloatStackSum::result);

    return MStatus::kSuccess;
}


