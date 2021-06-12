package ayedtools.apps.collgenerator;

import java.awt.Color;
import java.awt.Font;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.List;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellStyle;
import org.apache.poi.ss.usermodel.FillPatternType;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

import ayedtools.apps.commons.est.Field;
import ayedtools.apps.commons.est.Struct;
import ayedtools.apps.filesgenerator.SheetUtil;
import ayedtools.util.PropertiesUtil;
import ayedtools.util.StringUtil;

public class CollFunctionsCodeGenerator
{
	public static final int GENERATE_TOFROMSTRING=1;
	public static final int GENERATE_TODEBUG=2;
	public static final int GENERATE_INIT=4;
	public static final int GENERATE_EQUALS=8;
	public static final int GENERATE_HEADERS=16;
	public static final int GENERATE_STRUCT=32;

	public static List<Struct> parse(String t)
	{
		return _loadStructs(t);
	}

	private static List<Struct> _loadStructs(String t)
	{
		ArrayList<Struct> ret=new ArrayList<>();

		t=_removeComments(t);
		t=StringUtil.removeChars(t,"\n\r");

		ArrayList<String> templateTypenames=new ArrayList<>();

		char sep=1;
		String[] split=t.split("struct");
		for(String x:split)
		{
			if(x.length()==0)
			{
				continue;
			}
			if(x.contains("template"))
			{
				_procesarTemplates(x,templateTypenames);
				continue;
			}

			int idxAbre=x.indexOf('{');
			int idxCierra=x.indexOf('}');

			String structname=x.substring(0,idxAbre);
			Struct struct=new Struct();
			struct.setTemplateTypenames(templateTypenames);
			struct.setStructname(structname);
			struct.setToStringSeparator(sep++);

			String[] split2=x.substring(idxAbre+1,idxCierra).split(";");

			for(String w:split2)
			{
				w=w.trim();
				if(w.isEmpty()) continue;

				int pEsp=w.indexOf(' ');
				Field field=new Field();
				field.setFieldtype(w.substring(0,pEsp));
				field.setFieldname(w.substring(pEsp+1));
				struct.getFields().add(field);
			}

			ret.add(struct);
		}

		return ret;
	}

	private static void _procesarTemplates(String x, ArrayList<String> templateTypenames)
	{

		String[] split=x.substring("template".length()+1).split("typename");
		for(String s:split)
		{
			if(s.isEmpty()) continue;
			s=StringUtil.removeChars(s,", ;<>\n\r");
			if(s.isEmpty()) continue;
			templateTypenames.add(s);
		}
	}

	public static String _removeComments(String t)
	{
		int p1=t.indexOf("//");
		int p2=t.indexOf('\n',p1);
		while(p1>=0)
		{
			String x=t.substring(0,p1);
			String y=t.substring(p2);
			t=x+y;
			p1=t.indexOf("//");
			p2=t.indexOf('\n',p1);
		}

		return t;
	}

	public static String generate(List<Struct> structs, int mask)
	{
		StringBuffer sb=new StringBuffer();

		if((mask&GENERATE_HEADERS)!=0)
		{
			sb.append("#ifndef _MAINHPP\n");
			sb.append("#define _MAINHPP\n");
			sb.append("#include <iostream>\n");
			sb.append("#include <iostream>\n");
			sb.append("#include <sstream>\n");
			sb.append("#include <string>\n");
			sb.append("#include <string.h>\n");
			sb.append("#include <stdlib.h>\n");
			sb.append("#include \"biblioteca/funciones/strings.hpp\"\n");
			sb.append("#include \"biblioteca/funciones/tokens.hpp\"\n");
			sb.append("#include \"biblioteca/tads/Coll.hpp\"\n");
			sb.append("using namespace std;\n\n");
		}

		if((mask&GENERATE_STRUCT)!=0)
		{
			for(Struct struct:structs)
			{
				String s=struct.generateStuct();
				sb.append(s);
			}
		}

		for(Struct struct:structs)
		{
			if((mask&GENERATE_TOFROMSTRING)!=0)
			{
				String s=struct.generateToString();
				sb.append(s);

				s=struct.generateFromString();
				sb.append(s);
			}

			if((mask&GENERATE_TODEBUG)!=0)
			{
				String s=struct.generateToDebug();
				sb.append(s);
			}

			if((mask&GENERATE_INIT)!=0)
			{
				String s=struct.generateInit();
				sb.append(s);
			}

			if((mask&GENERATE_EQUALS)!=0)
			{
				String s=struct.generateEquals();
				sb.append(s);
			}
		}

		if((mask&GENERATE_HEADERS)!=0)
		{
			sb.append("#endif\n");
		}
		
		
		return sb.toString();
	}

	public static String generateCollFunctions(String t, int mask)
	{
		List<Struct> structs=parse(t);
		return generate(structs,mask);
	}

	public static void generateFilesGeneratorEntry(List<Struct> structs, String sheetName)
	{
		FileInputStream fis=null;
		FileOutputStream fos=null;
		try
		{
			String prop="ayedtools.filesgenerator.excelfilename";
			String excelfilename=PropertiesUtil.getRawString(prop);
			fis=new FileInputStream(excelfilename);
			XSSFWorkbook workbook=new XSSFWorkbook(fis);

			// creo la planilla
			XSSFSheet sheet=workbook.createSheet(sheetName);

			for(int i=0; i<100; i++)
			{
				Row row=sheet.createRow(i);
				for(int j=0; j<100; j++)
				{
					row.createCell(j);
				}
			}

			int col=1;
			for(Struct st:structs)
			{
				_generarArchivoEnPlanilla(sheet,st,col);
				col+=st.getFields().size()+1;
			}

			fos=new FileOutputStream(excelfilename);
			workbook.write(fos);
			workbook.close();

			fis.close();
			fos.close();
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			throw new RuntimeException(ex);
		}
	}

	private static void _estilo(XSSFSheet sheet, int r, int cDesde, int cHasta, Color c, Font font)
	{
		for(int i=cDesde; i<cHasta; i++)
		{
			Cell cell=SheetUtil.getCell(sheet,r,i);
			CellStyle cs=sheet.getWorkbook().createCellStyle();

			// font
			cs.setFont(SheetUtil.awtToPoiFont(sheet.getWorkbook(),font));

			// color
			cs.setFillForegroundColor(SheetUtil.awtToPoiColor(sheet.getWorkbook(),c));
			cs.setFillPattern(FillPatternType.SOLID_FOREGROUND);
			cell.setCellStyle(cs);
		}
	}

	private static void _generarArchivoEnPlanilla(XSSFSheet sheet, Struct st, int col)
	{
		int row=1;

		// creo filename
		Row xssRow=sheet.getRow(row);
		Cell xssCell=xssRow.getCell(col);
		String filename=st.getStructname().toUpperCase()+"S.dat";
		xssCell.setCellValue(filename);

		// estilo filename
		String proppath="ayedtools.collections.excelstyle.background";
		Color bgColor=PropertiesUtil.getColor(proppath,"filename");
		String proppathF="ayedtools.collections.excelstyle.font";
		Font font=PropertiesUtil.getFont(proppathF,"filename");
		_estilo(sheet,row++,col,col+st.getFields().size(),bgColor,font);

		// creo el nombre de la estructura
		xssRow=sheet.getRow(row);
		xssCell=xssRow.getCell(col);
		xssCell.setCellValue("struct "+st.getStructname());

		// estilo estructura
		bgColor=PropertiesUtil.getColor(proppath,"struct");
		font=PropertiesUtil.getFont(proppathF,"struct");
		_estilo(sheet,row++,col,col+st.getFields().size(),bgColor,font);

		// creo tipos de dato
		xssRow=sheet.getRow(row);
		int i=0;
		for(Field field:st.getFields())
		{
			xssCell=xssRow.getCell(col+(i++));
			String x=field.getFieldtype();
			if(field.isCharArray())
			{
				x+="["+field.getCharArrayLength()+"]";
			}
			xssCell.setCellValue(x);
		}

		// estilo types
		bgColor=PropertiesUtil.getColor(proppath,"types");
		font=PropertiesUtil.getFont(proppathF,"types");
		_estilo(sheet,row++,col,col+st.getFields().size(),bgColor,font);

		// creo campos
		xssRow=sheet.getRow(row);
		i=0;
		for(Field field:st.getFields())
		{
			xssCell=xssRow.getCell(col+(i++));
			xssCell.setCellValue(field.getFieldname());
		}

		// estilo campos
		bgColor=PropertiesUtil.getColor(proppath,"fields");
		font=PropertiesUtil.getFont(proppathF,"fields");
		_estilo(sheet,row++,col,col+st.getFields().size(),bgColor,font);

	}

	public static String generateCollToStringImple(String t)
	{
		Struct struct=parse(t).get(0);
		Field fString=struct.getFieldsByType("string").get(0);
		Field fChar=struct.getFieldsByType("char").get(0);

		String template=struct.getTemplateTypenames().get(0);

		StringBuffer sb=new StringBuffer();
		sb.append("template<typename "+template+">\n");
		sb.append("string collToString(Coll<"+template+"> c)\n");
		sb.append("{\n");
		sb.append("\treturn c."+fChar.getFieldname()+"+c."+fString.getFieldname()+";\n");
		sb.append("}\n\n");

		sb.append("template<typename "+template+">\n");
		sb.append("Coll<"+template+"> collFromString(string s)\n");
		sb.append("{\n");
		sb.append("\tColl<"+template+"> c;\n");
		sb.append("\tc."+fChar.getFieldname()+"=s[0];\n");
		sb.append("\tc."+fString.getFieldname()+"=substring(s,1);\n");
		sb.append("\treturn c;\n");
		sb.append("}\n\n");
		return sb.toString();
	}
}
