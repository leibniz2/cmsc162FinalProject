#ifndef SIMULATOR_H
#define SIMULATOR_H

class Simulator {

    public:
        void init();
        void display();
        void reshape(int w, int h);
        void setup_display();
        void setup_reshape();
};

#endif