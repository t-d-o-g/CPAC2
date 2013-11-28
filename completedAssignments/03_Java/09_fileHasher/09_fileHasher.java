import java.util.*;
import java.io.*;


public class FileHasher 
{
    public static void main(String[] args) throws IOException 
    {

	ConsoleReader cr = new ConsoleReader(System.in);
        File inputFile = new File(args[0]);
	File outputFile = new File("hashoutput.txt");

        FileReader fr = new FileReader(inputFile);
        FileWriter fw = new FileWriter(outputFile);
	PrintWriter pw = new PrintWriter(fw);
        HashSet set = new HashSet();

        StreamTokenizer st = new StreamTokenizer(fr);
        String s;

        int token = 1;
        while (token != StreamTokenizer.TT_EOF) {
            token = st.nextToken();
            switch (token) {
            case StreamTokenizer.TT_NUMBER:
                // A number was found; the value is in nval
                double num = st.nval;
                break;
            case StreamTokenizer.TT_WORD:
                // A word was found; the value is in sval
                s = st.sval;
                set.add(s);
                break;
            case '"':
                // A double-quoted string was found; sval contains the contents
                String dquoteVal = st.sval;
                break;
            case '\'':
                // A single-quoted string was found; sval contains the contents
                String squoteVal = st.sval;
                break;
            case StreamTokenizer.TT_EOL:
                // End of line character found
                break;
            case StreamTokenizer.TT_EOF:
                // End of file has been reached
                break;
            default:
                // A regular character was found; the value is the token itself
                char ch = (char)st.ttype;
                break;
            }
        }

        fr.close();
  
      Iterator it = set.iterator();
      while(it.hasNext())
      {
         fw.write("" + it.next());
         pw.println();
      }
      System.out.println();
      System.out.println("  The list of elements have been printed to file.");
        
        fw.close();
    }
}

