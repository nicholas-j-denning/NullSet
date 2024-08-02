#include "plugin.hpp"
#include <array>


struct Cell : Module {
	enum ParamId {
		_0_PARAM,
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
		_17_PARAM,
		_18_PARAM,
		_19_PARAM,
		_20_PARAM,
		_21_PARAM,
		_22_PARAM,
		_23_PARAM,
		_24_PARAM,
		_25_PARAM,
		_26_PARAM,
		_27_PARAM,
		_28_PARAM,
		_29_PARAM,
		_30_PARAM,
		_31_PARAM,
		_32_PARAM,
		_33_PARAM,
		_34_PARAM,
		_35_PARAM,
		_36_PARAM,
		_37_PARAM,
		_38_PARAM,
		_39_PARAM,
		_40_PARAM,
		_41_PARAM,
		_42_PARAM,
		_43_PARAM,
		_44_PARAM,
		_45_PARAM,
		_46_PARAM,
		_47_PARAM,
		_48_PARAM,
		_49_PARAM,
		_50_PARAM,
		_51_PARAM,
		_52_PARAM,
		_53_PARAM,
		_54_PARAM,
		_55_PARAM,
		_56_PARAM,
		_57_PARAM,
		_58_PARAM,
		_59_PARAM,
		_60_PARAM,
		PTRANSPOSE_PARAM,
		PRESET_PARAM,
		PREVERSE_PARAM,
		PINVERSE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
		ITRANSPOSE_INPUT,
		IRESET_INPUT,
		IREVERSE_INPUT,
		IINVERSE_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		_0_LIGHT,
		_1_LIGHT,
		_2_LIGHT,
		_3_LIGHT,
		_4_LIGHT,
		_5_LIGHT,
		_6_LIGHT,
		_7_LIGHT,
		_8_LIGHT,
		_9_LIGHT,
		_10_LIGHT,
		_11_LIGHT,
		_12_LIGHT,
		_13_LIGHT,
		_14_LIGHT,
		_15_LIGHT,
		_16_LIGHT,
		_17_LIGHT,
		_18_LIGHT,
		_19_LIGHT,
		_20_LIGHT,
		_21_LIGHT,
		_22_LIGHT,
		_23_LIGHT,
		_24_LIGHT,
		_25_LIGHT,
		_26_LIGHT,
		_27_LIGHT,
		_28_LIGHT,
		_29_LIGHT,
		_30_LIGHT,
		_31_LIGHT,
		_32_LIGHT,
		_33_LIGHT,
		_34_LIGHT,
		_35_LIGHT,
		_36_LIGHT,
		_37_LIGHT,
		_38_LIGHT,
		_39_LIGHT,
		_40_LIGHT,
		_41_LIGHT,
		_42_LIGHT,
		_43_LIGHT,
		_44_LIGHT,
		_45_LIGHT,
		_46_LIGHT,
		_47_LIGHT,
		_48_LIGHT,
		_49_LIGHT,
		_50_LIGHT,
		_51_LIGHT,
		_52_LIGHT,
		_53_LIGHT,
		_54_LIGHT,
		_55_LIGHT,
		_56_LIGHT,
		_57_LIGHT,
		_58_LIGHT,
		_59_LIGHT,
		LIGHTS_LEN
	};

	Cell() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(PTRANSPOSE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(PRESET_PARAM, 0.f, 1.f, 0.f, "");
		configParam(PREVERSE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(PINVERSE_PARAM, 0.f, 1.f, 0.f, "");
		configInput(CLOCK_INPUT, "");
		configInput(ITRANSPOSE_INPUT, "");
		configInput(IRESET_INPUT, "");
		configInput(IREVERSE_INPUT, "");
		configInput(IINVERSE_INPUT, "");
		configOutput(OUT_OUTPUT, "");
		
		for (int i = 0; i < 60; i++){
			configSwitch(i, 0.f, 1.f, 0.f);
		}
	}

	int step = -1;
	std::array<int,4> note = {-1,-1,-1,-1};
	std::array<std::array<dsp::BooleanTrigger,15>,4> noteTrigger;

	void process(const ProcessArgs& args) override {
		
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 15; j++){
				
			}
		}

	}
};


struct CellWidget : ModuleWidget {
	CellWidget(Cell* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Cell.svg")));

		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 15; j++){
				addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(
					mm2px(Vec(18+8*i, 10+8*j)), module, i*15+j, i*15+j
					));
			}
		}

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(52.761, 19.099)), module, Cell::PTRANSPOSE_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(7.466, 37.374)), module, Cell::PRESET_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(52.761, 48.967)), module, Cell::PREVERSE_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(52.761, 78.835)), module, Cell::PINVERSE_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.644, 18.062)), module, Cell::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(52.819, 29.555)), module, Cell::ITRANSPOSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.525, 47.83)), module, Cell::IRESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(52.819, 59.423)), module, Cell::IREVERSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(52.819, 89.291)), module, Cell::IINVERSE_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(52.913, 116.394)), module, Cell::OUT_OUTPUT));
	}
};


Model* modelCell = createModel<Cell, CellWidget>("Cell");