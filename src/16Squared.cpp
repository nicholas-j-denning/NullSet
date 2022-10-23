#include "plugin.hpp"
#include <array>
#include <cmath>

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
		configParam(STEPS_PARAM, 1.f, 16.f, 16.f, "Steps");
		configParam(CHANNELS_PARAM, 1.f, 16.f, 1.f, "Channels");
		configParam(FORWARD_PARAM, 0.f, 10.f, 0.f, "Forward");
		configParam(BACK_PARAM, 0.f, 10.f, 0.f, "Back");
		configParam(RESET_PARAM, 0.f, 10.f, 0.f, "Reset");
		configParam(_1_PARAM, -10.f, 10.f, 0.f, "1");
		configParam(_2_PARAM, -10.f, 10.f, 0.f, "2");
		configParam(_3_PARAM, -10.f, 10.f, 0.f, "3");
		configParam(_4_PARAM, -10.f, 10.f, 0.f, "4");
		configParam(_5_PARAM, -10.f, 10.f, 0.f, "5");
		configParam(_6_PARAM, -10.f, 10.f, 0.f, "6");
		configParam(_7_PARAM, -10.f, 10.f, 0.f, "7");
		configParam(_8_PARAM, -10.f, 10.f, 0.f, "8");
		configParam(_9_PARAM, -10.f, 10.f, 0.f, "9");
		configParam(_10_PARAM, -10.f, 10.f, 0.f, "10");
		configParam(_11_PARAM, -10.f, 10.f, 0.f, "11");
		configParam(_12_PARAM, -10.f, 10.f, 0.f, "12");
		configParam(_13_PARAM, -10.f, 10.f, 0.f, "13");
		configParam(_14_PARAM, -10.f, 10.f, 0.f, "14");
		configParam(_15_PARAM, -10.f, 10.f, 0.f, "15");
		configParam(_16_PARAM, -10.f, 10.f, 0.f, "16");
		configInput(FORWARDIN_INPUT, "Forward");
		configInput(BACKIN_INPUT, "Back");
		configInput(RESETIN_INPUT, "Reset");
		configOutput(OUT_OUTPUT, "Out");
		lightOn(step);
		for(int i = 0; i<16; i++)
			for(int j = 0; j<16; j++)
				value[i][j]=0;
	}

	int step = 1;
	std::array<std::array<float,16>,16> value;
	dsp::SchmittTrigger forwardTrigger;
	dsp::SchmittTrigger backTrigger;
	dsp::SchmittTrigger resetTrigger;
	dsp::SchmittTrigger forwardButtonTrigger;
	dsp::SchmittTrigger backButtonTrigger;
	dsp::SchmittTrigger resetButtonTrigger;

	void process(const ProcessArgs& args) override {

		int totalSteps = std::floor(params[STEPS_PARAM].getValue());	
		int channels = std::floor(params[CHANNELS_PARAM].getValue());	
		outputs[OUT_OUTPUT].setChannels(channels);

		setValues(step);
		
		// Get trigger inputs
		bool forward = forwardTrigger.process(rescale(inputs[FORWARDIN_INPUT].getVoltage() , 0.1f, 2.f, 0.f, 1.f));
		bool forwardButton = forwardButtonTrigger.process(rescale(params[FORWARD_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));
		bool back = backTrigger.process(rescale(inputs[BACKIN_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
		bool backButton = backButtonTrigger.process(rescale(params[BACK_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));
		bool reset = resetTrigger.process(rescale(inputs[RESETIN_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
		bool resetButton = resetButtonTrigger.process(rescale(params[RESET_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));

		// Update step
		if(resetButton){
			lightOff(step);
			step=1;
			lightOn(step);
			getValues(step);
		}
		if(forwardButton){
			lightOff(step);
			step++;
			if (step > totalSteps) step = 1;
			lightOn(step);
			getValues(step);
		}
		if(backButton){
			lightOff(step);
			step--;
			if (step < 1) step = totalSteps;
			lightOn(step);
			getValues(step);
		}
		if(reset){
			lightOff(step);
			step=1;
			lightOn(step);
			getValues(step);
		}
		if(forward){
			lightOff(step);
			step++;
			if (step > totalSteps) step = 1;
			lightOn(step);
			getValues(step);
		}
		if(back){
			lightOff(step);
			step--;
			if (step < 1) step = totalSteps;
			lightOn(step);
			getValues(step);
		}
		
		updateOutput(step,channels);
	}

	void lightOff(int light){
		switch(light){
			case 1:
				lights[L1_LIGHT].setBrightness(0.f);
				break;
			case 2:
				lights[L2_LIGHT].setBrightness(0.f);
				break;
			case 3:
				lights[L3_LIGHT].setBrightness(0.f);
				break;
			case 4:
				lights[L4_LIGHT].setBrightness(0.f);
				break;
			case 5:
				lights[L5_LIGHT].setBrightness(0.f);
				break;
			case 6:
				lights[L6_LIGHT].setBrightness(0.f);
				break;
			case 7:
				lights[L7_LIGHT].setBrightness(0.f);
				break;
			case 8:
				lights[L8_LIGHT].setBrightness(0.f);
				break;
			case 9:
				lights[L9_LIGHT].setBrightness(0.f);
				break;
			case 10:
				lights[L10_LIGHT].setBrightness(0.f);
				break;
			case 11:
				lights[L11_LIGHT].setBrightness(0.f);
				break;
			case 12:
				lights[L12_LIGHT].setBrightness(0.f);
				break;
			case 13:
				lights[L13_LIGHT].setBrightness(0.f);
				break;
			case 14:
				lights[L14_LIGHT].setBrightness(0.f);
				break;
			case 15:
				lights[L15_LIGHT].setBrightness(0.f);
				break;
			case 16:
				lights[L16_LIGHT].setBrightness(0.f);
				break;
		}
	}

	void lightOn(int light){
		switch(light){
			case 1:
				lights[L1_LIGHT].setBrightness(1.f);
				break;
			case 2:
				lights[L2_LIGHT].setBrightness(1.f);
				break;
			case 3:
				lights[L3_LIGHT].setBrightness(1.f);
				break;
			case 4:
				lights[L4_LIGHT].setBrightness(1.f);
				break;
			case 5:
				lights[L5_LIGHT].setBrightness(1.f);
				break;
			case 6:
				lights[L6_LIGHT].setBrightness(1.f);
				break;
			case 7:
				lights[L7_LIGHT].setBrightness(1.f);
				break;
			case 8:
				lights[L8_LIGHT].setBrightness(1.f);
				break;
			case 9:
				lights[L9_LIGHT].setBrightness(1.f);
				break;
			case 10:
				lights[L10_LIGHT].setBrightness(1.f);
				break;
			case 11:
				lights[L11_LIGHT].setBrightness(1.f);
				break;
			case 12:
				lights[L12_LIGHT].setBrightness(1.f);
				break;
			case 13:
				lights[L13_LIGHT].setBrightness(1.f);
				break;
			case 14:
				lights[L14_LIGHT].setBrightness(1.f);
				break;
			case 15:
				lights[L15_LIGHT].setBrightness(1.f);
				break;
			case 16:
				lights[L16_LIGHT].setBrightness(1.f);
				break;
		}
	}

	void getValues(int step){
		params[_1_PARAM].setValue(value[0][step-1]);
		params[_2_PARAM].setValue(value[1][step-1]);
		params[_3_PARAM].setValue(value[2][step-1]);
		params[_4_PARAM].setValue(value[3][step-1]);
		params[_5_PARAM].setValue(value[4][step-1]);
		params[_6_PARAM].setValue(value[5][step-1]);
		params[_7_PARAM].setValue(value[6][step-1]);
		params[_8_PARAM].setValue(value[7][step-1]);
		params[_9_PARAM].setValue(value[8][step-1]);
		params[_10_PARAM].setValue(value[9][step-1]);
		params[_11_PARAM].setValue(value[10][step-1]);
		params[_12_PARAM].setValue(value[11][step-1]);
		params[_13_PARAM].setValue(value[12][step-1]);
		params[_14_PARAM].setValue(value[13][step-1]);
		params[_15_PARAM].setValue(value[14][step-1]);
		params[_15_PARAM].setValue(value[14][step-1]);
		params[_16_PARAM].setValue(value[15][step-1]);
	}

	void setValues(int step){
		value[0][step-1] = params[_1_PARAM].getValue();
		value[1][step-1] = params[_2_PARAM].getValue();
		value[2][step-1] = params[_3_PARAM].getValue();
		value[3][step-1] = params[_4_PARAM].getValue();
		value[4][step-1] = params[_5_PARAM].getValue();
		value[5][step-1] = params[_6_PARAM].getValue();
		value[6][step-1] = params[_7_PARAM].getValue();
		value[7][step-1] = params[_8_PARAM].getValue();
		value[8][step-1] = params[_9_PARAM].getValue();
		value[9][step-1] = params[_10_PARAM].getValue();
		value[10][step-1] = params[_11_PARAM].getValue();
		value[11][step-1] = params[_12_PARAM].getValue();
		value[12][step-1] = params[_13_PARAM].getValue();
		value[13][step-1] = params[_14_PARAM].getValue();
		value[14][step-1] = params[_15_PARAM].getValue();
		value[15][step-1] = params[_16_PARAM].getValue();
	}

	void updateOutput(int step, int channels){
		for (int i=0; i < channels;i++)
			outputs[OUT_OUTPUT].setVoltage(value[i][step-1],i);
	}

	//automatically called by VCV to save state
	json_t* dataToJson() override {
		//make root json object
		json_t *rootJ = json_object();

		//add step to json
		json_object_set_new(rootJ, "step", json_integer(step));
		
		//add value to json
		json_t *valueJ = json_array();
		for(int i = 0; i<16; i++){
			for(int j = 0; j<16; j++){
				json_array_insert_new(valueJ, j+(i*16),json_real(value[i][j]));
			}
		}
		json_object_set_new(rootJ, "value", valueJ);

		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {

		// get step from json
		json_t * stepJ = json_object_get(rootJ, "step");
		if (stepJ)
			step = json_integer_value(stepJ);
		
		lightOff(1);
		lightOn(step);

		//get value[][] from json
		json_t *valueJ = json_object_get(rootJ, "value");	
		if (valueJ)
			for(int i = 0; i<16; i++){
				for(int j = 0; j<16; j++){
					json_t *valueArrayJ = json_array_get(valueJ,j+(i*16));
					if (valueArrayJ)
						value[i][j] = json_number_value(valueArrayJ);	
				}
			}	
	}
};


struct _16SquaredWidget : ModuleWidget {
	_16SquaredWidget(_16Squared* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/16Squared.svg")));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.177, 13.484)), module, _16Squared::STEPS_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.726, 13.484)), module, _16Squared::CHANNELS_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(16.677, 36.291)), module, _16Squared::FORWARD_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(29.615, 36.291)), module, _16Squared::BACK_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(42.552, 36.291)), module, _16Squared::RESET_PARAM));
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