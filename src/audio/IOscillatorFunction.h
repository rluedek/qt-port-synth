#ifndef IOSCILLATOR_FUNCTION_H
#define IOSCILLATOR_FUNCTION_H

class IOscillatorFunction
{
public:

virtual double calculate(double& time, double frequency) = 0;

private:
};

class Sine : public IOscillatorFunction
{
public:
    //ctor
    Sine();

    //dtor
    virtual ~Sine();
  
    double calculate(double& time, double frequency) override;
};

class Square : public IOscillatorFunction
{
public:
    //ctor
    Square();

    //dtor
    virtual ~Square();
  
    double calculate(double& time, double frequency) override;
};

class Triangle : public IOscillatorFunction
{
public:
    //ctor
    Triangle();

    //dtor
    virtual ~Triangle();
  
    double calculate(double& time, double frequency) override;
};


#endif