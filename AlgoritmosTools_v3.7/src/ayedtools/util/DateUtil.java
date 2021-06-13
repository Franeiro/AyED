package ayedtools.util;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class DateUtil
{
   public static String fullTime()
   {
      GregorianCalendar gc = new GregorianCalendar();
      int y = gc.get(Calendar.YEAR);
      int m = gc.get(Calendar.MONTH)+1;
      int d = gc.get(Calendar.DAY_OF_MONTH);
      int ho = gc.get(Calendar.HOUR_OF_DAY);
      int mi = gc.get(Calendar.MINUTE);
      int se = gc.get(Calendar.SECOND);
      
      return y+"-"+m+"-"+d+" "+ho+"."+mi+"."+se;
   }
   
}
