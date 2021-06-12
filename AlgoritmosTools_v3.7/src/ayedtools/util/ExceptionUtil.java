package ayedtools.util;

import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class ExceptionUtil 
{
   public static void showException(JFrame owner,Throwable ex)
   {
      String mssg = ex.getMessage();
      String exception = ex.getClass().getName();
      
      JOptionPane.showMessageDialog(owner,mssg,exception,JOptionPane.ERROR_MESSAGE);

   }
   
   public static void showExceptionX(JFrame owner,Throwable ex)
   {
      JDialog dialog = new JDialog(owner,ex.getClass().getCanonicalName(),true);
      JTextArea taConsole = new JTextArea();
      taConsole.setEditable(false);
      dialog.add(new JScrollPane(taConsole),BorderLayout.CENTER);
      
      // sur
      JPanel p = new JPanel(new FlowLayout(FlowLayout.RIGHT));
      JButton copy = new JButton("Copy to clipboard");
      copy.addActionListener((e)->AwtUtil.copyToClipboard(toString(ex)));
      p.add(copy);
      dialog.add(p,BorderLayout.SOUTH);      
      taConsole.setText(toString(ex));
      AwtUtil.setSize(owner,dialog,0.8);
      AwtUtil.center(owner,dialog);
      dialog.setVisible(true);
   }
   
   public static String toString(Throwable t)
   {
      StringBuffer sb = new StringBuffer(t.getMessage());
      for(StackTraceElement ste:t.getStackTrace())
      {
         sb.append("\t"+ste.toString()+"\n");
      }
    
      return sb.toString();
   }
   
         
}