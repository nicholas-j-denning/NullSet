#include "Palette.hpp"

using std::vector;

namespace nullset::palette {
    
void PaletteCompatibleModule::setStateFromExpanders() {
    if(rightExpander && rightExpander->leftChanged){
        pitchVector = rightExpander->pitchVector;
        root = rightExpander->root;
        rightExpander->leftChanged = false;
        leftChanged = true;
        onStateChangeFromExpander();
    }

    if(leftExpander && leftExpander->rightChanged){
        pitchVector = leftExpander->pitchVector;
        root = leftExpander->root;
        leftExpander->rightChanged = false;
        rightChanged = true;
        onStateChangeFromExpander();
    }
}

void PaletteCompatibleModule::onExpanderChange(const ExpanderChangeEvent& event) {
    rightExpander = dynamic_cast<PaletteCompatibleModule*>(getRightExpander().module);
    leftExpander = dynamic_cast<PaletteCompatibleModule*>(getLeftExpander().module);
}

void Palette::process(const ProcessArgs& args) {
    setStateFromExpanders();

    // process key change
    int key = params[keyParamIndex].getValue();
    if (prevKey != key) {
        pitchVector = &pitchVectors[key][chord];
        root = roots[key][chord];
        rightChanged = true; 
        leftChanged = true; 
    }
    prevKey = key;

    //process trigger input
    int len = triggers.size();
    for(int i = 0; i < len; i++) {
            bool triggered = triggers[i].process(inputs[i].getVoltage(), 0.1f, 1.0f);
            bool pressed = params[i].getValue();
            if(triggered || pressed){
                pitchVector = &pitchVectors[key][i];
                root = roots[key][i];
                leftChanged = true;
                rightChanged = true;
                chord = i;
                if(prevLight)
                    prevLight->setBrightness(0.0f);
                lights[i].setBrightness(1.0f);
                prevLight = &lights[i];
            };
    }
}

// chord elements and root must be between 1 and scale.size() inclusive
void Palette::init(int keyIndex, int chordIndex, int root, vector<int> chord, vector<float> scale){
    // initialize pitVector[key][chord]
        for(int note : chord) {
            int scaleIndex = (note+root-2) % scale.size();
            pitchVectors[keyIndex][chordIndex].push_back(scale[scaleIndex]);
        }	
    std::sort(pitchVectors[keyIndex][chordIndex].begin(), pitchVectors[keyIndex][chordIndex].end());
    
    // initialize root[key][chord]
    roots[keyIndex][chordIndex] = scale[root-1];
}

void Palette::onStateChangeFromExpander() {
    if(prevLight){
        prevLight->setBrightness(0.0f);
        prevLight = nullptr;
    }
}

}