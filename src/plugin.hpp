#pragma once
#include <rack.hpp>


using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern Model* modelQuickMelody;
extern Model* modelPolyAutoPan;
extern Model* modelWeightedQuantizer;
extern Model* modelPolyLFT;
extern Model* model_16Squared;
extern Model* modelLabeledPatchbay;
extern Model* modelRomanQuantizer;
