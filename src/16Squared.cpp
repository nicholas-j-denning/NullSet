#include "plugin.hpp"
#include <array>
#include <cmath>

struct _16Squared : Module {
	enum ParamId {
		PFORWARD_PARAM,
		PBACK_PARAM,
		PRESET_PARAM,
		STEPS_PARAM,
		POLY_PARAM,
		I1_PARAM,
		I2_PARAM,
		I3_PARAM,
		I4_PARAM,
		I5_PARAM,
		I6_PARAM,
		I7_PARAM,
		I8_PARAM,
		I9_PARAM,
		I10_PARAM,
		I11_PARAM,
		I12_PARAM,
		I13_PARAM,
		I14_PARAM,
		I15_PARAM,
		I16_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IFORWARD_INPUT,
		IBACK_INPUT,
		IRESET_INPUT,
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
		configParam(PFORWARD_PARAM, 0.f, 10.f, 0.f, "Forward");
		configParam(PBACK_PARAM, 0.f, 10.f, 0.f, "Back");
		configParam(PRESET_PARAM, 0.f, 10.f, 0.f, "Reset");
		configParam(STEPS_PARAM, 1.f, 16.f, 16.f, "Steps");
		configParam(POLY_PARAM, 1.f, 16.f, 1.f, "Poly");
		configParam(I1_PARAM, -10.f, 10.f, 0.f, "1");
		configParam(I2_PARAM, -10.f, 10.f, 0.f, "2");
		configParam(I3_PARAM, -10.f, 10.f, 0.f, "3");
		configParam(I4_PARAM, -10.f, 10.f, 0.f, "4");
		configParam(I5_PARAM, -10.f, 10.f, 0.f, "5");
		configParam(I6_PARAM, -10.f, 10.f, 0.f, "6");
		configParam(I7_PARAM, -10.f, 10.f, 0.f, "7");
		configParam(I8_PARAM, -10.f, 10.f, 0.f, "8");
		configParam(I9_PARAM, -10.f, 10.f, 0.f, "9");
		configParam(I10_PARAM, -10.f, 10.f, 0.f, "10");
		configParam(I11_PARAM, -10.f, 10.f, 0.f, "11");
		configParam(I12_PARAM, -10.f, 10.f, 0.f, "12");
		configParam(I13_PARAM, -10.f, 10.f, 0.f, "13");
		configParam(I14_PARAM, -10.f, 10.f, 0.f, "14");
		configParam(I15_PARAM, -10.f, 10.f, 0.f, "15");
		configParam(I16_PARAM, -10.f, 10.f, 0.f, "16");
		configInput(IFORWARD_INPUT, "Forward");
		configInput(IBACK_INPUT, "Back");
		configInput(IRESET_INPUT, "Reset");
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
		int channels = std::floor(params[POLY_PARAM].getValue());	
		outputs[OUT_OUTPUT].setChannels(channels);

		setValues(step);
		
		// Get trigger inputs
		bool forward = forwardTrigger.process(rescale(inputs[IFORWARD_INPUT].getVoltage() , 0.1f, 2.f, 0.f, 1.f));
		bool forwardButton = forwardButtonTrigger.process(rescale(params[PFORWARD_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));
		bool back = backTrigger.process(rescale(inputs[IBACK_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
		bool backButton = backButtonTrigger.process(rescale(params[PBACK_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));
		bool reset = resetTrigger.process(rescale(inputs[IRESET_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
		bool resetButton = resetButtonTrigger.process(rescale(params[PRESET_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));

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
		params[I1_PARAM].setValue(value[0][step-1]);
		params[I2_PARAM].setValue(value[1][step-1]);
		params[I3_PARAM].setValue(value[2][step-1]);
		params[I4_PARAM].setValue(value[3][step-1]);
		params[I5_PARAM].setValue(value[4][step-1]);
		params[I6_PARAM].setValue(value[5][step-1]);
		params[I7_PARAM].setValue(value[6][step-1]);
		params[I8_PARAM].setValue(value[7][step-1]);
		params[I9_PARAM].setValue(value[8][step-1]);
		params[I10_PARAM].setValue(value[9][step-1]);
		params[I11_PARAM].setValue(value[10][step-1]);
		params[I12_PARAM].setValue(value[11][step-1]);
		params[I13_PARAM].setValue(value[12][step-1]);
		params[I14_PARAM].setValue(value[13][step-1]);
		params[I15_PARAM].setValue(value[14][step-1]);
		params[I15_PARAM].setValue(value[14][step-1]);
		params[I16_PARAM].setValue(value[15][step-1]);
	}

	void setValues(int step){
		value[0][step-1] = params[I1_PARAM].getValue();
		value[1][step-1] = params[I2_PARAM].getValue();
		value[2][step-1] = params[I3_PARAM].getValue();
		value[3][step-1] = params[I4_PARAM].getValue();
		value[4][step-1] = params[I5_PARAM].getValue();
		value[5][step-1] = params[I6_PARAM].getValue();
		value[6][step-1] = params[I7_PARAM].getValue();
		value[7][step-1] = params[I8_PARAM].getValue();
		value[8][step-1] = params[I9_PARAM].getValue();
		value[9][step-1] = params[I10_PARAM].getValue();
		value[10][step-1] = params[I11_PARAM].getValue();
		value[11][step-1] = params[I12_PARAM].getValue();
		value[12][step-1] = params[I13_PARAM].getValue();
		value[13][step-1] = params[I14_PARAM].getValue();
		value[14][step-1] = params[I15_PARAM].getValue();
		value[15][step-1] = params[I16_PARAM].getValue();
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

		addParam(createParamCentered<VCVButton>(mm2px(Vec(12.644, 17.301)), module, _16Squared::PFORWARD_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(30.186, 17.301)), module, _16Squared::PBACK_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(47.728, 17.301)), module, _16Squared::PRESET_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.763, 46.755)), module, _16Squared::STEPS_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(30.305, 46.755)), module, _16Squared::POLY_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(13.158, 85.593)), module, _16Squared::I1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.773, 85.593)), module, _16Squared::I2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.387, 85.593)), module, _16Squared::I3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(48.002, 85.593)), module, _16Squared::I4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(13.158, 97.207)), module, _16Squared::I5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.773, 97.207)), module, _16Squared::I6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.387, 97.207)), module, _16Squared::I7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(48.002, 97.207)), module, _16Squared::I8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(13.158, 108.822)), module, _16Squared::I9_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.773, 108.822)), module, _16Squared::I10_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.387, 108.822)), module, _16Squared::I11_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(48.002, 108.822)), module, _16Squared::I12_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(13.158, 120.436)), module, _16Squared::I13_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(24.773, 120.436)), module, _16Squared::I14_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.387, 120.436)), module, _16Squared::I15_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(48.002, 120.436)), module, _16Squared::I16_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.644, 27.915)), module, _16Squared::IFORWARD_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(30.186, 27.915)), module, _16Squared::IBACK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.728, 27.915)), module, _16Squared::IRESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(47.822, 46.889)), module, _16Squared::OUT_OUTPUT));

		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(20.074, 57.61)), module, _16Squared::L1_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(26.83, 57.61)), module, _16Squared::L2_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(33.585, 57.61)), module, _16Squared::L3_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(40.341, 57.61)), module, _16Squared::L4_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(20.074, 64.366)), module, _16Squared::L5_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(26.83, 64.366)), module, _16Squared::L6_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(33.585, 64.366)), module, _16Squared::L7_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(40.341, 64.366)), module, _16Squared::L8_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(20.074, 71.121)), module, _16Squared::L9_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(26.83, 71.121)), module, _16Squared::L10_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(33.585, 71.121)), module, _16Squared::L11_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(40.341, 71.121)), module, _16Squared::L12_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(20.074, 77.876)), module, _16Squared::L13_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(26.83, 77.876)), module, _16Squared::L14_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(33.585, 77.876)), module, _16Squared::L15_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(40.341, 77.876)), module, _16Squared::L16_LIGHT));
	}
};


Model* model_16Squared = createModel<_16Squared, _16SquaredWidget>("16Squared");