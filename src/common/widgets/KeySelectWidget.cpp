#include "Widgets.hpp"

namespace nullset {

KeySelectWidget::KeySelectWidget(Vec pos, Module* module, unsigned int paramIndex)
    : _module(module), _paramIndex(paramIndex) {

    // position
    box.pos = pos;        

    // background
    SvgWidget* bg = new SvgWidget();
    bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/keySelect.svg")));
    addChild(bg);

    // knob
    Vec knobPos = mm2px(Vec(5.8,10));
    ParamWidget* knob = createParamCentered<RoundBlackKnob>(knobPos, module, paramIndex);
    addChild(knob);
    
    // key display
    keySvgs[0] = Svg::load(asset::plugin(pluginInstance, "res/keys/C.svg"));
    keySvgs[1] = Svg::load(asset::plugin(pluginInstance, "res/keys/C_SHARP.svg"));
    keySvgs[2] = Svg::load(asset::plugin(pluginInstance, "res/keys/D.svg"));
    keySvgs[3] = Svg::load(asset::plugin(pluginInstance, "res/keys/D_SHARP.svg"));
    keySvgs[4] = Svg::load(asset::plugin(pluginInstance, "res/keys/E.svg"));
    keySvgs[5] = Svg::load(asset::plugin(pluginInstance, "res/keys/F.svg"));
    keySvgs[6] = Svg::load(asset::plugin(pluginInstance, "res/keys/F_SHARP.svg"));
    keySvgs[7] = Svg::load(asset::plugin(pluginInstance, "res/keys/G.svg"));
    keySvgs[8] = Svg::load(asset::plugin(pluginInstance, "res/keys/G_SHARP.svg"));
    keySvgs[9] = Svg::load(asset::plugin(pluginInstance, "res/keys/A.svg"));
    keySvgs[10] = Svg::load(asset::plugin(pluginInstance, "res/keys/A_SHARP.svg"));
    keySvgs[11] = Svg::load(asset::plugin(pluginInstance, "res/keys/B.svg"));
    keyDisplay = new SvgWidget();
    keyDisplay->setSvg(keySvgs[0]);
    keyDisplay->box.pos = mm2px(Vec(0,16));
    addChild(keyDisplay);
}

void KeySelectWidget::draw(const DrawArgs &args){
    if(_module)
        keyDisplay->setSvg(keySvgs[_module->params[_paramIndex].getValue()]);
    Widget::draw(args);
}
    
}