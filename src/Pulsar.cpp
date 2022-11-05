#include "plugin.hpp"
#include <array>


struct Pulsar : Module {
	enum ParamId {
		PVOCT_PARAM,
		PWIDTH_PARAM,
		PTAPER_PARAM,
		LFO_PARAM,
		BI_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IVOCT_INPUT,
		IWIDTH_INPUT,
		ITAPER_INPUT,
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
		configParam(PVOCT_PARAM, -10.f, 10.f, 0.f, "V/Oct");
		configParam(PWIDTH_PARAM, 0.f, 1.f, 0.5f, "Width");
		configParam(PTAPER_PARAM, 0.f, 1.f, 0.5f, "Taper");
		configSwitch(LFO_PARAM, 0.f, 1.f, 0.f, "VCO/LFO", {"VCO","LFO"});
		configSwitch(BI_PARAM, 0.f, 1.f, 0.f, "Uni/Bi",{"Unipolar", "Bipolar"});
		configInput(IWIDTH_INPUT, "Width");
		configInput(ITAPER_INPUT, "Taper");
		configOutput(OUT_OUTPUT, "Out");
	}

	std::array<float,16> phase = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	std::array<float,16> freq;

	void process(const ProcessArgs& args) override {

		bool bipolar = params[BI_PARAM].getValue() > 0.f;
		bool LFO = params[LFO_PARAM].getValue() > 0.f;
		float* in = inputs[IVOCT_INPUT].getVoltages();
		float* aIn = inputs[ITAPER_INPUT].getVoltages();
		float* widthIn = inputs[IWIDTH_INPUT].getVoltages();
		int poly = inputs[IVOCT_INPUT].getChannels();
		float a = params[PTAPER_PARAM].getValue();	
		float width = params[PWIDTH_PARAM].getValue();
		float voct = params[PVOCT_PARAM].getValue();

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
        float chanVoct = math::clamp(in[i]+voct-5.f,-10.f,10.f);
				freq[i]	 = std::pow(2,chanVoct)*dsp::FREQ_C4;
			}
		}
		else {
			lights[LFO_LIGHT].setBrightness(0);
			for (int i = 0; i<poly; i++){
        float chanVoct = math::clamp(in[i]+voct,-10.f,10.f);
				freq[i]	 = std::pow(2,chanVoct)*dsp::FREQ_C4;
			}
		}

		outputs[OUT_OUTPUT].setChannels(poly);

		// Accumulate phases and write output
		for(int i=0; i<poly; i++){

			phase[i] += freq[i] * args.sampleTime;
			if (phase[i] >= 1.f)
				phase[i] -= 1.f;

      float chanA = math::clamp((aIn[i]/10.f)+a,0.f,1.f);
      float chanWidth = math::clamp((widthIn[i]/10.f)+width,0.f,1.f);

			outputs[OUT_OUTPUT].setVoltage(tukeyWindow(phase[i],chanA,chanWidth)+offset,i);
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

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(20.368, 18.41)), module, Pulsar::PVOCT_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(12.049, 50.611)), module, Pulsar::PWIDTH_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(28.941, 50.611)), module, Pulsar::PTAPER_PARAM));

		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(12.168, 82.594)), module, Pulsar::LFO_PARAM, Pulsar::LFO_LIGHT));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(29.059, 82.594)), module, Pulsar::BI_PARAM, Pulsar::BI_LIGHT));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.368, 29.023)), module, Pulsar::IVOCT_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(12.049, 61.225)), module, Pulsar::IWIDTH_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(28.941, 61.225)), module, Pulsar::ITAPER_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.461, 118.168)), module, Pulsar::OUT_OUTPUT));
	}
};


Model* modelPulsar = createModel<Pulsar, PulsarWidget>("Pulsar");
