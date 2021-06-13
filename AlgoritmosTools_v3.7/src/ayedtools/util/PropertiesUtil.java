package ayedtools.util;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Insets;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.LinkedHashMap;
import java.util.Properties;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class PropertiesUtil
{
   private static ClassLoader loader=null;
   private static Class<?> currClass=null;
   private static String currFilename=null;
   private static SortedProperties properties=null;

   static
   {
      try
      {
         loader=Thread.currentThread().getContextClassLoader();
      }
      catch(Exception e)
      {
         e.printStackTrace();
         throw new RuntimeException(e);
      }
   }

   public static void load(String filename)
   {
      try
      {
         if(currFilename!=filename)
         {
            currFilename=filename;
            InputStream is=new FileInputStream(filename);
            properties=new SortedProperties();
            properties.load(is);
            is.close();
         }
      }
      catch(Exception e)
      {
         e.printStackTrace();
         throw new RuntimeException(e);
      }
   }

   public static void store()
   {
      FileOutputStream fos=null;
      try
      {
         fos=new FileOutputStream(currFilename);
         properties.store(fos,"");
      }
      catch(Exception e)
      {
         e.printStackTrace();
         throw new RuntimeException(e);
      }
      finally
      {
         try
         {
            if(fos!=null) fos.close();
         }
         catch(Exception e2)
         {
            e2.printStackTrace();
            throw new RuntimeException(e2);
         }
      }
   }

   private static String _getPropertiesFilename(Class<?> clazz)
   {
      String propname=clazz.getName().replace('.','/');
      return propname+=".properties";
   }

   public static String getRawString(String proppath)
   {
      String s=properties.getProperty(proppath);
      return s==null?null:_processMacro(s);
   }

   public static String getString(String proppath, String stringname)
   {
      String s=getRawString(proppath);
      String toSearch=stringname+":[";
      int p=s.indexOf(toSearch)+toSearch.length();
      int q=s.indexOf("]",p);
      String x=s.substring(p,q);
      return x;
   }

   public static Integer getRawInt(String proppath)
   {
      return Integer.parseInt(getRawString(proppath));
   }

   public static Integer getInt(String proppath, String intname)
   {
      String x=getString(proppath,intname);
      return Integer.parseInt(x);
   }

   public static Boolean getRawBoolean(String bname)
   {
      String x=getRawString(bname);
      return x.toLowerCase().equals("true");
   }

   public static Boolean getBoolean(String proppath, String bname)
   {
      String x=getString(proppath,bname);
      return x.toLowerCase().equals("true");
   }

   public static Double getRawDouble(String proppath)
   {
      return Double.parseDouble(getRawString(proppath));
   }

   public static Double getDouble(String proppath, String doublename)
   {
      String x=getString(proppath,doublename);
      return Double.parseDouble(x);
   }

   private static Insets _decodeInsets(String s)
   {
      StringTokenizer st=new StringTokenizer(s,",");
      int t=Integer.parseInt(st.nextToken());
      int l=Integer.parseInt(st.nextToken());
      int b=Integer.parseInt(st.nextToken());
      int r=Integer.parseInt(st.nextToken());
      return new Insets(t,l,b,r);
   }

   public static Insets getRawInsets(String proppath)
   {
      String insetsName=getRawString(proppath).toLowerCase();
      return _decodeInsets(insetsName);
   }

   // public static Insets getInsets(Class<?> clazz, String proppath)
   // {
   // String s = getString(clazz,proppath,"insets");
   // return _decodeInsets(s);
   // }

   public static Color getRawColor(String proppath)
   {
      String colorName=getRawString(proppath).toLowerCase();
      return _decodeColor(colorName);
   }

   private static Color _decodeColor(String s)
   {
      StringTokenizer st=new StringTokenizer(s,",");
      if(st.countTokens()>1)
      {
         int r=Integer.parseInt(st.nextToken());
         int g=Integer.parseInt(st.nextToken());
         int b=Integer.parseInt(st.nextToken());
         return new Color(r,g,b);
      }
      else
      {
         s=s.toLowerCase();
         if(s.equals("blue")) return Color.BLUE;
         if(s.equals("red")) return Color.RED;
         if(s.equals("green")) return Color.GREEN;
         if(s.equals("orange")) return Color.ORANGE;
         if(s.equals("yellow")) return Color.YELLOW;
         if(s.equals("white")) return Color.WHITE;
         if(s.equals("black")) return Color.BLACK;
         if(s.equals("gray")) return Color.GRAY;
         if(s.equals("light_gray")) return Color.LIGHT_GRAY;
         if(s.equals("dark_gray")) return Color.DARK_GRAY;
         if(s.equals("cyan")) return Color.CYAN;
         if(s.equals("magenta")) return Color.MAGENTA;
         if(s.equals("pink")) return Color.PINK;
      }
      return null;
   }

   public static Color getColor(String proppath, String propname)
   {
      String s=getString(proppath,propname);
      return _decodeColor(s);
   }

   // public static Color getColor(Class<?> clazz, String proppath)
   // {
   // return getColor(clazz,proppath,"color");
   // }

   public static Font _decodeFont(String s)
   {
      StringTokenizer st=new StringTokenizer(s,",");
      String nom=st.nextToken();
      int style=Integer.parseInt(st.nextToken());
      int size=Integer.parseInt(st.nextToken());
      return new Font(nom,style,size);
   }

   public static Font getRawFont(String proppath)
   {
      String s=getRawString(proppath);
      return _decodeFont(s);
   }

   public static Font getFont(String proppath, String att)
   {
      String s=getString(proppath,att);
      return _decodeFont(s);
   }

   private static Dimension _decodeDimension(String s)
   {
      StringTokenizer st=new StringTokenizer(s,",");
      int width=Integer.parseInt(st.nextToken());
      int height=Integer.parseInt(st.nextToken());
      return new Dimension(width,height);
   }

   // public static Dimension getDimension(Class<?> clazz,String proppath)
   // {
   // String s = getString(clazz,proppath,"dimension");
   // return _decodeDimension(s);
   // }

   public Dimension getRawDimension(String proppath)
   {
      String s=getRawString(proppath);
      return _decodeDimension(s);
   }

   private static String _processMacro(String line)
   {
      StringBuffer sb=new StringBuffer();

      int i=0;
      int p1=line.indexOf("${");
      while(p1>=0)
      {
         sb.append(line.substring(i,p1));

         int p2=line.indexOf("}",p1);
         String r=getRawString(line.substring(p1+2,p2));

         sb.append(r);

         sb.append(line.substring(p2+1));

         line=sb.toString();
         sb.delete(0,sb.length());

         p1=line.indexOf("${");
      }

      return line;
   }

   public static void setRawString(String propname, String value)
   {
      properties.setProperty(propname,value);
   }

   // generate=init:[true],structs:[true],toDebug:[true],toStringFromString:[true],equals:[true],headers:[true]
   public static void setString(String path, String propname, String value)
   {
      String line=properties.getProperty(path);
      String toSearch=propname+":[";
      int p0=line.indexOf(toSearch)+toSearch.length()+1;
      int p1=line.indexOf(']',p0);
      line=line.substring(0,p0-1)+value+line.substring(p1);
      setRawString(path,line);
   }

   public static void setRawBoolean(String name, boolean b)
   {
      setRawString(name,b?"true":"false");
   }

   public static void setBoolean(String path, String name, boolean b)
   {
      setString(path,name,b?"true":"false");
   }

   public static void setRawInt(String name, int i)
   {
      setRawString(name,Integer.toString(i));
   }

   public static void setInt(String path, String name, int i)
   {
      setString(path,name,Integer.toString(i));
   }

   static class SortedProperties extends Properties
   {
      ArrayList<Object> keys = new ArrayList<>();
      
      @Override
      public synchronized Object put(Object key, Object value)
      {
//         if( !keys.contains(key) ) keys.add(key);
         if( get(key)==null ) keys.add(key);
         return super.put(key,value);
      }
      
      @Override
      public synchronized Enumeration<Object> keys()
      {
         return Collections.enumeration(keys);
      }
   }

   public static void main(String args[])
   {
      load("a.properties");

      System.out.println(getRawString("a"));
      System.out.println(getRawString("b"));
      System.out.println(getRawString("c"));
      System.out.println(getRawString("d"));
      System.out.println(getRawString("e"));

      PropertiesUtil.setRawString("b","Latifa");
      PropertiesUtil.setRawString("c","Camacho");
      PropertiesUtil.setRawString("b","Rujele");
      PropertiesUtil.setRawString("a","Kadija");
      PropertiesUtil.setRawString("a","Jade");
      PropertiesUtil.store();

      // store();
      //
      // load("ayedtools2.properties");
      //
      // System.out.println(getString(path,"headers"));
      // System.out.println(getString(path,"equals"));
      // System.out.println(getRawString(path));
      //
   }

}
