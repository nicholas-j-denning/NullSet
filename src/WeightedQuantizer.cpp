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
		CIN_INPUT,
		IN_INPUT,
		DBIN_INPUT,
		DIN_INPUT,
		EBIN_INPUT,
		EIN_INPUT,
		FIN_INPUT,
		GBIN_INPUT,
		GIN_INPUT,
		ABIN_INPUT,
		AIN_INPUT,
		BBIN_INPUT,
		BIN_INPUT,
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
		configParam(C_PARAM, 0.f, 10.f, 0.f, "C");
		configParam(DB_PARAM, 0.f, 10.f, 0.f, "C#/Db");
		configParam(D_PARAM, 0.f, 10.f, 0.f, "D");
		configParam(EB_PARAM, 0.f, 10.f, 0.f, "D#/Eb");
		configParam(E_PARAM, 0.f, 10.f, 0.f, "E");
		configParam(F_PARAM, 0.f, 10.f, 0.f, "F");
		configParam(GB_PARAM, 0.f, 10.f, 0.f, "F#/Gb");
		configParam(G_PARAM, 0.f, 10.f, 0.f, "G");
		configParam(AB_PARAM, 0.f, 10.f, 0.f, "G#/Ab");
		configParam(A_PARAM, 0.f, 10.f, 0.f, "A");
		configParam(BB_PARAM, 0.f, 10.f, 0.f, "A#/Bb");
		configParam(B_PARAM, 0.f, 10.f, 0.f, "B");
		configInput(IN_INPUT, "In");
		configInput(CIN_INPUT, "C");
		configInput(DBIN_INPUT, "C#/Db");
		configInput(DIN_INPUT, "D");
		configInput(EBIN_INPUT, "D#/Eb");
		configInput(EIN_INPUT, "E");
		configInput(FIN_INPUT, "F");
		configInput(GBIN_INPUT, "F#/Gb");
		configInput(GIN_INPUT, "G");
		configInput(ABIN_INPUT, "G#/Ab");
		configInput(AIN_INPUT, "A");
		configInput(BBIN_INPUT, "A#/Bb");
		configInput(BIN_INPUT, "B");
		configOutput(OUT_OUTPUT, "Out");
	}

	std::array<float,12> param;
	float paramSum;

	void process(const ProcessArgs& args) override {
		
		if (inputs[CIN_INPUT].isConnected()){
			param[0] = math::clamp(inputs[CIN_INPUT].getVoltage(),0.f,10.f);
			params[C_PARAM].setValue(param[0]);
		} else {
			param[0] = params[C_PARAM].getValue();
		}
		if (inputs[DBIN_INPUT].isConnected()){
			param[1] = math::clamp(inputs[DBIN_INPUT].getVoltage(),0.f,10.f);
			params[DB_PARAM].setValue(param[1]);
		} else {
			param[1] = params[DB_PARAM].getValue();
		}
		if (inputs[DIN_INPUT].isConnected()){
			param[2] = math::clamp(inputs[DIN_INPUT].getVoltage(),0.f,10.f);
			params[D_PARAM].setValue(param[2]);
		} else {
			param[2] = params[D_PARAM].getValue();
		}
		if (inputs[EBIN_INPUT].isConnected()){
			param[3] = math::clamp(inputs[EBIN_INPUT].getVoltage(),0.f,10.f);
			params[EB_PARAM].setValue(param[3]);
		} else {
			param[3] = params[EB_PARAM].getValue();
		}
		if (inputs[EIN_INPUT].isConnected()){
			param[4] = math::clamp(inputs[EIN_INPUT].getVoltage(),0.f,10.f);
			params[E_PARAM].setValue(param[4]);
		} else {
			param[4] = params[E_PARAM].getValue();
		}
		if (inputs[FIN_INPUT].isConnected()){
			param[5] = math::clamp(inputs[FIN_INPUT].getVoltage(),0.f,10.f);
			params[F_PARAM].setValue(param[5]);
		} else {
			param[5] = params[F_PARAM].getValue();
		}
		if (inputs[GBIN_INPUT].isConnected()){
			param[6] = math::clamp(inputs[GBIN_INPUT].getVoltage(),0.f,10.f);
			params[GB_PARAM].setValue(param[6]);
		} else {
			param[6] = params[GB_PARAM].getValue();
		}
		if (inputs[GIN_INPUT].isConnected()){
			param[7] = math::clamp(inputs[GIN_INPUT].getVoltage(),0.f,10.f);
			params[G_PARAM].setValue(param[7]);
		} else {
			param[7] = params[G_PARAM].getValue();
		}
		if (inputs[ABIN_INPUT].isConnected()){
			param[8] = math::clamp(inputs[ABIN_INPUT].getVoltage(),0.f,10.f);
			params[AB_PARAM].setValue(param[8]);
		} else {
			param[8] = params[AB_PARAM].getValue();
		}
		if (inputs[AIN_INPUT].isConnected()){
			param[9] = math::clamp(inputs[AIN_INPUT].getVoltage(),0.f,10.f);
			params[A_PARAM].setValue(param[9]);
		} else {
			param[9] = params[A_PARAM].getValue();
		}
		if (inputs[BBIN_INPUT].isConnected()){
			param[10] = math::clamp(inputs[BBIN_INPUT].getVoltage(),0.f,10.f);
			params[BB_PARAM].setValue(param[10]);
		} else {
			param[10] = params[BB_PARAM].getValue();
		}
		if (inputs[BIN_INPUT].isConnected()){
			param[11] = math::clamp(inputs[BIN_INPUT].getVoltage(),0.f,10.f);
			params[B_PARAM].setValue(param[11]);
		} else {
			param[11] = params[B_PARAM].getValue();
		}

		paramSum = 0;
		for (int i = 0; i<12;i++){
			paramSum+=param[i];
		}

		float poly = inputs[IN_INPUT].getChannels();
		outputs[OUT_OUTPUT].setChannels(poly);
		float * in = inputs[IN_INPUT].getVoltages();

		// if no pitched are enabled, short circuit input to output
		if (paramSum==0){
			for (int i = 0; i <poly; i++){
			outputs[OUT_OUTPUT].setVoltage(in[i],i);
			}
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

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.241, 16.378)), module, WeightedQuantizer::C_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.08, 24.721)), module, WeightedQuantizer::DB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.241, 33.728)), module, WeightedQuantizer::D_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.169, 41.981)), module, WeightedQuantizer::EB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.197, 51.033)), module, WeightedQuantizer::E_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.197, 68.291)), module, WeightedQuantizer::F_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.124, 76.544)), module, WeightedQuantizer::GB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.197, 85.685)), module, WeightedQuantizer::G_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.08, 93.849)), module, WeightedQuantizer::AB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.197, 102.901)), module, WeightedQuantizer::A_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.124, 111.243)), module, WeightedQuantizer::BB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.197, 120.206)), module, WeightedQuantizer::B_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.863, 16.415)), module, WeightedQuantizer::CIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.475, 24.5)), module, WeightedQuantizer::IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(59.746, 24.712)), module, WeightedQuantizer::DBIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.863, 33.72)), module, WeightedQuantizer::DIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(59.746, 41.973)), module, WeightedQuantizer::EBIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.863, 51.025)), module, WeightedQuantizer::EIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.819, 68.327)), module, WeightedQuantizer::FIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(59.702, 76.58)), module, WeightedQuantizer::GBIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.863, 85.632)), module, WeightedQuantizer::GIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(59.746, 93.841)), module, WeightedQuantizer::ABIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.863, 102.937)), module, WeightedQuantizer::AIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(59.746, 111.191)), module, WeightedQuantizer::BBIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.863, 120.243)), module, WeightedQuantizer::BIN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.475, 111.153)), module, WeightedQuantizer::OUT_OUTPUT));
	}
};


Model* modelWeightedQuantizer = createModel<WeightedQuantizer, WeightedQuantizerWidget>("WeightedQuantizer");