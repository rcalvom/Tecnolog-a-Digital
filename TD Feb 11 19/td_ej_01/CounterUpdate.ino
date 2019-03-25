void CounterUpdate(void)
{
    CounterDisp[2] = counter / 10;  //decenas
    CounterDisp[3] = counter % 10;  //unidades 
    Update = OFF;
}
