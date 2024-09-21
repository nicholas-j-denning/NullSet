#include "../../plugin.hpp"
#include <array>
#include <memory>

namespace nullset {

class PanelWidget : public Widget {
public:
    PanelWidget() = delete;
    inline PanelWidget(int hp){ setSize(mm2px(Vec(5.08 * hp, 128.5))); }
private:
    void draw(const DrawArgs& args) override;
};

class KeySelectWidget : public Widget {
public:
    KeySelectWidget() = delete;
    KeySelectWidget(Vec pos, Module* module, unsigned int paramIndex);
private:
    void draw(const DrawArgs& args) override;
    Module* _module;
    int _paramIndex;
    SvgWidget* keyDisplay;
    std::array<std::shared_ptr<Svg>, 12> keySvgs;
};

} // end namespace