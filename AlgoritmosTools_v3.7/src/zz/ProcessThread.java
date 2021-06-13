package zz;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ProcessThread extends Thread
{
   private ProcessBuilder processBuilder = null;
   private StringBuffer stringBuffer = null;
   private int exitValue = 0;
   
   public ProcessThread(ProcessBuilder pb)
   {
      this.processBuilder=pb;
   }

   public void run()
   {
      BufferedReader stdInput = null;
      BufferedReader stdError = null;
      try
      {
         Process p = processBuilder.start();
         stdInput=new BufferedReader(new InputStreamReader(p.getInputStream()));
         stdError=new BufferedReader(new InputStreamReader(p.getErrorStream()));

         // Read the output from the command
         stringBuffer = new StringBuffer();
         String s = null;
         while((s=stdInput.readLine())!=null)
         {
            stringBuffer.append(s+'\n');
         }

         // Read any errors from the attempted command
         while((s=stdError.readLine())!=null)
         {
            stringBuffer.append(s+'\n');
         }  
         
         exitValue = p.exitValue();
         stringBuffer.append("Exit value="+exitValue);
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
            if( stdError!=null) stdError.close();
            if( stdInput!=null) stdInput.close();
         }
         catch(Exception e2)
         {
            e2.printStackTrace();
            throw new RuntimeException(e2);
         }
      }
   }
   
   public String getProcessOutput()
   {
      return stringBuffer!=null?stringBuffer.toString():"";
   }

   public int getExitValue()
   {
      return exitValue;
   }
}
