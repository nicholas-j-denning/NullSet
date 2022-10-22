#include "plugin.hpp"
#include <array>

struct QuickMelody : Module {
	enum ParamId {
		PATTERN_PARAM,
		MIN_PARAM,
		MAX_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
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
		configParam(PATTERN_PARAM, 0.f, 1.f, 0.f, "");
		configParam(MIN_PARAM, -10.f, 10.f, -5.f, "");
		configParam(MAX_PARAM, -10.f, 10.f, 5.f, "");
		configInput(CLOCK_INPUT, "");
		configOutput(OUT_OUTPUT, "");
		random::init();
		float r = random::uniform();
		freq = dsp::FREQ_A4 * std::pow(2.f, 3.f*r);
		divider.setDivision(32);
	}

	//main phase of the generator
	float phase = 0.f;

	//phases of the different channels
	std::array<float,16> phases;

	//frequency of the generator
	float freq;
	
	std::array<dsp::SchmittTrigger,16> clockTrigger;
	dsp::SchmittTrigger patternTrigger;

	//divide samplerate for CPU
	dsp::ClockDivider divider;

	void process(const ProcessArgs& args) override {
		
		// process only every 32 samples
		if (divider.process()){
			// Accumulate phase
			phase += freq * args.sampleTime;
			if (phase >= 1.f)
				phase -= 1.f;

			// New Random pattern on button press
			if (params[PATTERN_PARAM].getValue()){
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
					float min = params[MIN_PARAM].getValue();
					float max = params[MAX_PARAM].getValue();
					float m = max - min;
					float b = min;
					float out = m*phases[i]+b;
					outputs[OUT_OUTPUT].setVoltage(out,i);
				}
			}
		}
	}
};


struct QuickMelodyWidget : ModuleWidget {
	QuickMelodyWidget(QuickMelody* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/QuickMelody.svg")));

		addParam(createParamCentered<VCVButton>(mm2px(Vec(10.16, 37.435)), module, QuickMelody::PATTERN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 61.742)), module, QuickMelody::MIN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 87.113)), module, QuickMelody::MAX_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 15.452)), module, QuickMelody::CLOCK_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 111.952)), module, QuickMelody::OUT_OUTPUT));
	}
};


Model* modelQuickMelody = createModel<QuickMelody, QuickMelodyWidget>("QuickMelody");