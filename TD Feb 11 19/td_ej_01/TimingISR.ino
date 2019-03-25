void TimingISR()
{
  if(counter<50)  counter++;
  else counter=0;
  if(flagReset){
    flagReset=false;
    counter=0;
  }
  Update = ON;
}
