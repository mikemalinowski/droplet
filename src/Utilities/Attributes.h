//
// Created by mikem on 18/12/2018.
//
#pragma once

#include <maya/MStatus.h>
#include <maya/MFnAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MObject.h>
#include <vector>

inline void SetAttributeProperties(MFnAttribute& attrFn, bool isArray=false, bool isKeyable=true, bool isWritable=true, bool isStorable=true)
{
    attrFn.setArray(isArray);
    attrFn.setKeyable(isKeyable);
    attrFn.setArray(isArray);
    attrFn.setWritable(isWritable);
    attrFn.setStorable(isStorable);

}

inline MObject CreateAttribute(const char* name, float value, bool isKeyable=true, bool isWritable=true, bool isArray=false, bool isStorable=true)
{

    MFnNumericAttribute numericAttrFn;

    // -- Create the attribute
    MObject attr = numericAttrFn.create(name, name, MFnNumericData::kFloat, value);

    // -- Set the attribute properties
    SetAttributeProperties(
        numericAttrFn,
        isArray,
        isKeyable,
        isWritable,
        isStorable
    );

    return attr;
}

inline MObject CreateAttribute(const char* name, std::vector<const char*> values, bool isKeyable=true, bool isWritable=true, bool isArray=false, bool isStorable=true)
{

    MFnEnumAttribute enumFn;

    // -- Create the attribute
    MObject attr = enumFn.create(name, name);

    // -- Set the attribute properties
    SetAttributeProperties(
        enumFn,
        isArray,
        isKeyable,
        isWritable,
        isStorable
    );

    // -- Add all the enumerators
    short index = 0;
    for(const char* item: values) {
        enumFn.addField(item, index);
        index++;
    }

    return attr;
}