package ayedtools.apps.filesgenerator;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;

import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import ayedtools.util.FileUtil;
import ayedtools.util.Log;
import ayedtools.util.PropertiesUtil;

public class FilesGenerator
{
   public static final String EXCEL_FILENAME_PROP="ayedtools.filesgenerator.excelfilename";
   public static final String OUTPUT_FOLDER_PROP="ayedtools.filesgenerator.outputfolder";

   public static void generateCScripts(ArrayList<AyedSheet> planillas) 
   {
      try
      {
         // itero la estructura
         for(AyedSheet planilla:planillas)
         {
            // donde lo voy a generar el script
            String prop="ayedtools.filesgenerator.outputfolder";
            String subfolder = PropertiesUtil.getRawString(prop);
            File fSubfolder = new File(subfolder);
            FileUtil.createDirIfNotExists(subfolder);
            
            // nombre del .cpp (Script)
            String scriptName=planilla.getScriptName()+".cpp";
            FileUtil.deleteFileIfExists(subfolder+"/"+scriptName);
            
            // genero el script
            Log.mssg("Generando script: "+scriptName);
            File f=new File(fSubfolder,scriptName);         

            // escribo el archivo
            RandomAccessFile raf=new RandomAccessFile(f,"rw");
            FileUtil.writeString(raf,planilla.generateStript());
            raf.close();
         }
         
      }
      catch(Exception e)
      {
         e.printStackTrace();
         throw new RuntimeException(e);
      }
   }

   public static ArrayList<AyedSheet> readExcelData() 
   {
      FileInputStream fis=null;
      Workbook excel=null;

      try
      {
         ArrayList<AyedSheet> ret=new ArrayList<>();

         // abro el excel
         String prop = "ayedtools.filesgenerator.excelfilename";
         String filename=PropertiesUtil.getRawString(prop);
         Log.mssg("Abriendo archivo: "+filename);
         fis=new FileInputStream(filename);
         excel=new XSSFWorkbook(fis);

         
         // maxrows/maxcols
         String proppath = "ayedtools.filesgenerator.excelscan";
         int maxcols = PropertiesUtil.getInt(proppath,"cols");
         int maxrows = PropertiesUtil.getInt(proppath,"rows");
         
         // itero las paginas
         for(int i=0; i<excel.getNumberOfSheets(); i++)
         {
            // i-esima pagina            
            Sheet sheet=excel.getSheetAt(i);
            
            // posicion de cada uno de los archivos descriptos
//            SheetUtil.getScanned().clear();
            SheetUtil.fullScan(sheet,new int[] {SheetUtil.SCANN_TYPE_endsWith, }
                                 ,new String[] {".dat"},maxrows,maxcols);
                        
            AyedSheet planilla = new AyedSheet(sheet);
            Log.mssg("Procesando planilla: "+planilla.getSheetname());
            ret.add(planilla);

            ArrayList<AyedFile> archivos=new ArrayList<>();
            planilla.setAyedFiles(archivos);

            ArrayList<RowCol> posFiles=SheetUtil.getScanned().get(".dat");
            for(int j=0; posFiles!=null&&j<posFiles.size(); j++)
            {
               RowCol rc=posFiles.get(j);

               // instancio
               AyedFile a=new AyedFile(sheet,rc.row,rc.col);
               Log.mssg("Archivo: "+a+", leido!");
               archivos.add(a);
            }
         }

         return ret;
      }
      catch(IOException e)
      {
         e.printStackTrace();
         throw new RuntimeException();
      }
      finally
      {
         try
         {
            if(excel!=null) excel.close();
            if(fis!=null) fis.close();
         }
         catch(Exception e2)
         {
            e2.printStackTrace();
            throw new RuntimeException(e2);
         }
      }
   }
   

}