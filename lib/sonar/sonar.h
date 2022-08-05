#ifndef SONAR_H
#define SONAR_H

namespace sonar{
    class SonarManager{
        public:
            SonarManager();
            void setup();
            void poll();
    };
}


#endif