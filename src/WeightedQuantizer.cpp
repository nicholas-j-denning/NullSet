#include "plugin.hpp"
#include <cmath>
#include <array>
#include <numeric>

struct WeightedQuantizer : Module {

	enum ParamId {
		C_PARAM,
		DB_PARAM,
		D_PARAM,
		EB_PARAM,
		E_PARAM,
		F_PARAM,
		GB_PARAM,
		G_PARAM,
		AB_PARAM,
		A_PARAM,
		BB_PARAM,
		B_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	WeightedQuantizer() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(C_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(D_PARAM, 0.f, 1.f, 0.f, "");
		configParam(EB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(E_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F_PARAM, 0.f, 1.f, 0.f, "");
		configParam(GB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(G_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BB_PARAM, 0.f, 1.f, 0.f, "");
		configParam(B_PARAM, 0.f, 1.f, 0.f, "");
		configInput(IN_INPUT, "");
		configOutput(OUT_OUTPUT, "");
	}

	std::array<float,12> param;
	float paramSum;

	void process(const ProcessArgs& args) override {

		// load parameters into array
		param[0] = params[C_PARAM].getValue();
		param[1] = params[DB_PARAM].getValue();
		param[2] = params[D_PARAM].getValue();
		param[3] = params[EB_PARAM].getValue();
		param[4] = params[E_PARAM].getValue();
		param[5] = params[F_PARAM].getValue();
		param[6] = params[GB_PARAM].getValue();
		param[7] = params[G_PARAM].getValue();
		param[8] = params[AB_PARAM].getValue();
		param[9] = params[A_PARAM].getValue();
		param[10] = params[BB_PARAM].getValue();
		param[11] = params[B_PARAM].getValue();

		paramSum = 0;
		for (int i = 0; i<12;i++){
			paramSum+=param[i];
		}

		float poly = inputs[IN_INPUT].getChannels();
		outputs[OUT_OUTPUT].setChannels(poly);
		float * in = inputs[IN_INPUT].getVoltages();

		// if no pitched are enabled, short circuit input to output
		if (paramSum==0){
			outputs[OUT_OUTPUT].setVoltage(in[0]);
		}
		else {
			for (int i = 0; i<poly; i++){
				float octave = std::floor(in[i]);
				float frac = in[i] - octave;
				float pitch = findPitch(frac);	
				outputs[OUT_OUTPUT].setVoltage(octave+pitch,i);
			}
		}
	}

	float findPitch(float frac){
		float sum = 0;
		for(int i = 0; i<12; i++){
			sum += param[i]/paramSum;
			if (frac<sum) return float(i)/12.f;
		}	
		return 10; //should never happen
	}
};


struct WeightedQuantizerWidget : ModuleWidget {
	WeightedQuantizerWidget(WeightedQuantizer* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/WeightedQuantizer.svg")));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 13.185)), module, WeightedQuantizer::C_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 22.45)), module, WeightedQuantizer::DB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 31.716)), module, WeightedQuantizer::D_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 40.981)), module, WeightedQuantizer::EB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 50.247)), module, WeightedQuantizer::E_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 59.512)), module, WeightedQuantizer::F_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 68.778)), module, WeightedQuantizer::GB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 78.043)), module, WeightedQuantizer::G_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 87.309)), module, WeightedQuantizer::AB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 96.574)), module, WeightedQuantizer::A_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 105.84)), module, WeightedQuantizer::BB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.991, 115.105)), module, WeightedQuantizer::B_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.12, 3.919)), module, WeightedQuantizer::IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.12, 124.371)), module, WeightedQuantizer::OUT_OUTPUT));
	}
};


Model* modelWeightedQuantizer = createModel<WeightedQuantizer, WeightedQuantizerWidget>("WeightedQuantizer");