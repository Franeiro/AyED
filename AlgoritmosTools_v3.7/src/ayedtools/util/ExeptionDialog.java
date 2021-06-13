package ayedtools.util;

import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
public class ExeptionDialog 
{
   public static void showException(JFrame parent,Throwable t)
   {
      JDialog dialog = new JDialog(parent,true);
      dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
      dialog.setTitle(t.getClass().getName());
      
      // consola en el centro
      JTextArea taConsole = new JTextArea();
      taConsole.setText(_loadText(t));
      
      taConsole.setEditable(false);
      dialog.getContentPane().add(new JScrollPane(taConsole),BorderLayout.CENTER);
      
      // close en el sur
      JPanel panel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
      JButton bClose = new JButton("Close");
      bClose.addActionListener((e)->dialog.dispose());
      panel.add(bClose);
      dialog.getContentPane().add(panel,BorderLayout.SOUTH);
      
      AwtUtil.setSize(parent,dialog,0.4);
      dialog.setVisible(true);
   }
   
   private static String _loadText(Throwable t)
   {
      StringBuffer sb = new StringBuffer();
      sb.append(t.getMessage()+"\n");
      for(StackTraceElement ste:t.getStackTrace())
      {
         sb.append(ste.toString()+"\n");
      }
      return sb.toString();
   }
}
