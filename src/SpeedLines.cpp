static const char* const CLASS = "SpeedLines";
static const char* const HELP =
        "Generates stylized motion blur using pre-rendered velocity data.";

#include <DDImage/Iop.h>
#include <DDImage/Row.h>
#include <DDImage/Knobs.h>
#include <DDImage/DrawIop.h>
#include <DDImage/Knob.h>

using namespace DD::Image;

static const char* const interpolation_types[] = {
  "smooth", "linear", 0
};

class SpeedLines : public Iop
{
   public:
    bool drawX, drawY, drawZ; //Enable/Disable any of the RGB channels from the input
    int keyInterval; //How often a control point gets created
    int lifespan; //How long a control point persists for
    bool fade; //Does the line fade out after being cut off
    float maxSpeed, minSpeed; //Pixels per frame value below/above which a control point is discarded
    enum { LINEAR, SMOOTH };
    int interpolation;
    SpeedLines(Node* node) : Iop(node)
    {
        inputs(3);
        drawX = drawY = drawZ = true;
        lifespan = 4;
        maxSpeed = 10.0f;
        minSpeed = 2.00f;
        interpolation = SMOOTH;
    }

    const char* input_label(int n, char*) const
    {
      switch (n) {
        case 0: return "Col";
        case 1: return "Vel";
        default: return "mask";
      }
    }

    void _validate(bool);
    void _request(int x, int y, int r, int t, ChannelMask channels, int count);
    void engine(int y, int x, int r, ChannelMask, Row &);
    virtual void knobs(Knob_Callback);

    const char* Class() const { return CLASS; }
    const char* node_help() const { return HELP; }
    static const Iop::Description description;
};

static Iop* SpeedLinesCreate(Node* node)
{
  return new SpeedLines(node);
}

const Iop::Description SpeedLines::description ( CLASS, "Merge/AddInputs", SpeedLinesCreate );

void SpeedLines::_validate(bool for_real)
{
    copy_info();
}

void SpeedLines::_request(int x, int y, int r, int t, ChannelMask channels, int count)
{
    input0().request(x, y, r, t, channels, count);
}

void SpeedLines::engine(int y, int x, int r, ChannelMask channels, Row& row)
{
    // Figure out how to get velocity daya -> look into Nuke Architecture
    // Figure out how to draw pixel -> look into Drawlops
    // Figure out how to not suck at this -> look into different career paths
    // If it becomes impossible try using OpenSplines
}

void SpeedLines::knobs(Knob_Callback f)
{
    Bool_knob(f, &drawX, "Draw X");
    Tooltip(f, "Enables/Disables the use of the velocity data on the X axis");
    Bool_knob(f, &drawY, "Draw Y");
    Tooltip(f, "Enables/Disables the use of the velocity data on the Y axis");
    Bool_knob(f, &drawZ, "Draw Z");
    Tooltip(f, "Enables/Disables the use of the velocity data on the Z axis");
    Int_knob(f, &lifespan, "Lifespan");
    Tooltip(f, "The amount of frames that a speedline persists for");
    Float_knob(f, &minSpeed, "Minimum Speed");
    Tooltip(f, "The minimal position difference required for a speedline segment to be drawn");
    Float_knob(f, &maxSpeed, "Maximum Speed");
    Tooltip(f, "The maximal position difference required for a speedline segment to be drawn");
    Enumeration_knob(f, &interpolation, interpolation_types, "interpolation", "Interpolation Type");
    Tooltip(f, "The type of intepolation used to draw each segment of the speedline");
}
