#pragma once

class Application;

namespace State
{
    class SBase
    {
        public:
            SBase(Application& app)
            :   m_pApplication  (&app)
            { }

            virtual ~SBase() = default;

            SBase(SBase& other) = delete;
            SBase& operator= (SBase& other) = delete;

            virtual void input  () = 0;
            virtual void update () = 0;
            virtual void draw   () = 0;

        private:
            Application* m_pApplication;
    };
}


