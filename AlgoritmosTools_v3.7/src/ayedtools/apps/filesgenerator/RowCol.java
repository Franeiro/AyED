package ayedtools.apps.filesgenerator;

public class RowCol
{
   public int row;
   public int col;
   
   public RowCol(int r,int c)
   {
      this.row = r;
      this.col = c;
   }
   
   @Override
   public String toString()
   {
      return "row="+row+", col="+col;
   }
}
