enum ActionType {
    add, modify, move, del
};

typedef struct record {
    enum ActionType ty; 			// add, modify, move, del

    // add
    bool isAddedShape;
    Shape *addedShape;
    struct Function *addedFunc;

    // modify
    bool isModifiedPoint;
    struct Point *modifiedPoint;
    double mpOldX, mpOldY;

    struct Func *modifiedFunc;
    struct Func *oldFunc;

    // move
    Shape *movedShape;
    double deltaX, deltaY;

    // del
    bool isDelShape;
    Shape *deletedShape;
    struct Func *deletedFunc;

    struct record *next;
}Record;