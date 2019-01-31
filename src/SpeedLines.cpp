static const char* const CLASS = "SpeedLines";
static const char* const HELP =
        "Generates stylized motion blur using pre-rendered velocity data.";

#include <DDImage/NukeWrapper.h>
#include <DDImage/Iop.h>
#include <DDImage/Row.h>
#include <DDImage/DrawIop.h>
#include <DDImage/Knob.h>
#include <DDImage/Knobs.h>
#include <DDImage/DDMath.h>

using namespace DD::Image;

static const char* const interpolation_types[] = {
  "linear", "smooth", 0
};

class SpeedLines : public DrawIop
{
    bool drawX, drawY, drawZ; //Enable/Disable any of the RGB channels from the input
    int keyInterval; //How often a control point gets created
    int lifespan; //How long a control point persists for
    bool fade; //Does the line fade out after being cut off
    float maxSpeed, minSpeed; //Pixels per frame value below/above which a control point is discarded
    enum { LINEAR, SMOOTH };
    int interpolation;

   public:
    const char* input_label(int n, char*) const;
    void _validate(bool);
    bool draw_engine(int y, int x, int r, float *buffer);
    SpeedLines(Node* node) : DrawIop(node)
    {
        inputs(2);
        drawX = drawY = drawZ = true;
        lifespan = 4;
        maxSpeed = 10.0f;
        minSpeed = 2.00f;
        interpolation = SMOOTH;
    }

    virtual void knobs(Knob_Callback);

    const char* Class() const { return CLASS; }
    const char* node_help() const { return HELP; }
    static const Iop::Description description;
};


const char* SpeedLines::input_label(int n, char*) const
{
    switch (n)
    {
        case 0: return "Vel";
        default: return "Col";
    }
}


void SpeedLines::_validate(bool for_real)
{
    copy_info();
    set_out_channels(Mask_All);
}

bool SpeedLines::draw_engine(int y, int x, int r, float *buffer)
// y - row, x vertical offset, r - end of row, channels - list of usable channels, row - pointer to the current row being operated on
{
   // row.get(input0(), y, x, r, channels);
   // Figure out how to get velocity daya -> look into Nuke Architecture
    // Figure out how to draw pixel -> look into Drawlops/ DDImage/gl.h
    // If it becomes impossible try using OpenSplines

    /* Step 1: Create an array of speed lines
     * Steo 2: Every speed line has an array of control points and a draw_segment(point A, point B) function.
     * Step 3: Every control point has XY pixel coordiantes, UV color, XYZ velocity value and Frame
     * Step 4: On every frame up to the current one go through the buffer and look for UV color matches since they do not change over time
     * Step 5: Record the averaged out XY pixel coordinates of the UV color matches.
     * Step 6: Look up velocity values at pixel coordinates.
     * Step 7: Compare velocity  velocity between this and previuos frame and if (minVel < currentVel-PreviousVel < maxVel) => draw line
     *  using draw_segments(currentControlPoint.poisiton, previousControlPoint.position)
     * Steo 8: TBA (lifetime etc.) */
}

void SpeedLines::knobs(Knob_Callback f)
{
    input_knobs(f);
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
    output_knobs(f);
}


static Op* build(Node* node)
{
  return new SpeedLines(node);
}

const Iop::Description SpeedLines::description ( CLASS, "Merge/AddInputs", build);
