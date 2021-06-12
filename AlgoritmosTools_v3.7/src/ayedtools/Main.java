package ayedtools;

import java.awt.BorderLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;

import javax.annotation.processing.SupportedSourceVersion;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import ayedtools.def.AlgoritmosToolsApp;
import ayedtools.util.AwtUtil;
import ayedtools.util.ExceptionUtil;
import ayedtools.util.ExeptionDialog;
import ayedtools.util.PropertiesUtil;

public class Main extends JFrame
{
   private JTabbedPane tabs=null;

   public Main()
   {
      tabs=new JTabbedPane();
      for(JPanel appPanel:_loadApps())
      {
         AlgoritmosToolsApp ayedtoolApp=(AlgoritmosToolsApp)appPanel;
         tabs.addTab(ayedtoolApp.getAppName(),appPanel);
      }

      int currTab = PropertiesUtil.getRawInt("ayedtools.apps.curr");
      tabs.setSelectedIndex(currTab);

      getContentPane().add(tabs,BorderLayout.CENTER);
      AwtUtil.setSize(this,0.8);
      AwtUtil.center(this);
      AwtUtil.setExitOnClose(this);
            
      tabs.addChangeListener(new EscuchaTab());
      addWindowListener(new EscuchaWindow());
      
      setVisible(true);
      
      // la app que aparece por default 
      AlgoritmosToolsApp currApp = (AlgoritmosToolsApp)tabs.getSelectedComponent();
      _onTabChage(currApp);
      
   }
   
   public void setAppTitle(String t)
   {
      setTitle("AYEDTools 2020 - "+t);
   }

   private List<JPanel> _loadApps()
   {
      ArrayList<JPanel> ret=new ArrayList<>();
      String sApps=PropertiesUtil.getRawString("ayedtools.apps");

      String[] apps=sApps.split(",");
      for(String sAppClassname:apps)
      {
         try
         {
            JPanel appPanel=(JPanel)Class.forName(sAppClassname).newInstance();
            ret.add(appPanel);
         }
         catch(Exception e)
         {
            e.printStackTrace();
            throw new RuntimeException(e);
         }
      }

      return ret;
   }
   
   private void _onTabChage(AlgoritmosToolsApp app)
   {
      setAppTitle(app.getAppName());
      app.onFocus();         
   }
   
   class EscuchaTab implements ChangeListener
   {
      @Override
      public void stateChanged(ChangeEvent e)
      {
         
         AlgoritmosToolsApp app = (AlgoritmosToolsApp)tabs.getSelectedComponent();
         _onTabChage(app);
      }      
   }
   
   class EscuchaWindow extends WindowAdapter
   {
      @Override
      public void windowClosing(WindowEvent e)
      {
         int currTab = tabs.getSelectedIndex();
         PropertiesUtil.setRawInt("ayedtools.apps.curr",currTab);
         PropertiesUtil.store();
      }
   }

   public static void main(String[] args) throws Exception
   {
      PropertiesUtil.load("algoritmos.properties");
      String stderr=PropertiesUtil.getRawString("ayedtools.errorlog");
      System.setErr(new PrintStream(new File(stderr)));

      Main win=new Main();      
      
      Thread.setDefaultUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler()
      {
         public void uncaughtException(Thread t, Throwable e)
         {
            ExceptionUtil.showException(win,e);
//            ExeptionDialog.showException(win,e);
         }
      });
   }
}
