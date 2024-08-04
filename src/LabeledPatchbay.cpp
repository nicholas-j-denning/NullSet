#include "plugin.hpp"
#include <string>
#include <array>
#include <iostream>

struct UserLabel : LedDisplayTextField {
	static const int MAX_LENGTH = 18;
	int boxID;
	engine::Module* module;
	UserLabel();
	void draw(const DrawArgs &args) override;
	void onChange(const event::Change& e) override;
};

struct LabeledPatchbay : Module {
	std::array<std::string,8> text;
	enum ParamId {
		P1_PARAM,
		P2_PARAM,
		P3_PARAM,
		P4_PARAM,
		P5_PARAM,
		P6_PARAM,
		P7_PARAM,
		P8_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		I1_INPUT,
		I2_INPUT,
		I3_INPUT,
		I4_INPUT,
		I5_INPUT,
		I6_INPUT,
		I7_INPUT,
		I8_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		O1_OUTPUT,
		O2_OUTPUT,
		O3_OUTPUT,
		O4_OUTPUT,
		O5_OUTPUT,
		O6_OUTPUT,
		O7_OUTPUT,
		O8_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	LabeledPatchbay() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(P1_PARAM, -1.f, 1.f, 0.f, "Attenuverter 1");
		configParam(P2_PARAM, -1.f, 1.f, 0.f, "Attenuverter 2");
		configParam(P3_PARAM, -1.f, 1.f, 0.f, "Attenuverter 3");
		configParam(P4_PARAM, -1.f, 1.f, 0.f, "Attenuverter 4");
		configParam(P5_PARAM, -1.f, 1.f, 0.f, "Attenuverter 5");
		configParam(P6_PARAM, -1.f, 1.f, 0.f, "Attenuverter 6");
		configParam(P7_PARAM, -1.f, 1.f, 0.f, "Attenuverter 7");
		configParam(P8_PARAM, -1.f, 1.f, 0.f, "Attenuverter 8");
		configInput(I1_INPUT, "1");
		configInput(I2_INPUT, "2");
		configInput(I3_INPUT, "3");
		configInput(I4_INPUT, "4");
		configInput(I5_INPUT, "5");
		configInput(I6_INPUT, "6");
		configInput(I7_INPUT, "7");
		configInput(I8_INPUT, "8");
		configOutput(O1_OUTPUT, "1");
		configOutput(O2_OUTPUT, "2");
		configOutput(O3_OUTPUT, "3");
		configOutput(O4_OUTPUT, "4");
		configOutput(O5_OUTPUT, "5");
		configOutput(O6_OUTPUT, "6");
		configOutput(O7_OUTPUT, "7");
		configOutput(O8_OUTPUT, "8");
	}

	void process(const ProcessArgs& args) override {
		if(int channels = inputs[I1_INPUT].getChannels()){
				float* voltages = inputs[I1_INPUT].getVoltages();
				float attenuverter = params[P1_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O1_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O1_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O1_OUTPUT].setChannels(0);
		}
		if(int channels = inputs[I2_INPUT].getChannels()){
				float* voltages = inputs[I2_INPUT].getVoltages();
				float attenuverter = params[P2_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O2_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O2_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O2_OUTPUT].setChannels(0);
		}
		if(int channels = inputs[I3_INPUT].getChannels()){
				float* voltages = inputs[I3_INPUT].getVoltages();
				float attenuverter = params[P3_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O3_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O3_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O3_OUTPUT].setChannels(0);
		}
		if(int channels = inputs[I4_INPUT].getChannels()){
				float* voltages = inputs[I4_INPUT].getVoltages();
				float attenuverter = params[P4_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O4_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O4_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O4_OUTPUT].setChannels(0);
		}
		if(int channels = inputs[I5_INPUT].getChannels()){
				float* voltages = inputs[I5_INPUT].getVoltages();
				float attenuverter = params[P5_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O5_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O5_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O5_OUTPUT].setChannels(0);
		}
		if(int channels = inputs[I6_INPUT].getChannels()){
				float* voltages = inputs[I6_INPUT].getVoltages();
				float attenuverter = params[P6_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O6_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O6_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O6_OUTPUT].setChannels(0);
		}
		if(int channels = inputs[I7_INPUT].getChannels()){
				float* voltages = inputs[I7_INPUT].getVoltages();
				float attenuverter = params[P7_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O7_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O7_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O7_OUTPUT].setChannels(0);
		}
		if(int channels = inputs[I8_INPUT].getChannels()){
				float* voltages = inputs[I8_INPUT].getVoltages();
				float attenuverter = params[P8_PARAM].getValue();
			for(int i = 0; i<channels; i++){
				outputs[O8_OUTPUT].setVoltage(voltages[i]*attenuverter,i);
			}
			outputs[O8_OUTPUT].setChannels(channels);
		}
		else{
			outputs[O8_OUTPUT].setChannels(0);
		}
	}

	json_t* dataToJson() override {
		//make root json object
		json_t *rootJ = json_object();

		json_t *textJ = json_array();
		for (int i = 0; i<8; i++){
			json_array_insert_new(textJ,i,json_string(text[i].c_str()));
		}
		json_object_set_new(rootJ, "text", textJ);

		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override {

		json_t *textJ = json_object_get(rootJ, "text");
		if(textJ)
			for(int i = 0; i<8; i++){
				json_t *textArrayJ = json_array_get(textJ,i);
				if (textArrayJ)
					text[i] = json_string_value(textArrayJ);
			}
	}
};


struct LabeledPatchbayWidget : ModuleWidget {
	LabeledPatchbayWidget(LabeledPatchbay* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/LabeledPatchbay.svg")));

		std::array<UserLabel*,8> userLabels;

		for (int i =0; i<8; i++){
			userLabels[i] = new UserLabel;
			userLabels[i]->box.pos = mm2px(Vec(13.2,7.2+ 15.2 * i));
			userLabels[i]->boxID = i;
			if(module){
				userLabels[i]->module=module;
				userLabels[i]->text=module->text[i];
			}
		}

		userLabels[0]->prevField=userLabels[7];		
		userLabels[1]->prevField=userLabels[0];		
		userLabels[2]->prevField=userLabels[1];		
		userLabels[3]->prevField=userLabels[2];		
		userLabels[4]->prevField=userLabels[3];		
		userLabels[5]->prevField=userLabels[4];		
		userLabels[6]->prevField=userLabels[5];		
		userLabels[7]->prevField=userLabels[6];		

		userLabels[0]->nextField=userLabels[1];		
		userLabels[1]->nextField=userLabels[2];		
		userLabels[2]->nextField=userLabels[3];		
		userLabels[3]->nextField=userLabels[4];		
		userLabels[4]->nextField=userLabels[5];		
		userLabels[5]->nextField=userLabels[6];		
		userLabels[6]->nextField=userLabels[7];		
		userLabels[7]->nextField=userLabels[0];		

		for (int i =0; i<8; i++){
			addChild(userLabels[i]);
		}

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 12.213)), module, LabeledPatchbay::P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 27.377)), module, LabeledPatchbay::P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 42.542)), module, LabeledPatchbay::P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 57.706)), module, LabeledPatchbay::P4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 72.87)), module, LabeledPatchbay::P5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 88.035)), module, LabeledPatchbay::P6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 103.199)), module, LabeledPatchbay::P7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(62.182, 118.364)), module, LabeledPatchbay::P8_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 12.178)), module, LabeledPatchbay::I1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 27.334)), module, LabeledPatchbay::I2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 42.489)), module, LabeledPatchbay::I3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 57.645)), module, LabeledPatchbay::I4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 72.801)), module, LabeledPatchbay::I5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 87.956)), module, LabeledPatchbay::I6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 103.112)), module, LabeledPatchbay::I7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.936, 118.267)), module, LabeledPatchbay::I8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 12.053)), module, LabeledPatchbay::O1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 27.209)), module, LabeledPatchbay::O2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 42.364)), module, LabeledPatchbay::O3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 57.52)), module, LabeledPatchbay::O4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 72.675)), module, LabeledPatchbay::O5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 87.831)), module, LabeledPatchbay::O6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 102.986)), module, LabeledPatchbay::O7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.041, 118.142)), module, LabeledPatchbay::O8_OUTPUT));
	}
};

UserLabel::UserLabel(){
	bgColor = nvgRGB(0x59,0x4c,0x62);
	color = nvgRGB(0xf7,0xdf,0xff);
}

void UserLabel::draw(const DrawArgs &args){
	nvgBeginPath(args.vg);
	nvgRect(args.vg, 5, 5, 120, 20);
	nvgFillColor(args.vg, bgColor);
	nvgFill(args.vg);
}

void UserLabel::onChange(const event::Change& e){
	LedDisplayTextField::onChange(e);
	LabeledPatchbay* labeledPatchbay = dynamic_cast<LabeledPatchbay*>(module);
	if(text.size()>MAX_LENGTH) {
		text = text.substr(0,MAX_LENGTH);
		cursor = MAX_LENGTH;
		selection = MAX_LENGTH;
	}
	labeledPatchbay->text[boxID]=text;
}

Model* modelLabeledPatchbay = createModel<LabeledPatchbay, LabeledPatchbayWidget>("LabeledPatchbay");