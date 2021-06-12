package ayedtools.apps.filesgenerator;

import java.awt.Color;
import java.awt.Font;
import java.util.ArrayList;
import java.util.HashMap;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellStyle;
import org.apache.poi.ss.usermodel.FillPatternType;
import org.apache.poi.ss.usermodel.IndexedColors;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;

import ayedtools.apps.commons.est.Field;
import ayedtools.util.StringUtil;

public class SheetUtil_BKP
{
   public static final int SCANN_TYPE_endsWith=1;
   public static final int SCANN_TYPE_equals=2;

   private static HashMap<String,ArrayList<RowCol>> scanned = null;
   
   public static HashMap<String,ArrayList<RowCol>> getScanned()
   {
      return scanned;
   }
   
   public static void fullScan(Sheet sheet,int[] scannType,String[] pattern,int maxRow,int maxCol)
   {            
      scanned = new HashMap<>();
      
      for(int i=0; i<maxRow; i++)
      {
         Row row=sheet.getRow(i);
         if(row==null) continue;
         for(int j=0; j<maxCol; j++)
         {
            Cell cell=row.getCell(j);
            if( isCellEmpty(cell) ) continue;

            if(cell.getCellType()==Cell.CELL_TYPE_STRING)
            {
               String v=cell.getStringCellValue();
               
               for(int k=0; k<pattern.length;k++)
               {
                  boolean ok=false;
                  switch(scannType[k])
                  {
                     case SCANN_TYPE_endsWith:
                        if( v.endsWith(pattern[k])) ok=true;
                        break;
                     case SCANN_TYPE_equals:
                        if( v.equals(pattern[k])) ok=true;
                        break;
                  }
                  
                  // meto en la tabla
                  if( ok )
                  {
                     ArrayList<RowCol> arr = scanned.get(pattern[k]);
                     if(arr==null)
                     {
                        arr = new ArrayList<>();
                        scanned.put(pattern[k],arr);
                     }
                     
                     arr.add(new RowCol(i,j));
                  }
               }               
            }
         }
      }
   }
   
   public static boolean isCellEmpty(Cell cell)
   {
      if(cell==null)
      { // use row.getCell(x, Row.CREATE_NULL_AS_BLANK) to avoid null cells
         return true;
      }

      if(cell.getCellType()==Cell.CELL_TYPE_BLANK)
      {
         return true;
      }

      if(cell.getCellType()==Cell.CELL_TYPE_STRING&&cell.getStringCellValue().trim().isEmpty())
      {
         return true;
      }

      return false;
   }

   public static Object getCellValue(Cell cell,Field field)
   {
      Object value = null;
      
      // numerico
      if( cell.getCellType()==Cell.CELL_TYPE_NUMERIC )
      {
         value = cell.getNumericCellValue();
         if( field.isInt() )
         {
            value = ((Double)value).intValue();
         }
         else
         {
            if( field.isShort() )
            {
               value = ((Double)value).shortValue();               
            }
         }
      }
      else
      {
         // es string
         value = cell.getStringCellValue();
         if( field.isChar() )
         {
            value = new Character(((String)value).charAt(0));
         }
         else
         {
            // es char[]
            int len=field.getCharArrayLength();
            value=StringUtil.rpad((String)value,len); 
         }
      }
      
      return value;
   }
   
   public static void awtFontToExcelFont(Cell cell,java.awt.Font font)
   {
      org.apache.poi.ss.usermodel.Font newFont = cell.getSheet().getWorkbook().createFont();
      newFont.setBold(font.getStyle()==1);
      newFont.setFontHeightInPoints((short)font.getSize());
      newFont.setItalic(font.getStyle()==2); 
      cell.getCellStyle().setFont(newFont);
   }
   
   private static short awtColorToExcelColor(Color color)
   {
      if(color.equals(Color.BLACK)) return IndexedColors.BLACK.getIndex();
      if(color.equals(Color.BLUE)) return IndexedColors.BLUE.getIndex();
      if(color.equals(Color.RED)) return IndexedColors.RED.getIndex();
      if(color.equals(Color.GREEN)) return IndexedColors.GREEN.getIndex();
      if(color.equals(Color.ORANGE))return IndexedColors.ORANGE.getIndex();
      if(color.equals(Color.YELLOW))return IndexedColors.YELLOW.getIndex();
      if(color.equals(Color.WHITE)) return IndexedColors.WHITE.getIndex();
      if(color.equals(Color.GRAY)) return IndexedColors.GREY_50_PERCENT.getIndex();
      if(color.equals(Color.LIGHT_GRAY)) return IndexedColors.GREY_25_PERCENT.getIndex();
      if(color.equals(Color.DARK_GRAY)) return IndexedColors.GREY_80_PERCENT.getIndex();
      if(color.equals(Color.CYAN)) return IndexedColors.TURQUOISE.getIndex();
      if(color.equals(Color.MAGENTA)) return IndexedColors.VIOLET.getIndex();
      if(color.equals(Color.PINK)) return IndexedColors.PINK.getIndex();

      throw new RuntimeException("Color "+color.toString()+"no reconocido");
   }
   
   
   public static void setCellBackground(Sheet sheet,int r,int c,Color color)
   {
      CellStyle style = sheet.getWorkbook().createCellStyle();
      Row row = sheet.getRow(r);
      if( row==null )
      {
         row = sheet.createRow(r);
      }
      
      Cell cell = row.getCell(c);
      if( cell==null )
      {
         cell = row.createCell(c);
      }
      
      short sc = awtColorToExcelColor(color);
      style.setFillForegroundColor(sc);
      style.setFillPattern(FillPatternType.SOLID_FOREGROUND);
      cell.setCellStyle(style);
      
//      awtFontToExcelFont(cell,new Font("Arial",2,16));
   }
}
