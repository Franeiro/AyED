package ayedtools.util;

public class StringUtil
{
   
   public static String removeSpecialChars(String s)
   {
      StringBuffer sb = new StringBuffer(s);
      for(int i=0; i<sb.length();i++)
      {
         char c = sb.charAt(i);
         switch(c)
         {
            case 'Á': c = 'A';
            break;
            case 'É': c = 'E';
            break;
            case 'Í': c = 'I';
            break;
            case 'Ó': c = 'O';
            break;
            case 'Ú': c = 'U';
            break;
            case 'á': c = 'a';
            break;
            case 'é': c = 'e';
            break;
            case 'í': c = 'i';
            break;
            case 'ó': c = 'o';
            break;
            case 'ú': c = 'u';
            break;
            case 'ñ': c = 'n';
            break;
            case 'Ñ': c = 'N';
            break;
         }
         
         sb.setCharAt(i,c);
      }
      return sb.toString();
   }

   public static String replicate(int n,char c)
   {
      String s="";
      for(int i=0; i<n; i++)
      {
         s+=c;
      }
      return s;
   }
   
   public static String rpad(String s,int len)
   {
      String ret = s;
      int diff = len-s.length();
      if( diff>0 )
      {
         ret+=replicate(diff,' ');
      }
      
      return ret.substring(0,len-1);//+'\0';
   }   
   
   public static String charToLowerCase(String s, int pos)
   {
      StringBuffer sb = new StringBuffer(s);
      char c = s.charAt(pos);
      sb.setCharAt(pos,Character.toLowerCase(c));
      return sb.toString();
   }
   
   public static String charToUpperCase(String s, int pos)
   {
      StringBuffer sb = new StringBuffer(s);
      char c = s.charAt(pos);
      sb.setCharAt(pos,Character.toUpperCase(c));
      return sb.toString();
   }
   
//   public static String clear(String s)
//   {
//      StringBuffer sb = new StringBuffer(s.trim());
//      
//      boolean fin = false;
//      int i=0;
//      for(; i<sb.length() && !fin; i++)
//      {
//         char c=sb.charAt(i);
//         if( Character.isLetter(c) || Character.isDigit(c) )
//         {
//            fin = true;
//         }
//      }
//      
//      fin = false;
//      int j=sb.length()-1;
//      for(; j>=0 && !fin; j--)
//      {
//         char c=sb.charAt(j);
//         if( Character.isLetter(c) || Character.isDigit(c) )
//         {
//            fin = true;
//         }
//      }
//      
//      return sb.length()>0?sb.substring(i-1,j+2):"";
//   }

   public static String removeChars(String s,String chars)
   {
      StringBuffer sb = new StringBuffer();
      
      for(int i=0;i<s.length();i++)
      {
         char c = s.charAt(i);
         
         // itero los chars que no van
         boolean okChar = true;
         for(int j=0;j<chars.length();j++)
         {
            char toRmv = chars.charAt(j);
            if(c==toRmv)
            {
               okChar=false;
            }
         }
         
         if( okChar )
         {
            sb.append(c);
         }
      }
      
      return sb.toString();
   }   
}
