#include "../Palette.hpp"
#include <algorithm>

namespace nullset::palette {

struct PaletteQuantizer : PaletteCompatibleModule {

	enum InputId {
		IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		ROOT_OUTPUT,
		OUT_OUTPUT,
		OUTPUTS_LEN
	};

	PaletteQuantizer() {
		config(0, INPUTS_LEN, OUTPUTS_LEN, 0);
		configInput(IN_INPUT, "");
		configOutput(ROOT_OUTPUT, "");
		configOutput(OUT_OUTPUT, "");
		outputs[ROOT_OUTPUT].setChannels(1);
	}

	void process(const ProcessArgs& args) override {
		setStateFromExpanders();
		int channels = std::max(1,inputs[IN_INPUT].getChannels());
		outputs[OUT_OUTPUT].setChannels(channels);
		float* voltages = inputs[IN_INPUT].getVoltages();
		for(int i = 0; i<channels; i++){
			float voltage = voltages[i];
			outputs[OUT_OUTPUT].setVoltage(quantize(voltage),i);	
		}
		outputs[ROOT_OUTPUT].setVoltage(root);
	}
	
	float quantize(float input) {
			assert(pitchVector);
			// scale voltage from zero to size of pitch vector
			// if (input>9) input = 9;
			// input = (input + 10.0f) * pitchVector->size() / 20.0f; 
			// return pitchVector->at(std::floor(input));
			float oct = std::floor(input);
			float pitch = input - oct;
			int n = pitchVector->size();
			float outOct = oct;
			if(pitch < oct + root){
				outOct = std::min(oct -1, -10.0f);
				pitch += 1;
			}
			for(int i = 1; i<n; i++){
				if(pitch <= oct + ((float) i / (float) n)){
					return (*pitchVector)[i-1] + outOct;
				}	
			}
			return(outOct+(*pitchVector)[n-1]);
	}
};


struct PaletteQuantizerWidget : ModuleWidget {
	PaletteQuantizerWidget(PaletteQuantizer* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/PaletteQuantizer.svg")));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.24, 22.618)), module, PaletteQuantizer::IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.215, 97.104)), module, PaletteQuantizer::ROOT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.215, 118.131)), module, PaletteQuantizer::OUT_OUTPUT));
	}
};

}

Model* modelPaletteQuantizer = createModel<nullset::palette::PaletteQuantizer, nullset::palette::PaletteQuantizerWidget>("PaletteQuantizer");