#include "plugin.hpp"
#include <cmath>
#include <array>


struct Pulsar : Module {
	enum ParamId {
		BI_PARAM,
		WIDTH_PARAM,
		TAPER_PARAM,
		LFO_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		VOCT_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		BI_LIGHT,
		LFO_LIGHT,
		LIGHTS_LEN
	};

	Pulsar() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configSwitch(BI_PARAM, 0.f, 1.f, 0.f, "Uni/Bi",{"Unipolar", "Bipolar"});
		configParam(WIDTH_PARAM, 0.f, 1.f, 0.f, "");
		configParam(TAPER_PARAM, 0.f, 1.f, 0.f, "");
		configSwitch(LFO_PARAM, 0.f, 1.f, 0.f, "VCO/LFO",{"VCO","LFO"});
		configInput(VOCT_INPUT, "");
		configOutput(OUT_OUTPUT, "");
	}

	std::array<float,16> phase = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::array<float,16> freq;

	void process(const ProcessArgs& args) override {

		bool bipolar = params[BI_PARAM].getValue() > 0.f;
		bool LFO = params[LFO_PARAM].getValue() > 0.f;
		float* in = inputs[VOCT_INPUT].getVoltages();
		int poly = inputs[VOCT_INPUT].getChannels();
		float a = params[TAPER_PARAM].getValue();	
		float width = params[WIDTH_PARAM].getValue();

		// set offset	
		float offset;
		if (bipolar){
			offset = -5.f;
			lights[BI_LIGHT].setBrightness(1);
		}
		else {
			offset = 0.f;
			lights[BI_LIGHT].setBrightness(0);
		}

		// single channel if no input
		if (poly==0) poly = 1; 

		//set frequencies
		if (LFO){
			lights[LFO_LIGHT].setBrightness(1);
			for (int i = 0; i<poly; i++){
				freq[i]	 = std::pow(2,in[i]-5.f)*dsp::FREQ_C4;
			}
		}
		else {
			lights[LFO_LIGHT].setBrightness(0);
			for (int i = 0; i<poly; i++){
				freq[i]	 = std::pow(2,in[i])*dsp::FREQ_C4;
			}
		}

		outputs[OUT_OUTPUT].setChannels(poly);

		// Accumulate phases and write output
		for(int i=0; i<poly; i++){

			phase[i] += freq[i] * args.sampleTime;
			if (phase[i] >= 1.f)
				phase[i] -= 1.f;

			outputs[OUT_OUTPUT].setVoltage(tukeyWindow(phase[i],a,width)+offset,i);
		}
	}

	float tukeyWindow(float phase, float a, float width){

		constexpr float tau = 6.283185307179586f;
		if (width==0){
			return 0;
		}
		if (phase<width*a/2.f){
			return 5*(1-std::cos(tau * phase / (a*width)));
		}
		if (phase<=width*(1-a/2.f)){
			return 10.f;
		}
		if (phase<width*1) {
			return 5*(1-std::cos(tau * (width - phase) / (a*width)));
		}
		return 0.f;
	}
};



struct PulsarWidget : ModuleWidget {
	PulsarWidget(Pulsar* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Pulsar.svg")));

		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(28.949, 15.023)), module, Pulsar::BI_PARAM, Pulsar::BI_LIGHT));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.538, 30.987)), module, Pulsar::WIDTH_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(25.216, 31.552)), module, Pulsar::TAPER_PARAM));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(18.379, 44.16)), module, Pulsar::LFO_PARAM, Pulsar::LFO_LIGHT));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.228, 14.992)), module, Pulsar::VOCT_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.139, 118.554)), module, Pulsar::OUT_OUTPUT));
	}
};


Model* modelPulsar = createModel<Pulsar, PulsarWidget>("Pulsar");