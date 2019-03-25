void AlarmUpdate(void)
{
  tm1637.point(POINT_ON);
  AlarmDisp[0] = hourAlarm / 10;
  AlarmDisp[1] = hourAlarm % 10;
  AlarmDisp[2] = minuteAlarm / 10;
  AlarmDisp[3] = minuteAlarm % 10;
}
