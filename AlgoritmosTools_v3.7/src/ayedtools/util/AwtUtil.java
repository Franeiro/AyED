package ayedtools.util;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;

import javax.swing.JFrame;

public class AwtUtil
{
   public static void copyToClipboard(String s)
   {
      Clipboard clipboard=Toolkit.getDefaultToolkit().getSystemClipboard();
      clipboard.setContents(new StringSelection(s),null);      
   }
   
   public static void setSize(Window tosize,double porc)
   {
      setSize(null,tosize,porc);
   }
   public static void setSize(Window parent,Window tosize,double porc)
   {
      int w,h;
      if( parent!=null )
      {
         w = (int)(parent.getSize().width*porc);
         h = (int)(parent.getSize().height*porc);
      }
      else
      {
         Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
         w = (int)(dim.width*porc);
         h = (int)(dim.height*porc);
      }
      
      tosize.setSize(w,h);
   }
   
   public static void center(Window toCenter) 
   {
      center(null,toCenter);
   }

   public static void center(Window parent,Window toCenter) 
   {
      int offsetX=0,offsetY=0;
      Dimension dimension;
      if( parent==null)
      {
         dimension = Toolkit.getDefaultToolkit().getScreenSize();
      }
      else
      {
         dimension = parent.getSize();
         offsetX=parent.getX();
         offsetY=parent.getY();
      }
         
      int x = (int) ((dimension.getWidth() - toCenter.getWidth()) / 2)+offsetX;
      int y = (int) ((dimension.getHeight() - toCenter.getHeight()) / 2)+offsetY;
      toCenter.setLocation(x, y);
  }

   public static void setExitOnClose(JFrame f)
   {
      f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
   }
}
