#ifndef CHAMBER_H
#define CHAMBER_H


class Chamber {
    public:
        // A chamber has an x, y location (origin) in a larger board
        // and a width and height
        int x, y, width, height;
        Chamber(int x, int y, int width, int height);
};

#endif
