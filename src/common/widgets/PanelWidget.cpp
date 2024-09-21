#include "Widgets.hpp"

namespace nullset {

void PanelWidget::draw(const DrawArgs& args) {
    nvgFillColor(args.vg, nvgRGB(0x84, 0x7B, 0x89));
    nvgStrokeColor(args.vg, nvgRGB(0x22, 0x08, 0x26));
    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0.0, 0.0, box.size.x, box.size.y);
    nvgFill(args.vg);
    nvgStrokeWidth(args.vg, 2.0f);
    nvgStroke(args.vg);
}   

} // end namespace