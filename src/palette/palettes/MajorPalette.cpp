#include "../Palette.hpp"
#include "../widgets/ModalPaletteWidget.hpp"
#include "../../common/widgets/Widgets.hpp"

using std::vector;

namespace nullset::palette::major {

enum chordId {
	ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
	ONE7, TWO7, THREE7, FOUR7, FIVE7, SIX7, SEVEN7,
	SCALE,
	CHORDS_LEN
};

vector<std::string> svgs = {
	"res/paletteChords/oneMaj.svg",
	"res/paletteChords/twoMin.svg",
	"res/paletteChords/threeMin.svg",
	"res/paletteChords/fourMaj.svg",
	"res/paletteChords/fiveMaj.svg",
	"res/paletteChords/sixMin.svg",
	"res/paletteChords/sevenDim.svg",
	"res/paletteChords/oneMaj7.svg",
	"res/paletteChords/twoMin7.svg",
	"res/paletteChords/threeMin7.svg",
	"res/paletteChords/fourMaj7.svg",
	"res/paletteChords/five7.svg",
	"res/paletteChords/sixMin7.svg",
	"res/paletteChords/sevenDimHalf7.svg",
	"res/paletteChords/majorScale.svg",
};

vector<float> scale = { 
	0.0f/12.0f, 
	//1.0f/12.0f, 
	2.0f/12.0f,
	//3.0f/12.0f,
	4.0f/12.0f,
	5.0f/12.0f,
	//6.0f/12.0f,
	7.0f/12.0f,
	//8.0f/12.0f,
	9.0f/12.0f,
	//10.0f/12.0f,
	11.0f/12.0f,
	};

vector<NVGcolor> colors = {
	nvgRGB(0x56, 0xfe, 0x00f), // green
	nvgRGB(0xfe, 0x00, 0x00f), // red
	nvgRGB(0x00, 0xf8, 0xfe), // sky blue
	nvgRGB(0xfe, 0x96, 0x00f), // orange
	nvgRGB(0x07, 0x0f, 0xfe), // indigo
	nvgRGB(0xfe, 0xd8, 0x00f), // yellow
	nvgRGB(0xc0, 0x0f, 0xef), // purple
};

vector<int> innerChord = {1, 3, 5};
vector<int> outerChord = {1, 3, 5, 7};
vector<int> centerChord = {1, 2, 3, 4, 5, 6, 7};

struct MajorPalette : Palette {

	MajorPalette() {
		keyParamIndex = CHORDS_LEN;
		config(CHORDS_LEN+1, CHORDS_LEN, 0, CHORDS_LEN);
		for (int i = 0; i < CHORDS_LEN; i++) {
			configInput(i);
			configLight(i);
			configButton(i);
		}
		configParam(keyParamIndex, 0.f, 11.f, 0.f, "Key");
		paramQuantities[keyParamIndex]->snapEnabled = true;

		triggers = vector<dsp::SchmittTrigger>(CHORDS_LEN);

		pitchVectors = vector<vector<vector<float>>>(12);
		roots = vector<vector<float>>(12);

		for (int i = 0; i<12; i++) {
			pitchVectors[i] = vector<vector<float>>(CHORDS_LEN);
			roots[i] = vector<float>(CHORDS_LEN);
			
			std::for_each(scale.begin(), scale.end(), [i](float& val) { 
				if(i != 0){
					val +=  1.0f/12.0f;
					val = val >= 1.0f ? val-1.0f : val;
				}
			});
			
			init(i, ONE, 1, innerChord, scale);	
			init(i, TWO, 2, innerChord, scale);	
			init(i, THREE, 3, innerChord, scale);	
			init(i, FOUR, 4, innerChord, scale);	
			init(i, FIVE, 5, innerChord, scale);	
			init(i, SIX, 6, innerChord, scale);	
			init(i, SEVEN, 7, innerChord, scale);	

			init(i, ONE7, 1, outerChord, scale);	
			init(i, TWO7, 2, outerChord, scale);	
			init(i, THREE7, 3, outerChord, scale);	
			init(i, FOUR7, 4, outerChord, scale);	
			init(i, FIVE7, 5, outerChord, scale);	
			init(i, SIX7, 6, outerChord, scale);	
			init(i, SEVEN7, 7, outerChord, scale);	

			init(i, SCALE, 1, centerChord, scale);
		}

		pitchVector = &pitchVectors[0][SCALE];
	}
};


struct MajorPaletteWidget : ModuleWidget {
		
	MajorPaletteWidget(MajorPalette* module) {
		setModule(module);
 		setPanel(new PanelWidget(25));
		addChild(new ModalPaletteWidget(
			mm2px(Vec(3.5, 4.25)), 
			mm2px(Vec(120.0,120.0)),
			innerChord,
			outerChord,
			colors,
			svgs,
			module,
			{ ONE, THREE, FIVE, SEVEN, TWO, FOUR, SIX },
			{ ONE7, THREE7, FIVE7, SEVEN7, TWO7, FOUR7, SIX7 },
			SCALE
		));
		addChild(new KeySelectWidget(mm2px(Vec(8,93)), module, CHORDS_LEN));
	}
};

}

Model* modelMajorPalette = createModel<nullset::palette::major::MajorPalette, nullset::palette::major::MajorPaletteWidget>("MajorPalette");
