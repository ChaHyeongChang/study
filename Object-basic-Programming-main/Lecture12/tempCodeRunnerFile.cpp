class Adder : public Calculator{

public:
    virtual int calc(int a, int b){
        return a + b;
    }
};

class Subtractor : public Calculator{
public:
    virtual int calc(int a, int b){
        return a-b;
    }
};
