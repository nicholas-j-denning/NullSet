#include "../../plugin.hpp"
#include <vector>
#include <string>

namespace nullset::palette {

class ModalPaletteWidget : public Widget {
public:
    ModalPaletteWidget() = delete;
    ModalPaletteWidget(
        Vec pos, 
        Vec size,
        std::vector<int> innerChord,
        std::vector<int> outerChord,
        std::vector<NVGcolor> _colors,
        std::vector<std::string> svgs,
        Module* module,
        std::vector<int> _innerIndex,
        std::vector<int> _outerIndex,
        int centerIndex
    );
private:
    void draw(const DrawArgs& args) override;
    void drawCircle(const DrawArgs& args, Vec center, float radius, NVGcolor color);
    Vec radial2Vec(float radius, float angle);
    void makeInput(float angle, float r, int index, Module* module);
    void makeButton(float angle, float r, int index, Module* module);
    void makeLight(float angle, float r, int index, Module* module);
    void makeLabel(float angle, float r, std::string svg);
    std::vector<NVGcolor> colors = {};
    std::vector<int> innerIndex = {};
    std::vector<int> outerIndex = {};
    int centerIndex = 0;
};

NVGcolor chordColor(int root,std::vector<int> chord, std::vector<NVGcolor> colors);

} // end namespace
