package ayedtools.apps.commons.est;

import ayedtools.util.StringUtil;

public class Field
{
   private int arrLength = 0;
   private String fieldname;
   private String fieldtype;
   
   public String getFieldname()
   {
//      if( isCharArray() )
//      {
//         return fieldname.substring(0,fieldname.indexOf('['));         
//      }
//      else
//      {
         return fieldname;
//      }
   }
   
   // puede ser: descr[20]
   public void setFieldname(String fieldname)
   {
//      arrLength = Math.max(arrLength,ifIsArrayGetLength(fieldtype));
      arrLength = Math.max(arrLength,ifIsArrayGetLength(fieldname));
      
      // no es array
      if( !isCharArray() )
      {      
         this.fieldname=fieldname.trim();
      }
      else
      {
         int pos = fieldname.indexOf('[');
         this.fieldname= fieldname.substring(0,pos);
      }
   }
   
   private int ifIsArrayGetLength(String s)
   {
      if( s==null ) return -1;
      
      int pos1 = s.indexOf('[');
      if( pos1>0 )
      {
         int pos2 = s.indexOf(']');
         return Integer.parseInt(s.substring(pos1+1,pos2));
      }      
      return -1;
   }
   
   public String getFieldtype()
   {
      return fieldtype;
   }
   
   // puede ser char[20]
   public void setFieldtype(String fieldtype)
   {
      arrLength = Math.max(arrLength,ifIsArrayGetLength(fieldtype));
//    if( isCharArray() )
      if( fieldtype.indexOf('[')>0 )
      {
         int pos = fieldtype.indexOf('[');
         this.fieldtype=fieldtype.substring(0,pos);         
      }
      else
      {
         this.fieldtype=fieldtype.trim();                  
      }
   }
   
   public boolean isCharArray()
   {
      return arrLength>0;
   }
   
   public boolean isString()
   {
      return fieldtype.equals("string");
   }
   
   public boolean isColl()
   {
      return fieldtype.startsWith("Coll");
   }
   
   public String getCollType()
   {
      int p1=fieldtype.indexOf('<');
      int p2=fieldtype.indexOf('>');
      return fieldtype.substring(p1+1,p2);      
   }

   public boolean isChar()
   {
      return fieldtype.equals("char") && !isCharArray();
   }
   
   public boolean isFinalType()
   {
      return fieldtype.equals("int")
            ||fieldtype.equals("short")
            ||fieldtype.equals("long")
            ||fieldtype.equals("char")
            ||fieldtype.equals("string")
            ||fieldtype.equals("bool")
            ||fieldtype.equals("double")
            ||fieldtype.equals("float")
            ||isCharArray();
   }
   
   public String getStringHungarianNotation()
   {
      return "s"+StringUtil.charToUpperCase(getFieldname(),0);
   }
   
   public boolean isDouble()
   {
      return fieldtype.equals("double");
   }
   public boolean isFloat()
   {
      return fieldtype.equals("float");
   }
   public boolean isInt()
   {
      return fieldtype.equals("int");
   }
   public boolean isShort()
   {
      return fieldtype.equals("short");
   }
   
   public int getCharArrayLength()
   {
      return arrLength;
   }

   public boolean isCollOfFinalType()
   {
      String collType = getCollType();
      return collType.equals("int")
            ||collType.equals("short")
            ||collType.equals("long")
            ||collType.equals("char")
            ||collType.equals("string")
            ||collType.equals("bool")
            ||collType.equals("double")
            ||collType.equals("float");
   }
   
}
