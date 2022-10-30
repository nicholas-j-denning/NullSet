// TODO: QuickMelody State, polylf inputs, autopan rate input, 16 squared copy/paste step
// Visuals: vcv knobs/buttons/lights/ports, add bobaudio sytle knob ranges+values, empty set logo bottom, name top, box trigger/inputs, box outputs
// Component labels: Futura PT Medium 12pt
// Module Labels: Futura PT Normal 12pt, line spacing 0.8, 1 mm from top
// Logo: Futura PT Normal 10pt
/*
bg: 847b89ff
name text: 000000ff
logo: f7dfffff
lightbox bg: d2d2d2ff
lightbox border: 594c62ff
lightbox text: f7dfffff
darkbox bg: 220826ff
darkbox border: efd4f9ff
darkbox text: 7d46a7ff
*/

#include "plugin.hpp"


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	p->addModel(modelQuickMelody);
	p->addModel(modelPolyAutoPan);
	p->addModel(modelWeightedQuantizer);
	p->addModel(modelPolyLFT);
	p->addModel(model_16Squared);
	p->addModel(modelLabeledPatchbay);
	p->addModel(modelPulsar);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
