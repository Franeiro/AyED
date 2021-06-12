package ayedtools.apps.filesgenerator;

import java.util.ArrayList;
import java.util.List;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;

import ayedtools.apps.commons.est.Field;
import ayedtools.apps.commons.est.Struct;
import ayedtools.util.PropertiesUtil;
import ayedtools.util.StringUtil;

public class AyedFile
{
   private static final int ROW_STRUCT=1;
   private static final int ROW_TYPES=2;
   private static final int ROW_FIELDS=3;
   private static final int ROW_DATA=4;

   private String filename = null;
   private Struct struct = null;
   private List<Object[]> data = null;
   
   public AyedFile(Sheet sheet,int row,int col)
   {
      // filename
      filename = _readFilename(sheet,row,col);

      // struct
      struct = _readStruct(sheet,row,col);

      // types
      struct.setFields(_readFields(sheet,row,col));

      // data
      data = _readData(sheet,row,col);
   }

   @Override
   public String toString()
   {
      return filename;
   }
   
   private String _readFilename(Sheet sheet, int row, int col)
   {
      String s = sheet.getRow(row).getCell(col).getStringCellValue();
      int pos = s.lastIndexOf('/');
      return pos>=0?s.substring(pos+1):s;
   }
   
   private String _readSubfolder(Sheet sheet, int row, int col)
   {
      String s = sheet.getRow(row).getCell(col).getStringCellValue();
      int pos = s.lastIndexOf('/');
      return pos>=0?s.substring(0,pos):null;
   }
   
   public Struct _readStruct(Sheet sheet, int iRow, int iCol)
   {
      Struct est = new Struct();
      Row row=sheet.getRow(iRow+ROW_STRUCT);
      Cell cell=row.getCell(iCol);
      String sn=cell.getStringCellValue();

      // nombre de la estructura
      String name = sn.substring(sn.indexOf(' ')+1);
      est.setStructname(name);
      
      // campos y typos
      est.setFields(_readFields(sheet,iRow,iCol));

      return est;
   }

   public List<Field> _readFields(Sheet sheet, int iRow, int iCol)
   {
      List<Field> ret=new ArrayList<>();
      
      String proppath = "ayedtools.filesgenerator.excelscan";
      int maxcol = PropertiesUtil.getInt(proppath,"cols");
            
      Row rowType=sheet.getRow(iRow+ROW_TYPES);
      Row rowField=sheet.getRow(iRow+ROW_FIELDS);

      for(int j=iCol; j<maxcol; j++)
      {
         Cell cellType=rowType.getCell(j);
         Cell cellField=rowField.getCell(j);
         if(SheetUtil.isCellEmpty(cellType)) break;
         if(SheetUtil.isCellEmpty(cellField)) break;

         // field
         Field field = new Field();
         field.setFieldname(cellField.getStringCellValue());
         
         // type
         field.setFieldtype(cellType.getStringCellValue());
         
         ret.add(field);
      }
      
      return ret;
   }

   public List<Object[]> _readData(Sheet sheet, int iRow, int iCol)
   {
      ArrayList<Object[]> ret=new ArrayList<>();

      String proppath = "ayedtools.filesgenerator.excelscan";
      int maxrow = PropertiesUtil.getInt(proppath,"rows");
      
      
      for(int i=iRow+ROW_DATA; i<maxrow; i++)
      {
         Row row=sheet.getRow(i);
         if(row==null) break;

         int z=0;
         Object x[]=new Object[struct.getFields().size()];

         boolean fin=false;
         for(int j=iCol; j<iCol+struct.getFields().size(); j++)
         {
            Cell cell=row.getCell(j);
            if(SheetUtil.isCellEmpty(cell))
            {
               fin=true;
               break;
            }

            Object v=SheetUtil.getCellValue(cell,struct.getFields().get(z));
            x[z++]=v;
         }

         if(!fin)
         {
            ret.add(x);
         }
         else
         {
            break;
         }
      }
      
      return ret;
   }
   
   public Struct getStruct()
   {
      return struct;
   }
   
   public String getFilename()
   {
      return filename;
   }
      
   public List<Object[]> getData()
   {
      return data;
   }
   
   public String generateWriteFunction(String subdir)
   {
      String structname=getStruct().getStructname();
      String x = getWriteFunctionName();

      StringBuffer sb = new StringBuffer();

      sb.append("void "+x+"()\n");
      sb.append("{\n");
      
      sb.append("\tmkdir(\""+subdir+"\");\n");         

      sb.append("\tFILE* f = fopen(\""+subdir+"/"+getFilename()+"\","+"\"w+b\""+");\n");
      
      // declaro la variable r
      sb.append("\t"+structname+" r;\n\n");

      List<Object[]> data = getData();
      for(int i=0;i<data.size();i++)
      {
         sb.append(_generateWriteRecord(data.get(i)));         
      }
      
      sb.append("\tfclose(f);\n");
      sb.append("}\n\n");
      
      return sb.toString();
   }
   
   public String getWriteFunctionName()
   {
      String fn = getFilename();
      fn = fn.substring(0,fn.indexOf('.'));
      return "write"+StringUtil.charToUpperCase(fn,0);
   }
   
   public String getReadFunctionName()
   {
      String fn = getFilename();
      fn = fn.substring(0,fn.indexOf('.'));
      return "read"+StringUtil.charToUpperCase(fn,0);
   }

   private String _generateWriteRecord(Object[] record)
   {
      StringBuffer sb = new StringBuffer();
      
      // asigno datos a r
      String structname = getStruct().getStructname();
      for(int i=0;i<record.length;i++)
      {
         Field field = getStruct().getFields().get(i);
         String fieldname = field.getFieldname();
         // si es cadena
         if( field.isCharArray() ) 
         {
            sb.append("\tstrcpy(r."+fieldname+",\""+record[i]+"\");\n");            
         }
         else
         {
            if( field.isChar() )
            {
               sb.append("\tr."+fieldname+"='"+record[i]+"';\n");                        
            }
            else
            {
               sb.append("\tr."+fieldname+"="+record[i]+";\n");                        
            }
         }
      }      

      // grabo con fwrite
      sb.append("\tfwrite(&r,sizeof("+structname+"),1,f);\n\n");
      
      return sb.toString();
   }
   
   public String generateReadFunction(String subdir)
   {
      String structname=getStruct().getStructname();
      String x = getReadFunctionName();
      
      StringBuffer sb = new StringBuffer();
      
      sb.append("void "+x+"()\n");
      sb.append("{\n");
      sb.append("\tFILE* f = fopen(\""+subdir+"/"+getFilename()+"\","+"\"r+b\""+");\n");
      
      // declaro la variable r
      sb.append("\t"+structname+" r;\n\n");
      sb.append("\tfread(&r,sizeof("+structname+"),1,f);\n");
      sb.append("\twhile(!feof(f))\n");
      sb.append("\t{\n");
      sb.append("\t\tcout << "+getStruct().getToDebugName()+"(r) << endl;\n");
      sb.append("\t\tfread(&r,sizeof("+structname+"),1,f);\n");
      sb.append("\t}\n");
      sb.append("\n");
      sb.append("\tfclose(f);\n");
      sb.append("}\n\n");
      
      return sb.toString();
   }   
   
}
