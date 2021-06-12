package ayedtools.util;

import java.util.HashMap;

import javax.swing.JTextArea;

public class Log
{
   private static HashMap<String,Object> consoles;

   static
   {
      consoles = new HashMap<>();
   }
   
   public static void putConsoleTo(Class<?> clazz,Object o)
   {
      consoles.put(clazz.getName(),o);
   }
      
   public static void mssg(String mssg)
   {
      String tolog = "[LOG] "+mssg+"\n";

      StackTraceElement[] st = Thread.currentThread().getStackTrace();
      for(StackTraceElement ste:st)
      {
         String zz = ste.getClassName();
         int posPesos = zz.indexOf('$');
         zz=posPesos>0?zz.substring(0,posPesos):zz; // si es innerClass
         
         Object console = consoles.get(zz);
         if( console instanceof JTextArea)
         {
            JTextArea ta = (JTextArea)console;
            ta.append(tolog);
            int len = ta.getText().length();
            ta.select(len,len);
            return;
         }
      }
      System.out.println(tolog);
   }
}
