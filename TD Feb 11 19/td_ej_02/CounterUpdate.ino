void CounterUpdate(void)
{
    CounterDisp[0] = counter1 /10;
    CounterDisp[1] = counter1 % 10;
    CounterDisp[2] = counter /10;
    CounterDisp[3] = counter %10;
    Update = OFF;
}
