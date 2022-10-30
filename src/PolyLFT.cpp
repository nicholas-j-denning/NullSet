#include "plugin.hpp"
#include <array>
#include <cmath>

struct PolyLFT : Module {
	enum ParamId {
		POLY_PARAM,
		PRATE_PARAM,
		PMIN_PARAM,
		PMAX_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IRATE_INPUT,
		IMIN_INPUT,
		IMAX_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	PolyLFT() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(POLY_PARAM, 1.f, 16.f, 1.f, "Channels");
		configParam(PRATE_PARAM, 0.1f, 500.f, 120.f, "Rate (BPM)");
		configParam(PMIN_PARAM, -10.f, 10.f, -5.f, "Min");
		configParam(PMAX_PARAM, -10.f, 10.f, 5.f, "Max");
		configInput(IRATE_INPUT, "Rate");
		configInput(IMIN_INPUT, "Min");
		configInput(IMAX_INPUT, "Max");
		configOutput(OUT_OUTPUT, "LFO");
	}

	float phase = 0.f;
	std::array<float,16> phases;

	void process(const ProcessArgs& args) override {
		float bpm;

		if (inputs[IRATE_INPUT].isConnected()){
			float in = inputs[IRATE_INPUT].getVoltage();
			bpm = 24.995f*in+250.05f;
		}
		else {
			bpm = params[PRATE_PARAM].getValue();
		}
			
		float freq = float(bpm) / 60;

		//accumulate phase
		phase += freq * args.sampleTime;
			if (phase >= 0.5f)
				phase -= 1.f;	

		int poly = std::floor(params[POLY_PARAM].getValue());

		// Equally space phases according to number of input channels
		for ( int i = 0; i<poly; i++) {
			phases[i]=phase+float(i)/float(poly);
			if (phases[i]>=0.5f) phases[i] -= 1.f;
		}		

		outputs[OUT_OUTPUT].setChannels(poly);
		for ( int i = 0; i<poly; i++){
			outputs[OUT_OUTPUT].setVoltage(triangleWave(phases[i]),i);
		}


	}

	float triangleWave(float phase){
		float result;
		if (phase >= 0) result = -phase;
		else result = phase;
		float min; 
		if (inputs[IMIN_INPUT].isConnected()){
			min = inputs[IMIN_INPUT].getVoltage();
		}
		else {
			min = params[PMIN_PARAM].getValue();
		}
		float max;
		if (inputs[IMAX_INPUT].isConnected()){
			max = inputs[IMAX_INPUT].getVoltage();
		}
		else {
			max = params[PMAX_PARAM].getValue();
		}
		return 2*(min-max)*result+min;
	}

};


struct PolyLFTWidget : ModuleWidget {
	PolyLFTWidget(PolyLFT* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/PolyLFT.svg")));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.375, 15.694)), module, PolyLFT::POLY_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.256, 34.086)), module, PolyLFT::PRATE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.256, 63.193)), module, PolyLFT::PMIN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.256, 92.299)), module, PolyLFT::PMAX_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.256, 44.7)), module, PolyLFT::IRATE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.256, 73.806)), module, PolyLFT::IMIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.256, 102.912)), module, PolyLFT::IMAX_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.348, 120.652)), module, PolyLFT::OUT_OUTPUT));
	}
};


Model* modelPolyLFT = createModel<PolyLFT, PolyLFTWidget>("PolyLFT");