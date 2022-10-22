#include "plugin.hpp"
#include <array>


struct PolyAutoPan : Module {
	enum ParamId {
		RATE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		RIGHT_OUTPUT,
		LEFT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	PolyAutoPan() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(RATE_PARAM, 1.f, 500.f, 120.f, "");
		configInput(IN_INPUT, "");
		configOutput(RIGHT_OUTPUT, "");
		configOutput(LEFT_OUTPUT, "");
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

		int poly = inputs[IN_INPUT].getChannels();

		// Equally space phases according to number of input channels
		for ( int i = 0; i<poly; i++) {
			phases[i]=phase+float(i)/float(poly);
			if (phases[i]>=0.5f) phases[i] -= 1.f;
		}		

		float left = 0;
		float right = 0;
		
		for ( int i = 0; i<poly; i++) {
			float in = inputs[IN_INPUT].getVoltage(i);	
			left += in*triangleWave(phases[i]);
			right += in*(1-triangleWave(phases[i]));
		}
		outputs[LEFT_OUTPUT].setVoltage(left);
		outputs[RIGHT_OUTPUT].setVoltage(right);
	}

	float triangleWave(float phase){
		float result;
		if (phase >= 0) result = -phase;
		else result = phase;
		return 2*result+1;
	}
};


struct PolyAutoPanWidget : ModuleWidget {
	PolyAutoPanWidget(PolyAutoPan* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/PolyAutoPan.svg")));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(9.805, 64.048)), module, PolyAutoPan::RATE_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 15.452)), module, PolyAutoPan::IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.79, 112.306)), module, PolyAutoPan::RIGHT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(13.951, 112.306)), module, PolyAutoPan::LEFT_OUTPUT));
	}
};


Model* modelPolyAutoPan = createModel<PolyAutoPan, PolyAutoPanWidget>("PolyAutoPan");