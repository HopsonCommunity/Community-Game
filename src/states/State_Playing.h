#pragma once

#include "State_Base.h"

class Application;

namespace State
{
    class SPlaying : public SBase
    {
        public:
            SPlaying(Application& app);

            void input  () override;
            void update () override;
            void draw   () override;

        private:
            Application* m_pApplication;
    };
}
