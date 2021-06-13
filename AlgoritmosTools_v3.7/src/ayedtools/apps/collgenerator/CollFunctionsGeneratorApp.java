package ayedtools.apps.collgenerator;

import java.awt.BorderLayout;
import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.KeyboardFocusManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import ayedtools.apps.commons.est.Struct;
import ayedtools.def.AlgoritmosToolsApp;
import ayedtools.util.AwtUtil;
import ayedtools.util.AyedButton;
import ayedtools.util.DateUtil;
import ayedtools.util.GridLayout2;
import ayedtools.util.PropertiesUtil;

public class CollFunctionsGeneratorApp extends JPanel implements AlgoritmosToolsApp
{
   private JTextArea taConsole=null;
   private JButton bGenerate=null;
   private String txtGenerateAndCopy="<html><font color=blue>Generate &amp; Copy</font></html>";
   private JButton bClear=null;
   private JCheckBox cbCollToString=null;

   private JCheckBox cbToFromStringGen=null;
   private JCheckBox cbInitGen=null;
   private JCheckBox cbToDebugGen=null;
   private JCheckBox cbEqualsGen=null;
   private JCheckBox cbStructsGen=null;
   private JCheckBox cbHeadersGen=null;
   private JCheckBox cbGenerateExcel=null;
   private JTextField tfSheetName = null;
   private AyedButton bExcelFilename  = null;
   public CollFunctionsGeneratorApp()
   {
      setLayout(new BorderLayout());
      
      // NORTE
      JPanel pCheckbox=new JPanel(new FlowLayout(FlowLayout.LEFT));

      String proppath="ayedtools.collections.generate";
      
      EscuchaCheckbox listener=new EscuchaCheckbox();
      Boolean b=PropertiesUtil.getBoolean(proppath,"headers");
      cbHeadersGen=new JCheckBox("Headers",b);
      cbHeadersGen.setActionCommand("headers");
      cbHeadersGen.addActionListener(listener);
      cbHeadersGen.setFocusable(false);
      pCheckbox.add(cbHeadersGen);

      b=PropertiesUtil.getBoolean(proppath,"structs");
      cbStructsGen=new JCheckBox("Structs",b);
      cbStructsGen.setActionCommand("structs");
      cbStructsGen.addActionListener(listener);
      cbStructsGen.setFocusable(false);
      pCheckbox.add(cbStructsGen);
      
      b=PropertiesUtil.getBoolean(proppath,"toString");
      cbToFromStringGen=new JCheckBox("toString/fromString",b);
      cbToFromStringGen.setActionCommand("toString");
      cbToFromStringGen.addActionListener(listener);
      cbToFromStringGen.setFocusable(false);

      pCheckbox.add(cbToFromStringGen);

      b=PropertiesUtil.getBoolean(proppath,"init");
      cbInitGen=new JCheckBox("init/create",b);
      cbInitGen.setActionCommand("init");
      cbInitGen.addActionListener(listener);
      cbInitGen.setFocusable(false);
      pCheckbox.add(cbInitGen);

      b=PropertiesUtil.getBoolean(proppath,"toDebug");
      cbToDebugGen=new JCheckBox("toDebug",b);
      cbToDebugGen.setActionCommand("toDebug");
      cbToDebugGen.addActionListener(listener);
      cbToDebugGen.setFocusable(false);
      pCheckbox.add(cbToDebugGen);

      b=PropertiesUtil.getBoolean(proppath,"equals");
      cbEqualsGen=new JCheckBox("equals",b);
      cbEqualsGen.setActionCommand("equals");
      cbEqualsGen.addActionListener(listener);
      cbEqualsGen.setFocusable(false);
      pCheckbox.add(cbEqualsGen);

      add(pCheckbox,BorderLayout.NORTH);

      // SUR
      JPanel pGrid = new JPanel(new GridLayout2(1,2));
      JPanel pButtons0=new JPanel(new FlowLayout(FlowLayout.RIGHT));
      bGenerate=new JButton(txtGenerateAndCopy);
      bGenerate.addActionListener(new EscuchaGenerateButton());
      bClear=new JButton("Clear");
      bClear.addActionListener(new EscuchaClearButton());
      pButtons0.add(bGenerate);
      pButtons0.add(bClear);
      
      JPanel pButtons1 = new JPanel(new FlowLayout(FlowLayout.LEFT));
      cbCollToString = new JCheckBox("Generate collToString");
      cbCollToString.setSelected(false);
      cbCollToString.setFocusable(false);
      cbCollToString.addActionListener(new EscuchaCollToString());
      pButtons1.add(cbCollToString);
      
      cbGenerateExcel = new JCheckBox("Generate on Excel");
      cbGenerateExcel.setSelected(false);
      cbGenerateExcel.setFocusable(false);
      cbGenerateExcel.addActionListener(new EscuchaExcel());
      
      tfSheetName = new JTextField(DateUtil.fullTime(),15);
      tfSheetName.setEnabled(false);
      pButtons1.add(cbGenerateExcel);
      pButtons1.add(tfSheetName);
      
      String path = "ayedtools.filesgenerator.excelfilename";
      String excelFilename = PropertiesUtil.getRawString(path);
      bExcelFilename = new AyedButton(excelFilename,50);
      bExcelFilename.setMaximumSize(new Dimension(100,bExcelFilename.getPreferredSize().height));
      bExcelFilename.addActionListener(new EscuchaBOpenExcel());            

      bExcelFilename.setEnabled(false);
      pButtons1.add(bExcelFilename);
      
      pGrid.add(pButtons1);
      pGrid.add(pButtons0);
      add(pGrid,BorderLayout.SOUTH);
      
      
      // CENTER
      taConsole=new JTextArea();
      taConsole.setFont(PropertiesUtil.getRawFont("ayedtools.awt.console.font"));
      taConsole.setTabSize(3);
      taConsole.setFocusTraversalKeys(KeyboardFocusManager.FORWARD_TRAVERSAL_KEYS, null);
      taConsole.setFocusTraversalKeys(KeyboardFocusManager.BACKWARD_TRAVERSAL_KEYS, null);
      add(new JScrollPane(taConsole),BorderLayout.CENTER);

      // foco al TextArea      
      taConsole.requestFocus();
   }
   
   @Override
   public void onFocus()
   {
      _showCollRequeriments();
      
      String path = "ayedtools.filesgenerator.excelfilename";
      String excelFilename = PropertiesUtil.getRawString(path);
      bExcelFilename.setText(excelFilename);
      validate();
      taConsole.requestFocus();      
   }
   
   public void _showCollRequeriments()
   {
      boolean mostrar=PropertiesUtil.getRawBoolean("ayedtools.collections.showmessage");
      if( mostrar )
      {
         String msg="<html>";
         msg+="Esta herramienta requiere que la implementación del TAD Coll<br>";
         msg+="incluya las siguientes funciones:<br><br>";
         msg+="string <font color=blue>collToString</font>(Coll&lt;T&gt; c);<br><br>";
         msg+="Debe retornar la cadena tokenizada que contiene los datos de<br>";
         msg+="la colección, precedida por el carácter separador.<br><br>";
         msg+="Coll&lt;T&gt; <font color=blue>collFromString</font>(string s);<br><br>";
         msg+="Debe armar y retorar una colección a partir de la cadena<br>";
         msg+="generada con la función anterior. Es decir: el primer carácter<br>";
         msg+="de s es carácter separador y el resto de la cadena es la cadena<br>";
         msg+="tokenizada que contiene los datos de la colección.<br><br></html>";

         JCheckBox cb = new JCheckBox("Mostrar de nuevo",true);
         JOptionPane.showMessageDialog(this,new Object[]{msg,cb},"Atención",JOptionPane.WARNING_MESSAGE);
         
         String prop="ayedtools.collections.showmessage";
         PropertiesUtil.setRawBoolean(prop,cb.isSelected()); 
      }
   }

   class EscuchaCheckbox implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent e)
      {
         String path = "ayedtools.collections.generate";
         JCheckBox cb=(JCheckBox)e.getSource();
         PropertiesUtil.setBoolean(path,cb.getActionCommand(),cb.isSelected());
      }
   }
   class EscuchaClearButton implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent e)
      {
         // genero, seteo
         taConsole.setText("");
         tfSheetName.setText(DateUtil.fullTime());
         taConsole.setEditable(true);
         taConsole.requestFocus();
         bGenerate.setText(txtGenerateAndCopy);
         cbCollToString.setSelected(false);
         bGenerate.setEnabled(true);
      }
   }
   
   public void justProcessed(JButton b)
   {
      if( b==null )
      {
         taConsole.setText("");
         taConsole.requestFocus();
         taConsole.setEditable(true);
         bGenerate.setText("Generate & Copy");
         bGenerate.setEnabled(true);
         cbCollToString.setText("Generate collToString");
         cbCollToString.setEnabled(true);
      }
         
      // deshabilito todo
      b.setText("Copied");
      bGenerate.setEnabled(false);
      cbCollToString.setEnabled(false);
      taConsole.setEditable(false);

      // muevo al inicio
      taConsole.select(0,0);      
   }
   
   class EscuchaExcel implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent e)
      {
         boolean b = cbGenerateExcel.isSelected(); 
         tfSheetName.setEnabled(b);   
         bExcelFilename.setEnabled(b);
         if( b )
         {
            tfSheetName.requestFocus();
            tfSheetName.selectAll();
         }
         else
         {
            tfSheetName.select(0,0);
         }
      }
   }

   class EscuchaGenerateButton implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent e)
      {
         // genero, seteo
         String t=taConsole.getText();
         
         int mask=0;
         mask+=cbEqualsGen.isSelected()?CollFunctionsCodeGenerator.GENERATE_EQUALS:0;
         mask+=cbHeadersGen.isSelected()?CollFunctionsCodeGenerator.GENERATE_HEADERS:0;
         mask+=cbInitGen.isSelected()?CollFunctionsCodeGenerator.GENERATE_INIT:0;
         mask+=cbToFromStringGen.isSelected()?CollFunctionsCodeGenerator.GENERATE_TOFROMSTRING:0;
         mask+=cbToDebugGen.isSelected()?CollFunctionsCodeGenerator.GENERATE_TODEBUG:0;
         mask+=cbStructsGen.isSelected()?CollFunctionsCodeGenerator.GENERATE_STRUCT:0;

         String gen = null;
         if( cbCollToString.isSelected() )
         {
            gen = CollFunctionsCodeGenerator.generateCollToStringImple(t);
         }
         else
         {
            gen=CollFunctionsCodeGenerator.generateCollFunctions(t,mask);
            
            List<Struct> structs = CollFunctionsCodeGenerator.parse(t);
            if( cbGenerateExcel.isSelected() )
            {
               String sheetNameDef = tfSheetName.getText().trim();
               CollFunctionsCodeGenerator.generateFilesGeneratorEntry(structs,sheetNameDef);
            }
         }
         
         taConsole.setText(gen);
         taConsole.select(0,0);
         taConsole.setEditable(false);
         bGenerate.setText("Copied!");
         bGenerate.setEnabled(false);
          
         // copio al clipboard
         AwtUtil.copyToClipboard(gen);
         
         setSelectedCheckbox(true);
      }      
   }
  
   static class EscuchaClose extends WindowAdapter
   {
      @Override
      public void windowClosing(WindowEvent e)
      {
         PropertiesUtil.store();
      }
   }
   
   class EscuchaCollToString implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent e)
      {
         boolean b = cbCollToString.isSelected();
         setSelectedCheckbox(!b);
      }
   }
   
   class EscuchaBOpenExcel implements ActionListener
   {
      public void actionPerformed(ActionEvent e)
      {
         try
         {
            _showCollRequerimentsExcel();
            String excel = bExcelFilename.getRealText();
            Desktop.getDesktop().open(new File(excel));            
         }
         catch(Exception e2)
         {
            e2.printStackTrace();
            throw new RuntimeException(e2);
         }
      }
   }
   
   
   public void setSelectedCheckbox(boolean b)
   {
      cbCollToString.setSelected(!b);
      cbEqualsGen.setEnabled(b);
      cbHeadersGen.setEnabled(b);
      cbInitGen.setEnabled(b);
      cbStructsGen.setEnabled(b);
      cbToDebugGen.setEnabled(b);
      cbToFromStringGen.setEnabled(b);
      cbGenerateExcel.setEnabled(b);

      boolean x = cbGenerateExcel.isSelected()?b:false;
      tfSheetName.setEnabled(x);
      bExcelFilename.setEnabled(x);
   }

   @Override
   public String getAppName()
   {
      return "Coll Functions Generator";
   }
   
   public void _showCollRequerimentsExcel()
   {
      String prop="ayedtools.filesgenerator.remembercloseexcel.showmessage";
      boolean mostrar=PropertiesUtil.getRawBoolean(prop);
      if( mostrar )
      {
         String excelFilename = bExcelFilename.getText();
         String planillaName= tfSheetName.getText();
         String msg="<html>";
         msg+="Recuerda <font color=red>cerrar</font> el archivo <font color=blue>"+excelFilename+"</font> para<br>";
         msg+="poder generar las entradas en la planilla <font color=blue>"+planillaName+"</font><br>";
         msg+="</html>";
         JCheckBox cb = new JCheckBox("Mostrar de nuevo",true);
         JOptionPane.showMessageDialog(this,new Object[]{msg,cb},"Atención",JOptionPane.WARNING_MESSAGE);
         
         PropertiesUtil.setRawBoolean(prop,cb.isSelected()); 
      }
   }

}
