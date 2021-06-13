package ayedtools.util;

import javax.swing.JButton;

public class AyedButton extends JButton
{
   private String realText;
   private int maxchars;
   
   public AyedButton(String text,int maxchars)
   {
      this.maxchars = maxchars;
      setText(text);
   }
   
   @Override
   public void setText(String t)
   {
      this.realText = t;

      if( t.length() > maxchars )
      {
         t = "..."+t.substring(t.length()-maxchars,t.length());
      }
      
      super.setText(t);
   }
   
   public String getRealText()
   {
      return realText;
   }
}
