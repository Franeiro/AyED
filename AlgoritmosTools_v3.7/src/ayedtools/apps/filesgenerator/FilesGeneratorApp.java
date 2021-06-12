package ayedtools.apps.filesgenerator;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Desktop;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.filechooser.FileNameExtensionFilter;

import ayedtools.def.AlgoritmosToolsApp;
import ayedtools.util.FileUtil;
import ayedtools.util.Log;
import ayedtools.util.PropertiesUtil;
import zz.ProcessThread;

public class FilesGeneratorApp extends JPanel implements AlgoritmosToolsApp
{
   private JTextArea taConsole;
   private JTextField tfExcelFilename;
   private JTextField tfOutputFolder;
   private JCheckBox cbCompileYEjecute;
   private Component outer;

   public FilesGeneratorApp()
   {
      BorderLayout borderLayout=new BorderLayout();
      setLayout(borderLayout);

      outer=this;

      JPanel mainPanel=new JPanel();
      GridBagLayout gridBagLayout=new GridBagLayout();
      mainPanel.setLayout(gridBagLayout);

      JLabel lblNewLabel=new JLabel("Excel file");
      GridBagConstraints gbc_lblNewLabel=new GridBagConstraints();
      gbc_lblNewLabel.anchor=GridBagConstraints.EAST;
      gbc_lblNewLabel.fill=GridBagConstraints.VERTICAL;
      gbc_lblNewLabel.insets=new Insets(5,5,5,5);
      gbc_lblNewLabel.gridx=0;
      gbc_lblNewLabel.gridy=0;

      mainPanel.add(lblNewLabel,gbc_lblNewLabel);

      String path="ayedtools.filesgenerator.excelfilename";
      String excelFile=PropertiesUtil.getRawString(path);
      tfExcelFilename=new JTextField(excelFile,30);
      tfExcelFilename.setEditable(false);
      GridBagConstraints gbc_tfExcelFilename=new GridBagConstraints();
      gbc_tfExcelFilename.gridwidth=2;
      gbc_tfExcelFilename.insets=new Insets(5,5,5,5);
      gbc_tfExcelFilename.fill=GridBagConstraints.BOTH;
      gbc_tfExcelFilename.gridx=1;
      gbc_tfExcelFilename.gridy=0;
      mainPanel.add(tfExcelFilename,gbc_tfExcelFilename);
      tfExcelFilename.setColumns(10);

      JButton bChooce=new JButton("...");
      bChooce.addActionListener(new EscuchaBExcel());
      GridBagConstraints gbc_bChooce=new GridBagConstraints();
      gbc_bChooce.anchor=GridBagConstraints.SOUTH;
      gbc_bChooce.fill=GridBagConstraints.HORIZONTAL;
      gbc_bChooce.insets=new Insets(5,5,5,5);
      gbc_bChooce.gridx=3;
      gbc_bChooce.gridy=0;
      mainPanel.add(bChooce,gbc_bChooce);

      JButton bOpenExcel=new JButton("Open");
      bOpenExcel.addActionListener(new EscuchaBOpenExcel());
      GridBagConstraints gbc_bOpenExcel=new GridBagConstraints();
      gbc_bOpenExcel.gridheight = 1;
      gbc_bOpenExcel.fill=GridBagConstraints.BOTH;
      gbc_bOpenExcel.insets=new Insets(5,5,5,5);
      gbc_bOpenExcel.gridx=4;
      gbc_bOpenExcel.gridy=0;
      gbc_bOpenExcel.fill=GridBagConstraints.BOTH;
      mainPanel.add(bOpenExcel,gbc_bOpenExcel);

      JButton bOpenFolder=new JButton("Open");
      bOpenFolder.addActionListener(new EscuchaBOpenFolder());
      GridBagConstraints gbc_bOpenFolder=new GridBagConstraints();
      gbc_bOpenFolder.gridheight = 1;
      gbc_bOpenFolder.fill=GridBagConstraints.BOTH;
      gbc_bOpenFolder.insets=new Insets(5,5,5,5);
      gbc_bOpenFolder.gridx=4;
      gbc_bOpenFolder.gridy=1;
      gbc_bOpenFolder.fill=GridBagConstraints.BOTH;
      mainPanel.add(bOpenFolder,gbc_bOpenFolder);
      
      
      
      JLabel lblOutputFolder=new JLabel("Output folder");
      GridBagConstraints gbc_lblOutputFolder=new GridBagConstraints();
      gbc_lblOutputFolder.anchor=GridBagConstraints.EAST;
      gbc_lblOutputFolder.insets=new Insets(5,5,5,5);
      gbc_lblOutputFolder.gridx=0;
      gbc_lblOutputFolder.gridy=1;
      mainPanel.add(lblOutputFolder,gbc_lblOutputFolder);

      path="ayedtools.filesgenerator.outputfolder";
      String outputFolder=PropertiesUtil.getRawString(path);
      tfOutputFolder=new JTextField(outputFolder,30);
      tfOutputFolder.setEditable(false);
      GridBagConstraints gbc_tfOutputFolder=new GridBagConstraints();
      gbc_tfOutputFolder.gridwidth=2;
      gbc_tfOutputFolder.insets=new Insets(5,5,5,5);
      gbc_tfOutputFolder.fill=GridBagConstraints.BOTH;
      gbc_tfOutputFolder.gridx=1;
      gbc_tfOutputFolder.gridy=1;
      mainPanel.add(tfOutputFolder,gbc_tfOutputFolder);

      JButton bGenerateFiles = new JButton("<html><font color=blue>Generate Files</font></html>");
      bGenerateFiles.addActionListener(new EscuchaGenerateFiles());
      GridBagConstraints gbc_btnNewButton = new GridBagConstraints();
      gbc_btnNewButton.fill = GridBagConstraints.BOTH;
      gbc_btnNewButton.gridheight = 2;
      gbc_btnNewButton.gridx = 5;
      gbc_btnNewButton.gridy = 0;
      gbc_btnNewButton.insets = new Insets(5,5,5,5);
      mainPanel.add(bGenerateFiles, gbc_btnNewButton);
            
      final String x = "ayedtools.filesgenerator.compileandexcec";
      boolean selected=PropertiesUtil.getRawBoolean(x);
      cbCompileYEjecute = new JCheckBox("Compilar y ejecutar los script",selected);
      cbCompileYEjecute.addActionListener((e)->PropertiesUtil.setRawBoolean(x,cbCompileYEjecute.isSelected()));
      GridBagConstraints cbc_cye = new GridBagConstraints();
      cbc_cye.fill = GridBagConstraints.NONE;
      cbc_cye.gridheight = 2;
      cbc_cye.gridx = 6;
      cbc_cye.gridy = 0;
      cbc_cye.insets = new Insets(5,5,5,5);
      mainPanel.add(cbCompileYEjecute, cbc_cye);
      
      JButton bChooceOutput=new JButton("...");
      bChooceOutput.addActionListener(new EscuchaBOutput());
      GridBagConstraints gbc_bChooceOutput=new GridBagConstraints();
      gbc_bChooceOutput.fill=GridBagConstraints.BOTH;
      gbc_bChooceOutput.insets=new Insets(5,5,5,5);
      gbc_bChooceOutput.gridx=3;
      gbc_bChooceOutput.gridy=1;
      mainPanel.add(bChooceOutput,gbc_bChooceOutput);
      gbc_bChooceOutput.fill=GridBagConstraints.BOTH;
      add(mainPanel,BorderLayout.NORTH);
      
      taConsole=new JTextArea();
      taConsole.setFont(PropertiesUtil.getRawFont("ayedtools.awt.console.font"));
      taConsole.setEditable(false);
      add(new JScrollPane(taConsole),BorderLayout.CENTER);
      Log.putConsoleTo(this.getClass(),taConsole);

      // SUR
      JButton bClear = new JButton("Clear");
      bClear.addActionListener((e)->taConsole.setText(""));
      JPanel pSouth = new JPanel(new FlowLayout(FlowLayout.RIGHT));
      pSouth.add(bClear);
      add(pSouth,BorderLayout.SOUTH);      
   }

   class EscuchaBExcel implements ActionListener
   {
      public void actionPerformed(ActionEvent e)
      {
         JFileChooser fc=new JFileChooser();
         fc.setCurrentDirectory(new File("."));
         fc.setFileFilter(new FileNameExtensionFilter("Excel File","xlsx"));
         fc.showOpenDialog(outer);

         File f = fc.getSelectedFile();
         if( f!=null )
         {
            String sf = f.getAbsolutePath();
            tfExcelFilename.setText(sf);
            PropertiesUtil.setRawString("ayedtools.filesgenerator.excelfilename",sf);
         }         
      }
   }
   
   class EscuchaBOpenExcel implements ActionListener
   {
      public void actionPerformed(ActionEvent e)
      {
         try
         {
            String excel = tfExcelFilename.getText();
            Desktop.getDesktop().open(new File(excel));            
         }
         catch(Exception e2)
         {
            e2.printStackTrace();
            throw new RuntimeException(e2);
         }
      }
   }
   
   class EscuchaBOpenFolder implements ActionListener
   {
      public void actionPerformed(ActionEvent e)
      {
         try
         {
            String folder = tfOutputFolder.getText();
            Desktop.getDesktop().open(new File(folder));            
         }
         catch(Exception e2)
         {
            e2.printStackTrace();
            throw new RuntimeException(e2);
         }
      }
   }
   
   
   class EscuchaGenerateFiles implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent e)
      {
         try
         {
            taConsole.setText("");

            // leo las planillas del excel
            ArrayList<AyedSheet> planillas = FilesGenerator.readExcelData();
            
            // genero los script
            FilesGenerator.generateCScripts(planillas);

            if( cbCompileYEjecute.isSelected() )
            {
               _showCollRequeriments(); 
            
               // ejecuto los .exe
               String envVar=PropertiesUtil.getString("ayedtools.minwg.enviroment","var");
               String envVal=PropertiesUtil.getString("ayedtools.minwg.enviroment","value");
               String comp=PropertiesUtil.getRawString("ayedtools.minwg.compiler");
               String outputFiles = PropertiesUtil.getRawString("ayedtools.filesgenerator.outputfolder");
               String[] cppFiles = new File(outputFiles).list((a,b)->b.endsWith(".cpp"));

               ProcessBuilder pb = null;
               
               for(String cpp:cppFiles)
               {
                  // compilo cpp
                  Log.mssg("Compilando programa: "+cpp);
                  pb = new ProcessBuilder();
                  pb.environment().put(envVar,envVal);
                  pb.directory(new File("."));
                  pb.command(comp,"-o",outputFiles+"/"+cpp+".exe",outputFiles+"/"+cpp);
                  ProcessThread pt = new ProcessThread(pb);
                  pt.start();
                  pt.join();
                  Log.mssg(pt.getProcessOutput());
                  
                  // ejecuto exe
                  Log.mssg("Ejecutando programa: "+outputFiles+"/"+cpp+".exe");
                  pb = new ProcessBuilder();
                  pb.environment().put(envVar,envVal);
                  pb.directory(new File(outputFiles));
                  pb.command(outputFiles+"/"+cpp+".exe").start();
                  pt = new ProcessThread(pb);
                  pt.start();
                  pt.join();
                  Log.mssg(pt.getProcessOutput());
                  
                  Log.mssg("Borrando ejecutable: "+outputFiles+"/"+cpp+".exe");
                  FileUtil.deleteFileIfExists(outputFiles+"/"+cpp+".exe");
               }
            }
         }
         catch(Exception e2)  
         {
            e2.printStackTrace();
            throw new RuntimeException(e2);
         }
      }
   }

   class EscuchaBOutput implements ActionListener
   {
      public void actionPerformed(ActionEvent e)
      {
         JFileChooser fc=new JFileChooser();
         fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
         fc.setCurrentDirectory(new File("."));
         fc.showOpenDialog(outer);

         File f = fc.getSelectedFile();
         if( f!=null )
         {
            String sf = f.getAbsolutePath();
            tfOutputFolder.setText(sf);
            PropertiesUtil.setRawString("ayedtools.filesgenerator.outputfolder",sf);
         }         
      }
   }
   
   class Consola extends Thread
   {
      Process p = null;
      
      public Consola(Process p)
      {
         this.p = p;
      }
      
      public void run()
      {
         try
         {
            BufferedReader stdInput=new BufferedReader(new InputStreamReader(p.getInputStream()));
            BufferedReader stdError=new BufferedReader(new InputStreamReader(p.getErrorStream()));

            // Read the output from the command
            String s=null;
            while((s=stdInput.readLine())!=null)
            {
               taConsole.append(s+'\n');
            }

            // Read any errors from the attempted command
            while((s=stdError.readLine())!=null)
            {
               taConsole.append(s+'\n');
            }  
            
            int len = taConsole.getText().length();
            taConsole.select(len,len);
         }
         catch(Exception e)
         {
            e.printStackTrace();
            throw new RuntimeException(e);
         }
      }
   }
   
   @Override
   public String getAppName()
   {
      return "Files Generator";
   }

   @Override
   public void onFocus()
   {
   }
   
   public void _showCollRequeriments()
   {
      boolean mostrar=PropertiesUtil.getRawBoolean("ayedtools.filesgenerator.showmessage");
      if( mostrar )
      {
         String msg="<html>";
         msg+="Esta acción genera y ejecuta archivos <font color=blue>.exe</font>. Por esta razón es<br>";
         msg+="probable que el <font color=red><b>antivirus</b></font> intercepte la ejecución y los elimine<br>";
         msg+="o los ponga en baúl de cuarentena.<br><br>";
         msg+="Fijate cómo <font color=blue>debes configurar tu antivirus</font> para que confíe en<br>";
         msg+="este programa y no interfiera con su ejecución.<br><br></html>";

         JCheckBox cb = new JCheckBox("Mostrar de nuevo",true);
         JOptionPane.showMessageDialog(this,new Object[]{msg,cb},"Atención",JOptionPane.WARNING_MESSAGE);
         
         String prop="ayedtools.filesgenerator.showmessage";
         PropertiesUtil.setRawBoolean(prop,cb.isSelected()); 
      }
   }
}
