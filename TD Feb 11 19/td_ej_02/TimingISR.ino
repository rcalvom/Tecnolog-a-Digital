void TimingISR()
{
  if(counter<50)  counter++;
  else counter=0;
  if(flagReset || counter1 >= 10){
    flagReset=false;
    flagSet=false;
    counter=0;
    counter1=0;
  }
  if(pulsaciones){
    counter1++;
    pulsaciones = false;
  }
  Update = ON;
  
}
