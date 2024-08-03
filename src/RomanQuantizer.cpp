#include "plugin.hpp"
#include <memory>
#include <array>
#include <vector>
#include <string>
#include <math.h>
#include <iostream>

enum Interval
{
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

std::string intervalString(int interval)
{
  switch (interval)
  {
  case I:
    return "I";
  case II_FLAT:
    return "II Flat";
  case II:
    return "II";
  case III_FLAT:
    return "III Flat";
  case III:
    return "III";
  case IV:
    return "IV";
  case IV_SHARP:
    return "IV Sharp";
  case V:
    return "V";
  case VI_FLAT:
    return "VI Flat";
  case VI:
    return "VI";
  case VII_FLAT:
    return "VII Flat";
  case VII:
    return "VII";
  }
  return "ERROR: SWITCH REACHED END";
}

std::string intervalSvg(int interval)
{
  switch (interval)
  {
  case I:
    return "I.svg";
  case II_FLAT:
    return "II_flat.svg";
  case II:
    return "II.svg";
  case III_FLAT:
    return "III_flat.svg";
  case III:
    return "III.svg";
  case IV:
    return "IV.svg";
  case IV_SHARP:
    return "IV_sharp.svg";
  case V:
    return "V.svg";
  case VI_FLAT:
    return "VI_flat.svg";
  case VI:
    return "VI.svg";
  case VII_FLAT:
    return "VII_flat.svg";
  case VII:
    return "VII.svg";
  }
  return "ERROR: SWITCH REACHED END";
}

enum Quality
{
  // Triads
  MAJ,
  MIN,
  DIM,
  AUG,
  SUS2,
  SUS4,

  // 7ths
  MAJ7,
  MIN7,
  DOM7,
  DIM7_HALF,
  DIM7_FULL,
  AUG7,
  MM7,

  QUALITY_LEN
};

std::string baseSvgFolder(int quality)
{
  switch (quality)
  {
  case MAJ:
    return "res/chords/major/";
  case MIN:
    return "res/chords/minor/";
  case DIM:
    return "res/chords/minor/";
  case AUG:
    return "res/chords/major/";
  case SUS2:
    return "res/chords/major/";
  case SUS4:
    return "res/chords/major/";
  case MAJ7:
    return "res/chords/major/";
  case MIN7:
    return "res/chords/minor/";
  case DOM7:
    return "res/chords/major/";
  case DIM7_HALF:
    return "res/chords/minor/";
  case DIM7_FULL:
    return "res/chords/minor/";
  case AUG7:
    return "res/chords/major/";
  case MM7:
    return "res/chords/major/";
  }
  return "ERROR: SWITCH REACHED END";
}

std::string extensionSvg(int quality)
{
  switch (quality)
  {
  case MAJ:
    return "res/chords/extension/blank.svg";
  case MIN:
    return "res/chords/extension/blank.svg";
  case DIM:
    return "res/chords/extension/dim.svg";
  case AUG:
    return "res/chords/extension/aug.svg";
  case SUS2:
    return "res/chords/extension/sus2.svg";
  case SUS4:
    return "res/chords/extension/sus4.svg";
  case MAJ7:
    return "res/chords/extension/maj7.svg";
  case MIN7:
    return "res/chords/extension/7.svg";
  case DOM7:
    return "res/chords/extension/7.svg";
  case DIM7_HALF:
    return "res/chords/extension/half_dim7.svg";
  case DIM7_FULL:
    return "res/chords/extension/full_dim7.svg";
  case AUG7:
    return "res/chords/extension/aug7.svg";
  case MM7:
    return "res/chords/extension/min7.svg";
  }
  return "ERROR: SWITCH REACHED END";
}

std::string qualityString(int quality)
{
  switch (quality)
  {
  case MAJ:
    return "Major";
  case MIN:
    return "Minor";
  case DIM:
    return "Diminished";
  case AUG:
    return "Augmented";
  case SUS2:
    return "Suspended 2nd";
  case SUS4:
    return "Suspended 4th";
  case MAJ7:
    return "Major 7th";
  case MIN7:
    return "Minor 7th";
  case DOM7:
    return "Dominant 7th";
  case DIM7_HALF:
    return "Half Diminished 7th";
  case DIM7_FULL:
    return "Fully Diminished 7th";
  case AUG7:
    return "Augmented 7th";
  case MM7:
    return "Minor Major 7th";
  }
  return "ERROR: SWITCH REACHED END";
}

enum Key
{
  C,
  C_SHARP,
  D,
  D_SHARP,
  E,
  F,
  F_SHARP,
  G,
  G_SHARP,
  A,
  A_SHARP,
  B
};

std::string keySvg(int key){
  switch(key){
  case C:
    return "C.svg";
  case C_SHARP:
    return "C_SHARP.svg";
  case D:
    return "D.svg";
  case D_SHARP:
    return "D_SHARP.svg";
  case E:
    return "E.svg";
  case F:
    return "F.svg";
  case F_SHARP:
    return "F_SHARP.svg";
  case G:
    return "G.svg";
  case G_SHARP:
    return "G_SHARP.svg";
  case A:
    return "A.svg";
  case A_SHARP:
    return "A_SHARP.svg";
  case B:
    return "B.svg";
  }
  return "ERROR: SWITCH REACHED END";
}

class Chord
{
  Quality quality;
  Interval interval;
  std::vector<int> pitches;
  void makePitches();

public:
  Chord(Quality quality, Interval interval) : quality{quality}, interval{interval} { makePitches(); };
  Chord() : quality{MAJ}, interval{I} { makePitches(); };
  void setChord(Quality quality, Interval interval)
  {
    this->quality = quality;
    this->interval = interval;
    makePitches();
  }
  float quantize(float input);
  Quality getQuality() { return quality; }
  Interval getInterval() { return interval; }
};

void Chord::makePitches()
{
  switch (quality)
  {
  case MAJ:
    pitches = {0, 4, 7};
    break;
  case MIN:
    pitches = {0, 3, 7};
    break;
  case DIM:
    pitches = {0, 3, 6};
    break;
  case AUG:
    pitches = {0, 4, 8};
    break;
  case SUS2:
    pitches = {0, 2, 7};
    break;
  case SUS4:
    pitches = {0, 5, 7};
    break;
  case MAJ7:
    pitches = {0, 4, 7, 11};
    break;
  case MIN7:
    pitches = {0, 3, 7, 10};
    break;
  case DOM7:
    pitches = {0, 4, 7, 10};
    break;
  case DIM7_HALF:
    pitches = {0, 3, 6, 10};
    break;
  case DIM7_FULL:
    pitches = {0, 3, 6, 9};
    break;
  case AUG7:
    pitches = {0, 4, 8, 11};
    break;
  case MM7:
    pitches = {0, 3, 7, 11};
    break;
  case QUALITY_LEN:
    pitches = {};
  }
}

float Chord::quantize(float input)
{
  input -= (1.f / 12.f) * interval;
  float oct = std::floor(input);
  float pitch = input - oct;
  float len = pitches.size();
  for (int i = 1; i <= len; i++)
  {
    if (pitch <= ((float)i / len))
      return (1.f / 12.f) * (pitches.at(i - 1) + (float)interval) + oct;
  }
  // should not happen
  return -10;
}

struct RomanQuantizer : Module
{
  enum ParamId
  {
    PSTEP_PARAM,
    STEPS_PARAM,
    PRESET_PARAM,
    KEY_PARAM,
    PPATTERN_PARAM,
    PARAMS_LEN
  };
  enum InputId
  {
    IN_INPUT,
    ISTEP_INPUT,
    IRESET_INPUT,
    TRANSPOSE_INPUT,
    IPATTERN_INPUT,
    INPUTS_LEN
  };
  enum OutputId
  {
    ROOT_OUTPUT,
    OUT_OUTPUT,
    OUTPUTS_LEN
  };
  enum LightId
  {
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

  RomanQuantizer()
  {
    config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
    configParam(PSTEP_PARAM, 0.f, 10.f, 0.f, "Step");
    configParam(STEPS_PARAM, 1.f, 16.f, 16.f, "Steps");
    configParam(PRESET_PARAM, 0.f, 10.f, 0.f, "Reset");
    configParam(KEY_PARAM, 1.f, 12.f, 1.f, "Key");
    configParam(PPATTERN_PARAM, 1.f, 10.f, 1.f, "Pattern");
    configInput(IN_INPUT, "In");
    configInput(ISTEP_INPUT, "Step");
    configInput(IRESET_INPUT, "Reset");
    configInput(TRANSPOSE_INPUT, "Transpose");
    configInput(IPATTERN_INPUT, "Pattern");
    configOutput(ROOT_OUTPUT, "Root Note");
    configOutput(OUT_OUTPUT, "Out");

    // Quantize to integer values
    paramQuantities[STEPS_PARAM]->snapEnabled = true;
    paramQuantities[KEY_PARAM]->snapEnabled = true;
    paramQuantities[PPATTERN_PARAM]->snapEnabled = true;
    
    lightOn(0);
    chords.at(0).at(0) = Chord(MAJ, I);
    chords.at(0).at(1) = Chord(MAJ, IV);
    chords.at(0).at(2) = Chord(MAJ, V);
    chords.at(0).at(3) = Chord(MAJ, I);
    chords.at(1).at(3) = Chord(MAJ, VII);
  }

  int step = 0;
  int pattern = 1;
  int totalSteps = 16;
  int key = 1;
  std::array<std::array<Chord, 16>, 10> chords;
  dsp::SchmittTrigger forwardTrigger;
  dsp::SchmittTrigger resetTrigger;
  dsp::SchmittTrigger forwardButtonTrigger;
  dsp::SchmittTrigger resetButtonTrigger;

  void process(const ProcessArgs &args) override
  {

    totalSteps = params[STEPS_PARAM].getValue();
    key = params[KEY_PARAM].getValue() - 1;
    float transpose = inputs[TRANSPOSE_INPUT].getVoltage();
    pattern = params[PPATTERN_PARAM].getValue();
    int channels = inputs[IN_INPUT].getChannels();
    outputs[OUT_OUTPUT].setChannels(channels);

    // Get trigger inputs
    bool forward = forwardTrigger.process(rescale(inputs[ISTEP_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
    bool forwardButton = forwardButtonTrigger.process(rescale(params[PSTEP_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));
    bool reset = resetTrigger.process(rescale(inputs[IRESET_INPUT].getVoltage(), 0.1f, 2.f, 0.f, 1.f));
    bool resetButton = resetButtonTrigger.process(rescale(params[PRESET_PARAM].getValue(), 0.1f, 2.f, 0.f, 1.f));

    // Update step
    if (step >= totalSteps)
    {
      lightOff(step);
      step--;
      lightOn(step);
    }
    if (resetButton)
    {
      lightOff(step);
      step = 0;
      lightOn(step);
    }
    if (forwardButton)
    {
      lightOff(step);
      step++;
      if (step >= totalSteps)
        step = 0;
      lightOn(step);
    }
    if (reset)
    {
      lightOff(step);
      step = 0;
      lightOn(step);
    }
    if (forward)
    {
      lightOff(step);
      step++;
      if (step >= totalSteps)
        step = 0;
      lightOn(step);
    }
    for (int i = 0; i < channels; i++)
    {
      float in = inputs[IN_INPUT].getVoltage(i);
      float out = math::clamp(chords.at(pattern - 1).at(step).quantize(in) + (1.f / 12.f) * key + transpose, -10.f, 10.f);
      outputs[OUT_OUTPUT].setVoltage(out, i);
    }
    float out = clamp((1.f / 12.f) * (chords.at(pattern - 1).at(step).getInterval() + key) + transpose, -10.f, 10.f);
    outputs[ROOT_OUTPUT].setVoltage(out);
  }

  void lightOff(int light)
  {
    switch (light + 1)
    {
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

  void lightOn(int light)
  {
    switch (light + 1)
    {
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

  json_t *dataToJson() override
  {

    json_t *rootJ = json_object();

    json_object_set_new(rootJ, "step", json_integer(step));

    json_t *intervalJ = json_array();
    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 16; j++)
      {
        json_array_insert_new(intervalJ, j + (i * 16), json_integer(chords.at(i).at(j).getInterval()));
      }
    }
    json_object_set_new(rootJ, "intervals", intervalJ);

    json_t *qualityJ = json_array();
    for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 16; j++)
      {
        json_array_insert_new(qualityJ, j + (i * 16), json_integer(chords.at(i).at(j).getQuality()));
      }
    }
    json_object_set_new(rootJ, "qualities", qualityJ);

    return rootJ;
  }

  void dataFromJson(json_t *rootJ) override
  {

    // get step from json
    json_t *stepJ = json_object_get(rootJ, "step");
    if (stepJ)
      step = json_integer_value(stepJ);

    lightOff(0);
    lightOn(step);

    // get value[][] from json
    json_t *qualityJ = json_object_get(rootJ, "qualities");
    json_t *intervalJ = json_object_get(rootJ, "intervals");
    if (qualityJ && intervalJ)
      for (int i = 0; i < 10; i++)
      {
        for (int j = 0; j < 16; j++)
        {
          json_t *intervalArrayJ = json_array_get(intervalJ, j + (i * 16));
          json_t *qualityArrayJ = json_array_get(qualityJ, j + (i * 16));
          Interval interval = I;
          Quality quality = MAJ;
          if (intervalArrayJ && qualityArrayJ)
          {
            interval = (Interval)json_number_value(intervalArrayJ);
            quality = (Quality)json_number_value(qualityArrayJ);
            chords.at(i).at(j).setChord(quality, interval);
          }
        }
      }
  }
};

struct ChordWidget : SvgWidget
{
  RomanQuantizer *module;
  int step;
  std::array<std::array<std::shared_ptr<window::Svg>, QUALITY_LEN>, INTERVAL_LEN> svg; // svg[I][MAJOR]
  std::shared_ptr<window::Svg> blank;
  void draw(const DrawArgs &args) override
  {
    if (module)
    {
      if (module->totalSteps > step)
      {
        int pattern = module->pattern - 1;
        setSvg(svg.at(module->chords.at(pattern).at(step).getInterval()).at(module->chords.at(pattern).at(step).getQuality()));
      }
      else
        setSvg(blank);
    }
    SvgWidget::draw(args);
  }
};

struct KeyWidget : SvgWidget
{
  RomanQuantizer *module;
  std::array<std::shared_ptr<window::Svg>, 12> svg;
  void draw(const DrawArgs &args) override
  {
    if (module)
    {
      setSvg(svg[module->key]);
    }
    SvgWidget::draw(args);
  }
};


struct RomanQuantizerWidget : ModuleWidget
{
  RomanQuantizerWidget(RomanQuantizer *module)
  {
    setModule(module);
    setPanel(createPanel(asset::plugin(pluginInstance, "res/RomanQuantizer.svg")));

    // load key svgs
    std::array<std::shared_ptr<window::Svg>, 12> keySvgs;
    for (int i = 0; i < 12; i++)
    {
      std::string filename = "res/keys/" + keySvg(i);
      keySvgs.at(i) = Svg::load(asset::plugin(pluginInstance, filename));
    }
    
    //Initialize KeyWidget
    KeyWidget *keyWidget = new KeyWidget();
    keyWidget->svg = keySvgs;
    keyWidget->box.pos = mm2px(Vec(4.2, 67.3));
    keyWidget->module = module;
    addChild(keyWidget);
    
    //load chord svgs
    std::shared_ptr<window::Svg> blankChordSvg;
    blankChordSvg = Svg::load(asset::plugin(pluginInstance, "res/chords/BLANK.svg"));
    std::array<std::array<std::shared_ptr<window::Svg>, QUALITY_LEN>, INTERVAL_LEN> chordSvgs;
    std::array<std::array<std::shared_ptr<window::Svg>, QUALITY_LEN>, INTERVAL_LEN> extensionSvgs;
    for (int i = 0; i < INTERVAL_LEN; i++)
    {
      for (int q = 0; q < QUALITY_LEN; q++)
      {
        // std::string filename = "res/chords/" + intervalString(i)+ "_MAJOR.svg";
        std::string filename = baseSvgFolder(q) + intervalSvg(i);
        chordSvgs.at(i).at(q) = Svg::load(asset::plugin(pluginInstance, filename));
        filename = extensionSvg(q);
        extensionSvgs.at(i).at(q) = Svg::load(asset::plugin(pluginInstance, filename));
      }
    }

    // initialize ChordWidgets for chordsvgs
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        ChordWidget *x = new ChordWidget();
        x->blank = blankChordSvg;
        x->svg = chordSvgs;
        x->box.pos = mm2px(Vec(37.9 + 27.5 * i, 12.3 + 27.5 * j));
        x->module = module;
        x->step = i + j * 4;
        addChild(x);
      }
    }
    // initialize for extensionsvgs
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        ChordWidget *x = new ChordWidget();
        x->blank = blankChordSvg;
        x->svg = extensionSvgs;
        x->box.pos = mm2px(Vec(37.9 + 27.5 * i, 12.3 + 27.5 * j));
        x->module = module;
        x->step = i + j * 4;
        addChild(x);
      }
    }

    addParam(createParamCentered<VCVButton>(mm2px(Vec(25.79, 17.144)), module, RomanQuantizer::PSTEP_PARAM));
    addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(10.038, 38.694)), module, RomanQuantizer::STEPS_PARAM));
    addParam(createParamCentered<VCVButton>(mm2px(Vec(25.79, 50.911)), module, RomanQuantizer::PRESET_PARAM));
    addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(10.038, 61.149)), module, RomanQuantizer::KEY_PARAM));
    addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(25.79, 84.677)), module, RomanQuantizer::PPATTERN_PARAM));

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

  void appendContextMenu(Menu *menu) override
  {
    menu->addChild(new MenuSeparator);
    RomanQuantizer *rq = dynamic_cast<RomanQuantizer *>(module);
    int pattern = rq->pattern - 1;
    for (int step = 0; step < 16; step++)
    {
      menu->addChild(createSubmenuItem("Set Step " + std::to_string(step + 1) + " Chord", "", [=](Menu *menu)
                                       {
      //   menu->addChild(createMenuItem("Interval:"));
        for (int interval=0;interval<INTERVAL_LEN;interval++){
          menu->addChild(createSubmenuItem(intervalString(interval),"",[=](Menu* menu){
            for (int quality=0;quality<QUALITY_LEN;quality++){
                menu->addChild(createMenuItem(qualityString(quality),"",[=](){
                  rq->chords.at(pattern).at(step).setChord((Quality)quality,(Interval)interval);
                }));
              }
          }));
        } }));
    }
    ModuleWidget::appendContextMenu(menu);
  }
};

Model *modelRomanQuantizer = createModel<RomanQuantizer, RomanQuantizerWidget>("RomanQuantizer");
