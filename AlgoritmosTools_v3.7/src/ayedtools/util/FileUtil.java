package ayedtools.util;

import java.io.File;
import java.io.RandomAccessFile;

import javax.swing.JFileChooser;

public class FileUtil
{
   public static void createDirIfNotExists(String path)
   {
      File f = new File(path);
      if( !f.exists() )
      {
         f.mkdirs();
      }
   }
   
   public static void writeString(RandomAccessFile raf,String s)
   {
      try
      {
         byte[] b=s.getBytes();
         raf.write(b);         
      }
      catch(Exception e)
      {
         e.printStackTrace();
         throw new RuntimeException(e);
      }
   }

   public static void deleteFileIfExists(String s)
   {
      File f = new File(s);
      if( f.exists() )
      {
         f.delete();
      }
      
   }
}
