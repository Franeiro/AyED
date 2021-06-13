package ayedtools.apps.commons.est;

import java.util.ArrayList;
import java.util.List;

import ayedtools.util.StringUtil;

public class Struct
{
   private String structname;
   private char toStringSeparator;
   
   private List<String> templateTypenames = new ArrayList<>();
   private List<Field> fields = new ArrayList<>();   
   
   public List<String> getTemplateTypenames()
   {
      return templateTypenames;
   }

   public void setTemplateTypenames(ArrayList<String> templateTypenames)
   {
      this.templateTypenames=templateTypenames;
   }

   public List<Field> getFields()
   {
      return fields;
   }

   public void setFields(List<Field> fields)
   {
      this.fields=fields;
   }

   public void setStructname(String structname)
   {
      this.structname=structname.trim();
   }
   
   public String getStructname()
   {
      return structname;
   }

   public char getToStringSeparator()
   {
      return toStringSeparator;
   }

   public void setToStringSeparator(char toStringSeparator)
   {
      this.toStringSeparator=toStringSeparator;
   }
   
   public String getToStringName()
   {
      return getToStringName(structname);
   }
   
   public String getToStringName(String structname)
   {
      StringBuffer sb = new StringBuffer(structname);
      sb.setCharAt(0,Character.toLowerCase(sb.charAt(0)));
      return sb.toString()+"ToString"; 
   }
   
   public String getFromStringName()
   {
      return getFromStringName(structname);
   }
   
   public String getFromStringName(String structname)
   {
      StringBuffer sb = new StringBuffer(structname);
      sb.setCharAt(0,Character.toLowerCase(sb.charAt(0)));
      
      if( structname.equals("int")
         ||structname.equals("short")
         ||structname.equals("char")
         ||structname.equals("string")
         ||structname.equals("double"))
      {
         String type=structname.equals("short")?"int":structname;
         return "stringTo"+StringUtil.charToUpperCase(type,0); 
      }
      else
      {
         return sb.toString()+"FromString";          
      }
      
   }   
   
   public String generateToString()
   {
      StringBuffer sb = new StringBuffer();
      sb.append("string "+getToStringName()+"("+getStructname()+" x)\n");
      sb.append("{\n");
      sb.append("\tchar sep = "+(int)getToStringSeparator()+";\n");  
      ArrayList<String> sVars = new ArrayList<>();
      for(int i=0;i<getFields().size();i++)
      {
         Field field = getFields().get(i);
         String svar = field.getStringHungarianNotation();
         sVars.add(svar);
         if( field.isFinalType() )
         {
            if( field.isChar())
            {
               sb.append("\tstring "+svar+"=string(1,x."+field.getFieldname()+");\n");                  
               continue;
            }
            if( field.isCharArray() || field.isString() )
            {
               sb.append("\tstring "+svar+"=x."+field.getFieldname()+";\n");                  
               continue;
            }

            sb.append("\tstring "+svar+"=to_string(x."+field.getFieldname()+");\n");                  
            continue;
         }
         else
         {
            if( !field.isColl() )
            {
               sb.append("\tstring "+svar+"="+getToStringName(field.getFieldtype())+"(x."+field.getFieldname()+");\n");               
            }
            else
            {
               sb.append("\tstring "+svar+"=collToString<"+field.getCollType()+">(x."+field.getFieldname()+");\n");                              
            }
         }
      }
      
      String z = "\treturn ";
      for(int i=0; i<sVars.size();i++)
      {
         z+=sVars.get(i)+(i<sVars.size()-1?"+sep+":";\n");
      }
      
      sb.append(z);
      
      sb.append("}\n\n");
            
      return sb.toString();
   }
   
   
   public String generateFromString()
   {
      StringBuffer sb = new StringBuffer();
      sb.append(getStructname()+" "+getFromStringName()+"(string s)\n");
      sb.append("{\n");
      sb.append("\tchar sep = "+(int)getToStringSeparator()+";\n");  
      sb.append("\t"+getStructname()+" x;\n");

      for(int i=0;i<getFields().size();i++)
      {
         Field field = getFields().get(i);
         sb.append("\tstring t"+i+" = getTokenAt(s,sep,"+i+");\n");  

         if( field.isFinalType() )
         {
            if( field.isChar())
            {
               sb.append("\tx."+field.getFieldname()+"=(char)t"+i+"[0];\n");
               continue;
            }
            if( field.isCharArray() )
            {
               sb.append("\tstrcpy(x."+field.getFieldname()+",t"+i+".c_str());\n");
               continue;
            }
            
            if( field.isDouble()||field.isFloat() )
            {
               sb.append("\tx."+field.getFieldname()+"=stod(t"+i+");\n");
               continue;
            }
            
            if( field.isInt()||field.isShort() )
            {
               sb.append("\tx."+field.getFieldname()+"=stoi(t"+i+");\n");
               continue;
            }
            if( field.isString() )
            {
               sb.append("\tx."+field.getFieldname()+"=t"+i+";\n");
               continue;               
            }
         }
         else
         {
            if( !field.isColl() )
            {
               String fr=getFromStringName(field.getFieldtype());
               sb.append("\tx."+field.getFieldname()+"="+fr+"(t"+i+");\n");
            }
            else
            {
               String collType = field.getCollType();
               sb.append("\tx."+field.getFieldname()+"=collFromString<"+collType+">(t"+i+");\n");
            }
         }
      }
      
      String z = "\treturn x;\n";
      sb.append(z);
      sb.append("}\n\n");
      return sb.toString();
   }
   
   
   public String getInitName()
   {
      return StringUtil.charToLowerCase(getStructname(),0);
   }
   
   public String generateInit()
   {
      StringBuffer sb = new StringBuffer();
      sb.append(getStructname()+" "+getInitName()+"(");
      
      char varName = 'a';
      for(int i=0;i<getFields().size();i++)
      {
         Field field = getFields().get(i);
         String pName = field.getFieldname();
         
         varName = varName==pName.charAt(0)?++varName:varName;
         
         if( !field.isCharArray() )
         {
            sb.append(field.getFieldtype()+" "+pName);
            sb.append((i<getFields().size()-1)?",":")\n");
            continue;
         }
         else
         {   
            sb.append("string "+pName);
            sb.append((i<getFields().size()-1)?",":")\n");
            continue;
         }
      }
      sb.append("{\n");
      sb.append("\t"+getStructname()+" "+varName+";\n");
      for(int i=0;i<getFields().size();i++)
      {
         Field field = getFields().get(i);
         String pName = field.getFieldname();

         if( !field.isCharArray() )
         {
            sb.append("\t"+varName+"."+field.getFieldname()+" = "+pName+";\n");
            continue;
         }
         else
         {   
            sb.append("\tstrcpy("+varName+"."+field.getFieldname()+","+pName+".c_str());\n");
            continue;
         }
      }
      sb.append("\treturn "+varName+";\n");
      sb.append("}\n\n");
      return sb.toString();
   }

   public String getEqualsName()
   {
      return getEqualsName(getStructname());
   }
   
   public String getEqualsName(String structname)
   {
      StringBuffer sb = new StringBuffer(structname);
      sb.setCharAt(0,Character.toLowerCase(sb.charAt(0)));
      return sb.toString()+"Equals"; 
   }

   public String generateEquals()
   {
      StringBuffer sb = new StringBuffer();
      sb.append("bool "+getEqualsName()+"("+getStructname()+" a,"+getStructname()+" b)\n");
      sb.append("{\n");
      for(int i=0;i<getFields().size();i++)
      {
         Field field = getFields().get(i);
         if( field.isFinalType() )
         {
            if( !field.isCharArray() )
            {
               sb.append("\tif(a."+field.getFieldname()+"!=b."+field.getFieldname()+") return false;\n");
               continue;
            }
         }
         else
         {
            if( !field.isColl() )
            {
               String mtdEq = getEqualsName(field.getFieldtype());
               sb.append("\tif(!"+mtdEq+"(a."+field.getFieldname()+",b."+field.getFieldname()+")) return false;\n");
               continue;
            }
            else
            {
               String collType = field.getCollType();
               sb.append("\tif(collToString<"+collType+">(a."+field.getFieldname()+")!=collToString<"+collType+">(b."+field.getFieldname()+")) return false;\n");
               continue;
            }
         }
      }
      
      sb.append("\treturn true;\n");
      sb.append("}\n\n");
      return sb.toString();
   }

   public String getToDebugName()
   {
      return getToDebugName(getStructname());
   }
   
   public String getToDebugName(String structname)
   {
      StringBuffer sb = new StringBuffer(structname);
      sb.setCharAt(0,Character.toLowerCase(sb.charAt(0)));
      
      if( structname.equals("int")
        ||structname.equals("short")
        ||structname.equals("char")
        ||structname.equals("string")
        ||structname.equals("double"))
      {
         String type=structname.equals("short")?"int":structname;
         return type+"ToString"; 
      }
      else
      {
         return sb.toString()+"ToDebug"; 
      }
   }
   
   public String generateToDebug()
   {
      StringBuffer sb = new StringBuffer();
      sb.append("string "+getToDebugName()+"("+getStructname()+" x)\n");
      sb.append("{\n");
      sb.append("\tstringstream sout;\n");
      
      sb.append("\tsout<< \"[\";\n");
      for(int i=0;i<getFields().size();i++)
      {
         String comma = i<getFields().size()-1?"\tsout << \",\";\n":"";
         Field field = getFields().get(i);
         if( field.isFinalType() )
         {
            sb.append("\tsout << x."+field.getFieldname()+";\n");                  
            sb.append(comma);
            continue;
         }
         else
         {
            if( !field.isColl() )
            {
               String toDb = getToDebugName(field.getFieldtype());
               sb.append("\tsout << "+toDb+"(x."+field.getFieldname()+");\n");
               sb.append(comma);
            }
            else
            {
               String collType = field.getCollType();
               sb.append("\tcollReset<"+collType+">(x."+field.getFieldname()+");\n");
               sb.append("\tint n=collSize<"+collType+">(x."+field.getFieldname()+");\n");
               sb.append("\tsout << \"{\";\n");
               sb.append("\tfor(int i=0; i<n; i++)\n");
               sb.append("\t{\n");
               String fromStringFn = getFromStringName(collType);
               String toDb = getToDebugName(collType);
               sb.append("\t\t"+collType+" q = collGetAt<"+collType+">(x."+field.getFieldname()+",i,"+fromStringFn+");\n");               

               sb.append("\t\tsout << "+toDb+"(q)");        
               sb.append(" << ((i<n-1)?\",\":\"\");\n"); 
               
               sb.append("\t}\n");
               sb.append("\tsout << \"}\";\n");
               sb.append(comma);               
            }
         }
      }
      sb.append("\tsout<< \"]\";\n");      
      sb.append("\treturn sout.str();\n");      
      sb.append("}\n\n");
      return sb.toString();
   }   
   
   public String generateStuct()
   {
      StringBuffer sb = new StringBuffer();
      sb.append("struct "+getStructname()+"\n");
      sb.append("{\n");
      for(int i=0;i<getFields().size();i++)
      {
         Field field = getFields().get(i);
         sb.append("\t"+field.getFieldtype()+" "+field.getFieldname()); 
         if( field.isCharArray() )
         {
            sb.append("["+field.getCharArrayLength()+"]");            
         }
         sb.append(";\n");
      }
      sb.append("};\n\n");
      return sb.toString();      
   }

   public ArrayList<Field> getFieldsByType(String type)
   {
      ArrayList<Field> ret = new ArrayList<>();
      for(Field f:getFields())
      {
         if(f.getFieldtype().equals(type) )
         {
            ret.add(f);
         }
      }
      
      return ret;
   }
}
