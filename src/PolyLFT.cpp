#include "plugin.hpp"
#include <array>
#include <cmath>

struct PolyLFT : Module {
	enum ParamId {
		CHANNELS_PARAM,
		RATE_PARAM,
		MIN_PARAM,
		MAX_PARAM,
		PARAMS_LEN
	};
	enum InputId {
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
		configParam(CHANNELS_PARAM, 1.f, 16.f, 1.f, "test");
		configParam(RATE_PARAM, 1.f, 500.f, 120.f, "");
		configParam(MIN_PARAM, -10.f, 10.f, -5.f, "");
		configParam(MAX_PARAM, -10.f, 10.f, 5.f, "");
		configOutput(OUT_OUTPUT, "");
	}

	float phase = 0.f;
	std::array<float,16> phases;

	void process(const ProcessArgs& args) override {
		int bpm = params[RATE_PARAM].getValue();
		float freq = float(bpm) / 60;

		//accumulate phase
		phase += freq * args.sampleTime;
			if (phase >= 0.5f)
				phase -= 1.f;	

		int poly = std::floor(params[CHANNELS_PARAM].getValue());

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
		float min = params[MIN_PARAM].getValue();
		float max = params[MAX_PARAM].getValue();
		return 2*(min-max)*result+min;
	}
};


struct PolyLFTWidget : ModuleWidget {
	PolyLFTWidget(PolyLFT* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/PolyLFT.svg")));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 15.452)), module, PolyLFT::CHANNELS_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 37.435)), module, PolyLFT::RATE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 61.742)), module, PolyLFT::MIN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 87.113)), module, PolyLFT::MAX_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 111.952)), module, PolyLFT::OUT_OUTPUT));
	}
};


Model* modelPolyLFT = createModel<PolyLFT, PolyLFTWidget>("PolyLFT");