static const char* const CLASS = "SpeedLines";
static const char* const HELP =
        "Generates stylized motion blur using pre-rendered velocity data";

#include <DDImage/Iop.h>
#include <DDImage/Row.h>
#include <DDImage/Knobs.h>
#include <DDImage/DrawIop.h>
#include <DDImage/Knob.h>

using namespace DD::Image;


class SpeedLines : public Iop
{
    bool drawX, drawY, drawZ;
    int lifespan;
   public:
    // Constructor
    SpeedLines(Node* node) : NoIop(node)
    {
        drawX = drawY = drawZ = true;
        lifespan = 4;
    }

    // Destructor
    ~SpeedLines()
    {
    }

    void _validate(bool);
    void _request(int x, int y, int z, int t, ChannelMask channels, int count);
    void engine(int y, int x, int r, ChannelMask, Row &);
    virtual void knobs(Knob_Callback);

};

void SpeedLines::_validate(bool for_real)
{
    copy_info();
}

void SpeedLines::_request(int x, int y, int z, int t, ChannelMask channels, int count)
{
    input0.request(x, y, r, t, channels, count);
}

void SpeedLines::engine()
{
    // Consider using NoIop instead of an Iop which is an Iop that does not affect the input just draws ontop of it
    // Figure out how to get velocity daya -> look into Nuke Architecture
    // Figure out how to draw pixel -> look into Drawlops
    // Figure out how to not suck at this -> look into different career paths
    // If it becomes impossible try using OpenSplines
}

void SpeedLines::knobs(Knob_Callback f)
{
    Bool_knob(f, &drawX, "Draw X");
    Bool_knob(f, &drawY, "Draw Y");
    Bool_knob(f, &drawZ, "Draw Z");
    Int_knob(f, &lifespan, "Lifespan");
}
