void TimingISR()
{
    halfsecond ++;
    Update = ON;
    if(halfsecond == 2){
      second ++;
      if(second == 60)
      {
        minute ++;
        if(minute == 60)
        {
          hour ++;
          if(hour == 24)hour = 0;
          minute = 0;
        }
        second = 0;
      }
      halfsecond = 0;
    }
    ClockPoint = (~ClockPoint) & 0x01;  
}
