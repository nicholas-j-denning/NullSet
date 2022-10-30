#include "plugin.hpp"
#include <array>

struct PolyAutoPan : Module {
	enum ParamId {
		PRATE_PARAM,
		TRIM_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_INPUT,
		IRATE_INPUT,
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
		configParam(PRATE_PARAM, 0.1f, 500.f, 120.f, "Rate (BPM)");
		configParam(TRIM_PARAM, 0.f, 2.f, 1.f, "Trim");
		configInput(IN_INPUT, "In");
		configInput(IRATE_INPUT, "Rate");
		configOutput(RIGHT_OUTPUT, "Right");
		configOutput(LEFT_OUTPUT, "Left");
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

		left *= params[TRIM_PARAM].getValue();
		right *= params[TRIM_PARAM].getValue();

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

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.186, 44.605)), module, PolyAutoPan::PRATE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.305, 79.447)), module, PolyAutoPan::TRIM_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.186, 19.266)), module, PolyAutoPan::IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.186, 54.867)), module, PolyAutoPan::IRATE_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.186, 105.173)), module, PolyAutoPan::RIGHT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.186, 115.776)), module, PolyAutoPan::LEFT_OUTPUT));
	}
};


Model* modelPolyAutoPan = createModel<PolyAutoPan, PolyAutoPanWidget>("PolyAutoPan");