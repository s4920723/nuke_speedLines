static const char* const CLASS = "SpeedLines";
static const char* const HELP =
        "Generates stylized motion blur using pre-rendered velocity data.";

#include <DDImage/Iop.h>
#include <DDImage/Row.h>
#include <DDImage/Knobs.h>
#include <DDImage/DrawIop.h>
#include <DDImage/Knob.h>

using namespace DD::Image;

class SpeedLines : public Iop
{
    bool drawX, drawY, drawZ; //Enable/Disable any of the RGB channels from the input
    int keyInterval; //How often a control point gets created
    int lifespan; //How long a control point persists for
    bool fade; //Does the line fade out after being cut off
    int maxSpeed, minSpeed; //Pixels per frame value below/above which a control point is discarded

   public:
    // Constructor
    SpeedLines(Node* node) : Iop(node)
    {
        drawX = drawY = drawZ = true;
        lifespan = 4;
    }

    // Destructor
    ~SpeedLines()
    {
    }

    void _validate(bool);
    void _request(int x, int y, int r, int t, ChannelMask channels, int count);
    void engine(int y, int x, int r, ChannelMask, Row &);
    virtual void knobs(Knob_Callback);

    const char* Class() const { return CLASS; }
    const char* node_help() const { return HELP; }

      //! Information to the plug-in manager of DDNewImage/Nuke.

      static const Iop::Description description;
};

static Iop* SpeedLinesCreate(Node* node)
{
  return new SpeedLines(node);
}

/*! The Iop::Description is how NUKE knows what the name of the operator is,
   how to create one, and the menu item to show the user. The menu item may be
   0 if you do not want the operator to be visible.
 */

const Iop::Description SpeedLines::description ( CLASS, "Merge/AddInputs", SpeedLinesCreate );

void SpeedLines::_validate(bool for_real)
{
    copy_info();
}

void SpeedLines::_request(int x, int y, int r, int t, ChannelMask channels, int count)
{
    input(0)->request(x, y, r, t, channels, count);
}

void SpeedLines::engine(int y, int x, int r, ChannelMask channels, Row& row)
{
    //row.get(input0(), y, x, r, channels);
    Row input0Row(x, r);
    input0Row.get(input0(), y, x, r, channels);

    foreach (z, channels)
    {
        const float* input0 = input0Row[z] + x;
       float* OUTP = row.writable(z);
       *OUTP = *input0;
    }
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
