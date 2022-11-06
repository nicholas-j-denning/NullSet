#include "plugin.hpp"
#include <memory>
#include <array>
#include <vector>
#include <string>
#include <math.h>
#include <iostream>


enum Interval {
  I,
  II_FLAT,
  II,
  III_FLAT,
  III,
  IV,
  IV_SHARP,
  V,
  VI_FLAT,
  VI,
  VII_FLAT,
  VII,
  INTERVAL_LEN
};

std::string intervalString(int interval){
  switch (interval) {
    case I: 
      return "I";
    case II_FLAT: 
      return "II_FLAT";
    case II: 
      return "II";
    case III_FLAT: 
      return "III_FLAT";
    case III: 
      return "III";
    case IV: 
      return "IV";
    case IV_SHARP: 
      return "IV_SHARP";
    case V: 
      return "V";
    case VI_FLAT: 
      return "VI_FLAT";
    case VI: 
      return "VI";
    case VII_FLAT: 
      return "VII_FLAT";
    case VII: 
      return "VII";
  }
  return "ERROR: SWITCH REACHED END";
}

enum Quality {
  MAJOR,
  QUALITY_LEN
};

std::string qualityString(int quality){
  switch (quality) {
    case MAJOR:
      return "MAJOR";
  }
  return "ERROR: SWITCH REACHED END";
}

class Chord {
  Quality quality;
  Interval interval;
  bool enabled;
  std::vector<int> pitches;

public:
  Chord(Quality quality, Interval interval);
  float quantize(float input);
  bool isEnabled(){return enabled;};
  void enable(){enabled=true;};
  void disable(){enabled=false;};
  Quality getQuality(){return quality;}
  Interval getInterval(){return interval;}
};

Chord::Chord(Quality quality,Interval interval): quality{quality}, interval{interval}{
  switch (quality) {
    case MAJOR:
      pitches = {0,4,7};
      break;
    case QUALITY_LEN:
      pitches = {};
  }
}

float Chord::quantize(float input){
  input -= (1.f/12.f)*interval;
  float oct = std::floor(input);
  float pitch = input - oct;
  float len = pitches.size();
  for (int i = 1; i<=len;i++){
    if (pitch<=((float)i/len)) return (1.f/12.f)*(pitches.at(i-1)+(float)interval)+oct;
  }
  // should not happen
  return -10;
}

struct RomanQuantizer : Module {
	enum ParamId {
		PSTEP_PARAM,
		STEPS_PARAM,
		PRESET_PARAM,
		KEY_PARAM,
		PPATTERN_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_INPUT,
		ISTEP_INPUT,
		IRESET_INPUT,
		TRANSPOSE_INPUT,
		IPATTERN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		ROOT_OUTPUT,
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

	RomanQuantizer() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(PSTEP_PARAM, 0.f, 10.f, 0.f, "Step");
		configParam(STEPS_PARAM, 1.f, 16.99f, 16.f, "Steps");
		configParam(PRESET_PARAM, 0.f, 10.f, 0.f, "Reset");
		configParam(KEY_PARAM, 1.f, 12.99f, 1.f, "Key");
		configParam(PPATTERN_PARAM, 0.f, 9.99f, 0.f, "Pattern");
		configInput(IN_INPUT, "In");
		configInput(ISTEP_INPUT, "Step");
		configInput(IRESET_INPUT, "Reset");
		configInput(TRANSPOSE_INPUT, "Transpose");
		configInput(IPATTERN_INPUT, "Pattern");
		configOutput(ROOT_OUTPUT, "Root Note");
		configOutput(OUT_OUTPUT, "Out");
    lightOn(0);
	}

  int step = 0;
  std::array<Chord,16> chords ={
    Chord(MAJOR,I),
    Chord(MAJOR,IV),
    Chord(MAJOR,V),
    Chord(MAJOR,I),
    Chord(MAJOR,I),
    Chord(MAJOR,IV),
    Chord(MAJOR,V),
    Chord(MAJOR,I),
    Chord(MAJOR,I),
    Chord(MAJOR,IV),
    Chord(MAJOR,V),
    Chord(MAJOR,I),
    Chord(MAJOR,I),
    Chord(MAJOR,IV),
    Chord(MAJOR,V),
    Chord(MAJOR,I)
  };
	dsp::SchmittTrigger forwardTrigger;
	dsp::SchmittTrigger resetTrigger;
	dsp::SchmittTrigger forwardButtonTrigger;
	dsp::SchmittTrigger resetButtonTrigger;


	void process(const ProcessArgs& args) override {

		int totalSteps = std::floor(params[STEPS_PARAM].getValue());	
		int channels = inputs[IN_INPUT].getChannels();
		outputs[OUT_OUTPUT].setChannels(channels);

    for (int i = 0; i<16;i++){
      if (i<totalSteps) chords[i].enable();
      else chords[i].disable();
    }

		// Get trigger inputs
		bool forward = forwardTrigger.process(rescale(inputs[ISTEP_INPUT].getVoltage() , 0.1f, 2.f, 0.f, 1.f));
		bool forwardButton = forwardButtonTrigger.process(rescale(params[PSTEP_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));
		bool reset = resetTrigger.process(rescale(inputs[IRESET_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
		bool resetButton = resetButtonTrigger.process(rescale(params[PRESET_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));

		// Update step
		if(resetButton){
			lightOff(step);
			step=0;
			lightOn(step);
		}
		if(forwardButton){
			lightOff(step);
			step++;
			if (step >= totalSteps) step = 0;
			lightOn(step);
		}
		if(reset){
			lightOff(step);
			step=0;
			lightOn(step);
		}
		if(forward){
			lightOff(step);
			step++;
			if (step >= totalSteps) step = 0;
			lightOn(step);
		}
    for (int i= 0;i<channels;i++){
      float in = inputs[IN_INPUT].getVoltage(i);
      float out = chords[step].quantize(in);
      outputs[OUT_OUTPUT].setVoltage(out);
    }
		
	}

	void lightOff(int light){
		switch(light+1){
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
		switch(light+1){
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
};

struct ChordWidget : SvgWidget {
  RomanQuantizer* module;
  int index;
  std::array<std::array<std::shared_ptr<window::Svg>,QUALITY_LEN>,INTERVAL_LEN> svg; // svg[I][MAJOR]
  std::shared_ptr<window::Svg> blank;
  void draw(const DrawArgs &args) override{
    if(module){
      if (module->chords[index].isEnabled())
        setSvg(svg.at(module->chords[index].getInterval()).at(module->chords[index].getQuality()));
      else 
        setSvg(blank);
    }

    SvgWidget::draw(args);
  }
};

struct RomanQuantizerWidget : ModuleWidget {
	RomanQuantizerWidget(RomanQuantizer* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/RomanQuantizer.svg")));

    // load svgs
    std::shared_ptr<window::Svg> blankSvg;
    blankSvg = Svg::load(asset::plugin(pluginInstance,"res/chords/BLANK.svg"));
    std::array<std::array<std::shared_ptr<window::Svg>,QUALITY_LEN>,INTERVAL_LEN> chordSvgs;
    for(int i=0;i<INTERVAL_LEN;i++){
      for(int q=0;q<QUALITY_LEN;q++){
        std::string filename = "res/chords/" + intervalString(i)+ "_" + qualityString(q) + ".svg";
        chordSvgs.at(i).at(q) = Svg::load(asset::plugin(pluginInstance, filename));
      }
    }

    // initialize ChordWidgets
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        ChordWidget* x = new ChordWidget();
        x->blank=blankSvg;
        x->svg=chordSvgs;
        x->box.pos = mm2px(Vec(37.9+27.5*i, 12.3+27.5*j));
        x->module = module;
        x->index = i+j*4;
        addChild(x);
      }
    }

		addParam(createParamCentered<VCVButton>(mm2px(Vec(25.79, 17.144)), module, RomanQuantizer::PSTEP_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.038, 38.694)), module, RomanQuantizer::STEPS_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(25.79, 50.911)), module, RomanQuantizer::PRESET_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.038, 61.149)), module, RomanQuantizer::KEY_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(25.79, 84.677)), module, RomanQuantizer::PPATTERN_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.038, 16.239)), module, RomanQuantizer::IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.79, 27.758)), module, RomanQuantizer::ISTEP_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.79, 61.524)), module, RomanQuantizer::IRESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.038, 95.047)), module, RomanQuantizer::TRANSPOSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.79, 95.291)), module, RomanQuantizer::IPATTERN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.013, 117.636)), module, RomanQuantizer::ROOT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(25.884, 117.691)), module, RomanQuantizer::OUT_OUTPUT));

		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(59.371, 33.993)), module, RomanQuantizer::L1_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(86.842, 33.993)), module, RomanQuantizer::L2_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(114.313, 33.993)), module, RomanQuantizer::L3_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(141.784, 33.993)), module, RomanQuantizer::L4_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(59.371, 61.463)), module, RomanQuantizer::L5_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(86.842, 61.463)), module, RomanQuantizer::L6_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(114.313, 61.463)), module, RomanQuantizer::L7_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(141.784, 61.463)), module, RomanQuantizer::L8_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(59.371, 88.934)), module, RomanQuantizer::L9_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(86.842, 88.934)), module, RomanQuantizer::L10_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(114.313, 88.934)), module, RomanQuantizer::L11_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(141.784, 88.934)), module, RomanQuantizer::L12_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(59.371, 116.404)), module, RomanQuantizer::L13_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(86.842, 116.404)), module, RomanQuantizer::L14_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(114.313, 116.404)), module, RomanQuantizer::L15_LIGHT));
		addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(141.784, 116.404)), module, RomanQuantizer::L16_LIGHT));
	}
};


Model* modelRomanQuantizer = createModel<RomanQuantizer, RomanQuantizerWidget>("RomanQuantizer");
