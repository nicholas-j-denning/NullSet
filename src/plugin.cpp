// TODO: 16 squared copy/paste step
// TODO: make 16Squared step change when step is lowered like ROman
// TODO: change plugin knobs to stepped as needed
// TODO: Wavtetable VCO, with serum like inteface, load wavtable folder, random selection, table hybridization
// TODO: exponential rhythm generator,
// TODO: convolutional/granular cross synthesis
// TODO: Grainset: open multiple files, granulate. Can arrage by various properties such as spectral centroid
// TODO: Polyphonic waveguide resonator
// TODO: Bon Iver style voice tuner
// TODO: 16 random constants on a poly cable, set range, button/trigger to randomize
// TODO: poly waveguide physical modeling synthesis


// Visuals: vcv knobs/buttons/lights/ports, add bobaudio sytle knob ranges+values, empty set logo bottom, name top, box trigger/inputs, box outputs
// Component labels: Futura PT Medium 10pt
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
	p->addModel(modelRomanQuantizer);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
