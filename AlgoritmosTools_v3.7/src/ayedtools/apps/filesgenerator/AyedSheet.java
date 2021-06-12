package ayedtools.apps.filesgenerator;

import java.io.RandomAccessFile;
import java.util.ArrayList;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;

import ayedtools.util.FileUtil;
import ayedtools.util.StringUtil;

public class AyedSheet
{
   private String sheetname;
   private ArrayList<AyedFile> ayedfiles;
   
   public AyedSheet(Sheet sheet)
   {
      // nombre
      sheetname = sheet.getSheetName();      
   }
   
   public String generateStript()
   {
      StringBuffer sb = new StringBuffer();
      
      // main header
      sb.append( _generateMainHeader() );
      
      // genero las estructuras
      for(AyedFile a:getAyedFiles())
      {
         sb.append(a.getStruct().generateStuct());
      }

      // genero las funciones que escriben
      for(AyedFile a:getAyedFiles())
      {
         sb.append(a.generateWriteFunction(getScriptName()));
      }

      // genero las funciones que leen y toString
      for(AyedFile a:getAyedFiles())
      {
         sb.append(a.getStruct().generateToDebug());
         sb.append(a.generateReadFunction(getScriptName()));
      }
      
      // main
      sb.append( _generateMain() );
      return sb.toString();
   }
   
   public ArrayList<AyedFile> getAyedFiles()
   {
      return ayedfiles;
   }
   
   public void setAyedFiles(ArrayList<AyedFile> archivos)
   {
      this.ayedfiles=archivos;
   }
   
   public String getSheetname()
   {
      return sheetname;
   }
   
   public String getScriptName()
   {
      return StringUtil.removeSpecialChars(_toScriptName(getSheetname()));
   }
   
   private static String _toScriptName(String s)
   {
      StringBuffer sb=new StringBuffer();
      for(int i=0; i<s.length(); i++)
      {
         char c=s.charAt(i);
         if(c==' ')
         {
            i++;
            c=s.charAt(i);
            c=(char)((c>='a'&&c<='z')?c-'a'+'A':c);
         }
         sb.append(c);
      }

      return sb.toString();
   }
   
   private String _generateMain()
   {
      StringBuffer sb = new StringBuffer();

      sb.append("int main()\n");
      sb.append("{\n");

      // invoco funciones
      for(AyedFile a:getAyedFiles())
      {
         String fWrite=a.getWriteFunctionName();
         String fRead=a.getReadFunctionName();

         sb.append("\tcout << \"--\" << \""+a.getFilename()+"\" << \"--\" << endl;\n");
         sb.append("\t"+fWrite+"();\n");
         sb.append("\t"+fRead+"();\n\n");
      }

      sb.append("\treturn 0;\n");
      sb.append("}\n");
      
      return sb.toString();
   }

   private String _generateMainHeader()
   {
      StringBuffer sb = new StringBuffer();
      sb.append("#include <iostream>\n");
      sb.append("#include <sstream>\n");
      sb.append("#include <string>\n");
      sb.append("#include <string.h>\n");
      sb.append("#include <stdio.h>\n");
      sb.append("#include <stdlib.h>\n");
      sb.append("#include <direct.h>\n");
      sb.append("using namespace std;\n\n");
//      sb.append("#include \"biblioteca/funciones/strings.hpp\"\n");
//      sb.append("#include \"biblioteca/funciones/tokens.hpp\"\n");
      sb.append("using namespace std;\n\n");
      
      return sb.toString();
   }
}
