#include "ModalPaletteWidget.hpp"

using std::vector;
using std::string;

namespace nullset::palette {

ModalPaletteWidget::ModalPaletteWidget(
        Vec pos, 
        Vec size,
        vector<int> innerChord,
        vector<int> outerChord,
        vector<NVGcolor> scaleColors,
        vector<std::string> svgs,
        Module* module,
        vector<int> _innerIndex,
        vector<int> _outerIndex,
        int _centerIndex
) 
{
    innerIndex = _innerIndex;
    outerIndex = _outerIndex;
    centerIndex = _centerIndex;
    
    colors = vector<NVGcolor>(innerIndex.size() + outerIndex.size() + 1);
    
    colors[centerIndex] = nvgRGB(255, 255, 255);

    colors[innerIndex[0]] = chordColor(1, innerChord, scaleColors);
    colors[innerIndex[1]] = chordColor(3, innerChord, scaleColors);
    colors[innerIndex[2]] = chordColor(5, innerChord, scaleColors);
    colors[innerIndex[3]] = chordColor(7, innerChord, scaleColors);
    colors[innerIndex[4]] = chordColor(2, innerChord, scaleColors);
    colors[innerIndex[5]] = chordColor(4, innerChord, scaleColors);
    colors[innerIndex[6]] = chordColor(6, innerChord, scaleColors);

    colors[outerIndex[0]] = chordColor(1, outerChord, scaleColors);
    colors[outerIndex[1]] = chordColor(3, outerChord, scaleColors);
    colors[outerIndex[2]] = chordColor(5, outerChord, scaleColors);
    colors[outerIndex[3]] = chordColor(7, outerChord, scaleColors);
    colors[outerIndex[4]] = chordColor(2, outerChord, scaleColors);
    colors[outerIndex[5]] = chordColor(4, outerChord, scaleColors);
    colors[outerIndex[6]] = chordColor(6, outerChord, scaleColors);

    setPosition(pos);
    setSize(size);

    makeInput(0, 0, centerIndex, module);
    makeButton(0, 0, centerIndex, module);
    makeLight(0, 0, centerIndex, module);
    makeLabel(0, 0, svgs[centerIndex]);
    for(int i = 0; i < 7; i++) {
        float innerAngle = (i * 2* 3.1415926 / 7.0);
        makeInput(innerAngle, 0.5, innerIndex[i], module);
        makeButton(innerAngle, 0.5, innerIndex[i], module);
        makeLight(innerAngle, 0.5, innerIndex[i], module);
        makeLabel(innerAngle, 0.5, svgs[innerIndex[i]]);
        float outerAngle = innerAngle + 3.1415926 / 7.0;
        makeInput(outerAngle, 0.8, outerIndex[i], module);
        makeButton(outerAngle, 0.8, outerIndex[i], module);
        makeLight(outerAngle, 0.8, outerIndex[i], module);
        makeLabel(outerAngle, 0.8, svgs[outerIndex[i]]);
    }
}

void ModalPaletteWidget::draw(const DrawArgs& args) {
    nvgFillColor(args.vg, nvgRGB(50, 50, 50));
    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0.0, 0.0, box.size.x, box.size.y);
    nvgFill(args.vg);
    
    drawCircle(args, radial2Vec(0,0), 28, colors[centerIndex]);

    for(int i = 0; i < 7; i++) {
        float angle = (i * 2* 3.1415926 / 7.0);
        drawCircle(args, radial2Vec(0.5, angle),28, colors[innerIndex[i]]);
    }

    for(int i = 0; i < 7; i++) {
        float angle = (i * 2* 3.1415926 / 7.0) + 3.1415926 / 7.0;
        drawCircle(args, radial2Vec(0.8, angle),28, colors[outerIndex[i]]);
    }
    Widget::draw(args);
}   

Vec ModalPaletteWidget::radial2Vec(float radius, float angle) {
    float r = box.size.x / 2; 
    assert(radius >= 0 && radius <= 1);
    angle = angle + 3.1415926 * 8.0 / 7.0;
    return Vec(r - radius * r * sin(angle), r + 7 + radius * r * cos(angle));
}

void ModalPaletteWidget::drawCircle(const DrawArgs& args, Vec center, float r, NVGcolor color) {
    nvgStrokeColor(args.vg, nvgRGB(0,0,0));
    nvgFillColor(args.vg, color);
    nvgStrokeWidth(args.vg, 4.0);
    nvgBeginPath(args.vg);
    nvgCircle(args.vg, center.x, center.y, r);
    nvgStroke(args.vg);
    nvgFill(args.vg);
}

void ModalPaletteWidget::makeInput(float angle, float r, int index, Module* module) {
    float offsetDistance = 28;
    float offsetAngle = (2 * 3.1415926) * 7 / 12;
    Vec posision = radial2Vec(r, angle);
    posision.x +=offsetDistance * cos(offsetAngle);
    posision.y +=offsetDistance * -sin(offsetAngle);
    PortWidget* input = createInputCentered<PJ301MPort>(posision, module, index);
    addChild(input);
}

void ModalPaletteWidget::makeButton(float angle, float r, int index, Module* module) {
    float offsetDistance = 28;
    float offsetAngle = (2 * 3.1415926) * 11 / 12;
    Vec posision = radial2Vec(r, angle);
    posision.x +=offsetDistance * cos(offsetAngle);
    posision.y +=offsetDistance * -sin(offsetAngle);
    ParamWidget* button = createParamCentered<VCVButton>(posision, module, index);
    addChild(button);
}

void ModalPaletteWidget::makeLight(float angle, float r, int index, Module* module) {
    float offsetDistance = 28;
    float offsetAngle = (2 * 3.1415926) * 3 / 12;
    Vec posision = radial2Vec(r, angle);
    posision.x +=offsetDistance * cos(offsetAngle);
    posision.y +=offsetDistance * -sin(offsetAngle);
    LightWidget* light = createLightCentered<LargeLight<WhiteLight>>(posision, module, index);
    addChild(light);
}

void ModalPaletteWidget::makeLabel(float angle, float r, std::string svg) {
    float offsetDistance = 39.6;
    float offsetAngle = (2 * 3.1415926) * 3 / 8;
    Vec posision = radial2Vec(r, angle);
    posision.x +=offsetDistance * cos(offsetAngle);
    posision.y +=offsetDistance * -sin(offsetAngle);
    SvgWidget* svgWiget = new SvgWidget();
    svgWiget->box.pos = posision;
    svgWiget->setSvg(Svg::load(asset::plugin(pluginInstance, svg)));
    addChild(svgWiget);
}

NVGcolor chordColor(int root, std::vector<int> chord, std::vector<NVGcolor> colors){
    int len = colors.size();
    int numNotes = chord.size();
    float r = 0, g = 0, b = 0;
    for(int note : chord) {
        int index = (root + note - 2) % len;
        r+=colors[index].r;
        g+=colors[index].g;
        b+=colors[index].b;
    }
    return nvgRGBf(r/numNotes, g/numNotes, b/numNotes);
}

} // end namespace
