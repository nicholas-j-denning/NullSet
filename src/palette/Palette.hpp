#include "../plugin.hpp"

namespace nullset::palette {

class PaletteCompatibleModule : public Module {
protected:
    const std::vector<float>* pitchVector = &zeroVector; 
    float root = 0;
    bool leftChanged = true;
    bool rightChanged = true;
    void setStateFromExpanders();
    virtual void onStateChangeFromExpander() {};
private:
    void onExpanderChange(const ExpanderChangeEvent& event) override ;
    PaletteCompatibleModule* rightExpander = nullptr;
    PaletteCompatibleModule* leftExpander = nullptr;
    const std::vector<float> zeroVector = {0.0f};
};

class Palette : public PaletteCompatibleModule {
protected:
    // chord elements and root must be between 1 and scale.size() inclusive
    void init(int keyIndex, int chordIndex, int root, std::vector<int> chord, std::vector<float> scale);
    std::vector<std::vector<std::vector<float>>> pitchVectors; // [key][chord][note]
    std::vector<std::vector<float>> roots; // [key][chord]
    std::vector<dsp::SchmittTrigger> triggers;
    int keyParamIndex = 0;
private:
    void onStateChangeFromExpander() override;
	void process(const ProcessArgs& args) override;
    int prevKey = 0;
    int chord = 0;
    Light* prevLight = nullptr;
};

}