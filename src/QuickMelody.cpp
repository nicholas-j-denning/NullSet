#include "plugin.hpp"
#include <array>

struct QuickMelody : Module {
	enum ParamId {
		PPATTERN_PARAM,
		PMAX_PARAM,
		PMIN_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
		IPATTERN_INPUT,
		IMAX_INPUT,
		IMIN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	QuickMelody() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(PPATTERN_PARAM, 0.f, 1.f, 0.f, "New Pattern");
		configParam(PMAX_PARAM, -10.f, 10.f, -5.f, "Max");
		configParam(PMIN_PARAM, -10.f, 10.f, 5.f, "Min");
		configInput(CLOCK_INPUT, "Clock");
		configInput(IPATTERN_INPUT, "New Pattern");
		configInput(IMAX_INPUT, "Max");
		configInput(IMIN_INPUT, "Min");
		configOutput(OUT_OUTPUT, "Sequence");
		random::init();
		float r = random::uniform();
		freq = dsp::FREQ_A4 * std::pow(2.f, 3.f*r);
	}

	//main phase of the generator
	float phase = 0.f;

	//phases of the different channels
	std::array<float,16> phases;

	//frequency of the generator
	float freq;
	
	std::array<dsp::SchmittTrigger,16> clockTrigger;
	dsp::SchmittTrigger patternTrigger;

	void process(const ProcessArgs& args) override {
		
		// Accumulate phase
		phase += freq * args.sampleTime;
		if (phase >= 1.f)
			phase -= 1.f;

		// New Random pattern on button press
		if (params[PPATTERN_PARAM].getValue()){
			float r = random::uniform();
			freq = dsp::FREQ_A4 * std::pow(2.f, 3.f*r);
		}

		float patt = inputs[IPATTERN_INPUT].getVoltage();
		// New Random pattern on trigger
		if (patternTrigger.process(rescale(patt, 0.1f, 2.f, 0.f, 1.f))){
			float r = random::uniform();
			freq = dsp::FREQ_A4 * std::pow(2.f, 3.f*r);
		}

		//configure polyphony
		int poly = inputs[CLOCK_INPUT].getChannels();
		outputs[OUT_OUTPUT].setChannels(poly);

		// Equally space phases according to number of input channels
		for ( int i = 0; i<poly; i++) {
			phases[i]=phase+float(i)/float(poly);
			if (phases[i]>=1.f) phases[i] -= 1.f;
		}

		// Change notes on clock trigger
		for ( int i = 0; i<poly; i++) {
			float in = inputs[CLOCK_INPUT].getVoltage(i);
			if (clockTrigger[i].process(rescale(in, 0.1f, 2.f, 0.f, 1.f))){
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
				float m = max - min;
				float b = min;
				float out = m*phases[i]+b;
				outputs[OUT_OUTPUT].setVoltage(out,i);
			}
		}
	}

	json_t* dataToJson() override {
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "freq", json_real(freq));
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {
		json_t * freqJ = json_object_get(rootJ, "freq");
		if (freqJ)
			freq = json_real_value(freqJ);
	}
};


struct QuickMelodyWidget : ModuleWidget {
	QuickMelodyWidget(QuickMelody* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/QuickMelody.svg")));

		addParam(createParamCentered<VCVButton>(mm2px(Vec(10.447, 36.934)), module, QuickMelody::PPATTERN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.447, 65.236)), module, QuickMelody::PMAX_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.447, 93.589)), module, QuickMelody::PMIN_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.447, 19.038)), module, QuickMelody::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.447, 47.924)), module, QuickMelody::IPATTERN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.447, 75.581)), module, QuickMelody::IMAX_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.447, 104.589)), module, QuickMelody::IMIN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.447, 121.854)), module, QuickMelody::OUT_OUTPUT));
	}
};


Model* modelQuickMelody = createModel<QuickMelody, QuickMelodyWidget>("QuickMelody");