static const char* const CLASS = "SpeedLines";
static const char* const HELP =
        "Generates stylized motion blur using pre-rendered velocity data";

#include <DDImage/Iop.h>
#include <DDImage/Row.h>
#include <DDImage/Knobs.h>

using namespace DD::Image;


class SpeedLines : public Iop
{
   public:
    // Constructor
    SpeedLines(Node* node) : NoIop(node)
    {

    }

    // Destructor
    ~SpeedLines()
    {
    }

    void _validate(bool);
    void _request(int x, int y, int z, int t, ChannelMask channels, int count);
    void engine(int y, int x, int r, ChannelMask, Row &);

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
    // Get velocity data
    // Draw pixel
    //
    //
}
