#include "plugin.hpp"


struct _16Squared : Module {
	enum ParamId {
		STEPS_PARAM,
		CHANNELS_PARAM,
		FORWARD_PARAM,
		BACK_PARAM,
		RESET_PARAM,
		_1_PARAM,
		_2_PARAM,
		_3_PARAM,
		_4_PARAM,
		_5_PARAM,
		_6_PARAM,
		_7_PARAM,
		_8_PARAM,
		_9_PARAM,
		_10_PARAM,
		_11_PARAM,
		_12_PARAM,
		_13_PARAM,
		_14_PARAM,
		_15_PARAM,
		_16_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		FORWARDIN_INPUT,
		BACKIN_INPUT,
		RESETIN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		L1_LIGHT,
		L2_LIGHT,
		L3_LIGHT,
		L4_LIGHT,
		L5_LIGHT,
		L6_LIGHT,
		L7_LIGHT,
		L8_LIGHT,
		L9_LIGHT,
		L10_LIGHT,
		L11_LIGHT,
		L12_LIGHT,
		L13_LIGHT,
		L14_LIGHT,
		L15_LIGHT,
		L16_LIGHT,
		LIGHTS_LEN
	};

	_16Squared() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(STEPS_PARAM, 0.f, 1.f, 0.f, "");
		configParam(CHANNELS_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FORWARD_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BACK_PARAM, 0.f, 1.f, 0.f, "");
		configParam(RESET_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_6_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_7_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_8_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_9_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_10_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_11_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_12_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_13_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_14_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_15_PARAM, 0.f, 1.f, 0.f, "");
		configParam(_16_PARAM, 0.f, 1.f, 0.f, "");
		configInput(FORWARDIN_INPUT, "");
		configInput(BACKIN_INPUT, "");
		configInput(RESETIN_INPUT, "");
		configOutput(OUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct _16SquaredWidget : ModuleWidget {
	_16SquaredWidget(_16Squared* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/16Squared.svg")));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.177, 13.484)), module, _16Squared::STEPS_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.726, 13.484)), module, _16Squared::CHANNELS_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(16.677, 36.291)), module, _16Squared::FORWARD_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.615, 36.291)), module, _16Squared::BACK_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(42.552, 36.291)), module, _16Squared::RESET_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.515, 72.387)), module, _16Squared::_1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.452, 72.387)), module, _16Squared::_2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.39, 72.387)), module, _16Squared::_3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.327, 72.387)), module, _16Squared::_4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.515, 85.325)), module, _16Squared::_5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.452, 85.325)), module, _16Squared::_6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.39, 85.325)), module, _16Squared::_7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.327, 85.325)), module, _16Squared::_8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.515, 98.262)), module, _16Squared::_9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.452, 98.262)), module, _16Squared::_10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.39, 98.262)), module, _16Squared::_11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.327, 98.262)), module, _16Squared::_12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.515, 111.2)), module, _16Squared::_13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(23.452, 111.2)), module, _16Squared::_14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.39, 111.2)), module, _16Squared::_15_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(49.327, 111.2)), module, _16Squared::_16_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(16.677, 27.323)), module, _16Squared::FORWARDIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(29.615, 27.323)), module, _16Squared::BACKIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(42.552, 27.323)), module, _16Squared::RESETIN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(29.854, 122.597)), module, _16Squared::OUT_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(19.673, 44.157)), module, _16Squared::L1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(26.429, 44.157)), module, _16Squared::L2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(33.184, 44.157)), module, _16Squared::L3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(39.94, 44.157)), module, _16Squared::L4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(19.673, 50.913)), module, _16Squared::L5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(26.429, 50.913)), module, _16Squared::L6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(33.184, 50.913)), module, _16Squared::L7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(39.94, 50.913)), module, _16Squared::L8_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(19.673, 57.668)), module, _16Squared::L9_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(26.429, 57.668)), module, _16Squared::L10_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(33.184, 57.668)), module, _16Squared::L11_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(39.94, 57.668)), module, _16Squared::L12_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(19.673, 64.423)), module, _16Squared::L13_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(26.429, 64.423)), module, _16Squared::L14_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(33.184, 64.423)), module, _16Squared::L15_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(39.94, 64.423)), module, _16Squared::L16_LIGHT));
	}
};


Model* model_16Squared = createModel<_16Squared, _16SquaredWidget>("16Squared");