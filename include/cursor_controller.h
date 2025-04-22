#ifndef GUARD_CURSOR_CONTROLLER_H
#define GUARD_CURSOR_CONTROLLER_H

class CursorController {
    public:
        virtual ~CursorController() = default;
        virtual void update() = 0;
};

#endif // GUARD_CURSOR_CONTROLLER_H