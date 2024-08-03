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

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
