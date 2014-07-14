
#include "../../utt/icase.hpp"
#include "../../utils/sweeper.hpp"
#include "../../utt/utt_assert.hpp"

class sweeper_test : public icase
{
public:
    virtual bool run()
    {
        using namespace utt;
        int x = 0;
        {
            sweeper s([&]() { x++; }, [&]() { x++; });
            assert.equal(x, 1);
        }
        assert.equal(x, 2);
        return true;
    }
    DEFINE_CASE(sweeper_test);
};

REGISTER_CASE(sweeper_test);

