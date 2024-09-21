#include "plugin.hpp"

Plugin* pluginInstance;

void init(Plugin* p) {
	pluginInstance = p;

	p->addModel(modelQuickMelody);
	p->addModel(modelPolyAutoPan);
	p->addModel(modelWeightedQuantizer);
	p->addModel(modelPolyLFT);
	p->addModel(model_16Squared);
	p->addModel(modelLabeledPatchbay);
	p->addModel(modelRomanQuantizer); 
	
	p->addModel(modelMajorPalette);
	p->addModel(modelPaletteQuantizer);
}
